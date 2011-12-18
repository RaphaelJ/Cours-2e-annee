/*-------------------------------------------------------------------
 Vanstapel Herman EPL
  
 Serveur DNS
-----------------------------------------------------------------------
-----------------------------------------------------------------------
 Utilisation d'une trame.
-----------------------------------------------------------------------
 C'est la couche liaison
------------------------------------------------------------------------*/


#include <stdio.h>
#include <string.h>
#include <strings.h>
#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "../protocol/protocol.h"
#include "../dnslib/dnslib.h"

enum Evenements {
	         RECEPTION , 
		 DECTOUCHE, 
		 ENVOI,
		 NEAN , 
		 MENU,
		 IPSOURCE ,
		 IPDEST,
		 REQUETEDNS,
                 REPONSEDNS,
		 ENVOIICMP,
		 RECEPTIONICMP
                } ; 

#define FICHIERDNS "dns.db"

struct Global {
FILE *FConfig  ;
int IPInterface ;
int IPDNS ;
int PortApplication    ;
int PortRequeteDNS ;
int Protocole    ;
int Gateway     ;
int NetworkMask ;
int ActivationDNS ;
int MacD ;
int Liaison  ;
/* gestion de la connexion */
int HandleL[100] ;
int HandleE[100] ;
struct gEvenement gEv ;
struct Physique TPhys ;
struct NomsResolus *CacheDNS ;
int courant ;
int prochainalire ;
char BufferR[1000] [TBUFFERPAQUET] ;
int WaitReceive ;
} ;

/*----------------- Prototypes ---------------------------------------------------------------------*/

enum Evenements CoucheReseau( enum Evenements ev,char Buffer[],int tBuffer,struct Global *g) ;
void CoucheLiaison(struct Global *g) ;

int VericationParametreTransport(struct Global *g)
{
 int rc ;
 if ( g->PortApplication == 0 || g->PortRequeteDNS == 0 || g-> Protocole == 0 )
    rc=0 ;
 else
    rc=1 ;
 return rc ;
}

int Help()
{
 printf("Aide \n") ;
 printf("connexion iplocal portlocal ipdistant portdistant\n") ;
 printf("ip_address ip  # Fixe l adresse du pc\n") ;
 printf("netmask masque # fixe le masque réseau du pc \n") ;
 printf("gateway ip  # fixe la passerelle du Pc \n") ;
 printf("dns ip # fixe l adresse du serveur dns\n") ;
 printf("ports ClientMsg  ClientDns ProtocolMsg# fixe le port & Protcole ( udp , tcp )  du client msg et le port du client dns\n") ;
 printf("ping ip # teste une interface\n") ;
 printf("send ipdest portdest msg # envoie un message à lip et port dest, l ip &  port source est fixé par cmd ip & ports \n") ;
 printf("bind on | off # démarre arrete le serveur dns \n") ;
 printf("nslookup nomaresoudre # permet d obtenir l ip pour le nom a resoudre auprès du serveur designé par cmd dns\n") ;
 printf("waitreceive # attend une reception réseau avant de continuer le script\n") ;
 printf("read # permet de lire les message \n") ;
 printf("exit # sort du programme unpc \n") ;
 printf("ipconfig # permet de voir les parametres \n") ; 
 return(1) ;
}

enum Evenements GenerationSegment(struct Segment *ps ,int PortSource,int PortDestination,void *Contenu, struct Global *g )
{
 ps->PortSource = PortSource ;
 ps->PortDestination = PortDestination ;
 memcpy(ps->Buffer,Contenu,sizeof(ps->Buffer)) ;
 fprintf(stderr,"Transport:s:%d,d:%d %s %d\n",ps->PortSource,ps->PortDestination,ps->Buffer,sizeof(ps->Buffer)) ;
 return(ENVOI) ;
}

void AffichePaquet( struct Paquet *pp)
{
 char Buffer1[30], Buffer2[30] ;
 Ipv4ToS(pp->IPSource,Buffer1 ) ;
 Ipv4ToS(pp->IPDestination,Buffer2 ) ;
 fprintf(stderr,"Reseau:message :%s:%s %d\n",Buffer1,Buffer2,pp->Protocole) ;
}

enum Evenements GenerationPaquet(struct Paquet *pp,int IPDestination,int Protocole, void *Contenu, struct Global *g )
{
 int res ;
 
 if ( g->NetworkMask == 0 )
	{
	fprintf(stderr,"Reseau: Le masque n'est pas dï¿½ini\n") ;
	res = NEAN ;
	}
	else
	if ( g->Gateway == 0 )
	{
	fprintf(stderr,"Reseau: Le Gateway est non dï¿½ini\n") ;
	res = NEAN ;
	}
	else
	if ( (IPDestination & g->NetworkMask) != (g->IPInterface & g->NetworkMask) )
	if (( g->IPInterface & g->NetworkMask) == ( g->Gateway & g->NetworkMask))
		{
		fprintf(stderr,"Reseau:Envoi au Routeur !\n") ;
		g->MacD = g->Gateway ;
		}
	else
		{
		fprintf(stderr,"Reseau: Gateway impossible ï¿½atteindre\n") ;
		res = NEAN ;
		}
	else
		g->MacD = IPDestination ;
        /*                           */
	/*   *nc        = Liaison ; */
        /*------------------------------*/
	pp->IPSource    = g->IPInterface ;
	pp->IPDestination    = IPDestination ;
	pp->Protocole = Protocole ;
	memcpy(pp->Buffer,Contenu,sizeof(pp->Buffer)) ;
	AffichePaquet(pp) ;
	if ( pp->IPDestination == g->IPInterface )
		{      /* nous sommes dï¿½a a destination */
		/* envoi a la couche transport */
		res = RECEPTION ;	 
		}
        else
	   res = ENVOI ;  
  return(res) ; 
 }

enum Evenements GenerationTrame(struct Trame *UneTrame,void *Contenu, struct Global *g )
{
   char Buffer[200] ;
         char BufferIP[20] ;
   int rc ;
  /* Remplissage de la trame */
         UneTrame->Numero = 0 ;
	 UneTrame->MacDestination.Constructeur = 0xFF ;
	 UneTrame->MacDestination.Numero = g->MacD ; /* Je nai pas implementï¿½arp */
         UneTrame->MacSource.Constructeur = 0xFF ;
	 UneTrame->MacSource.Numero = g->IPInterface ; /* Je nai pas implementï¿½arp */
         /* &(g->IPInterface) */
         memcpy(UneTrame->Buffer,Contenu,sizeof(UneTrame->Buffer)) ;
         Ipv4ToS((UneTrame->MacDestination).Numero,BufferIP ) ; /* A controler */
         fprintf(stderr,"Liaison:   contenu :%s  vers FF:%s \n",UneTrame->Buffer,BufferIP ) ;
         AffichePaquet((struct Paquet *)  UneTrame->Buffer) ;
          rc = VersCouchePhysique(&(g->TPhys),UneTrame,sizeof(struct Trame)) ; 
         if (rc == -1 )
           {
            perror("Motif:") ;
            return(NEAN) ;
           }
         else
           {
            fprintf(stderr,"Liaison: %d bytes ï¿½rits\n",rc) ;
	    return(ENVOI) ;
           }
}

enum Evenements ResolutionNom(char *NomOuIp,int *IPDestination,struct Global *g)
{
 int PortDestination ;
 fprintf(stderr,">ResolutionNom %s\n",NomOuIp) ;
 if (Ipv4ToInt(NomOuIp, IPDestination)==-1)
    {
      printf(" Ce n'est pas une ip et") ;
     *IPDestination = RechercheNomCacheDNS(g->CacheDNS,NomOuIp) ;
     if (!(*IPDestination))
	{
	 printf("ce nom n'est pas dans le cache dns %d\n",*IPDestination) ;
         return(0) ; 
	}
     else
	 printf("ce nom est dans le cache dns\n") ;	 
    }
 
 return(1) ;
}

enum Evenements ReceptionICMP(Buffer,IPSource )
{
 char BufferProv[20] ;
 int *Code ;

 Ipv4ToS(IPSource,BufferProv) ;
 printf("ICMP Adresse IP Source:%s .......... \n",BufferProv);
 return(NEAN) ;
}

enum Evenements LireMessage( struct Global *g)
{
 int rc ;
 if ( g->courant<g->prochainalire )
                    {
                     printf("Le message %d est %s\n",g->courant,g->BufferR[g->courant]);
                     (g->courant)++;
                     rc = NEAN ;
                    }
                    else
                       {
                        printf("Pas de message a lire\n") ;
                        rc = NEAN ;
                       }
}

enum Evenements AfficherParametres( struct Global *g)
{
 char Buffer[20] ;

 Ipv4ToS(g->IPInterface,Buffer) ;
 printf("Adresse IP    :%s \n",Buffer);
 Ipv4ToS(g->NetworkMask,Buffer ) ;
 printf("Masque Rï¿½eau :%s \n",Buffer);
 Ipv4ToS(g->Gateway,Buffer ) ;
 printf("Adresse Passerelle :%s \n",Buffer);
 Ipv4ToS(g->IPDNS,Buffer ) ;
 printf("Adresse serveur DNS :%s \n",Buffer);
 printf("Port pour votre client DNS :%d \n",g->PortRequeteDNS);
 printf("Port Application     :%d \n",g->PortApplication);
 printf("Protocole utilisï¿½:") ;
 if ( g->Protocole == UDP )
     printf("UDP\n") ;
 else
     if ( g->Protocole == TCP )
         printf("TCP \n") ;
     else
        printf("??? \n") ;
 printf("ServiceDNS %d \n", g->ActivationDNS  );
 return(NEAN) ;
}

enum Evenements ResolutionDNSFichier()
{
  char NomAResoudre[80] ;
  char NomFichier[80] ;
  char Buffer1[80] ;
   int Ip ;

  printf("Entrez le nom a vï¿½ifier:") ;
  fgets(NomAResoudre,sizeof NomAResoudre,stdin) ;
  NomAResoudre[strlen(NomAResoudre)-1] = 0 ;
  printf("Le NomAResoudre est :%s:\n",NomAResoudre) ;
  strncpy(NomFichier,FICHIERDNS,sizeof NomFichier ) ;
  Ip = RechercheNomDB(FICHIERDNS,NomAResoudre) ;
  if(Ip)
     {
      Ipv4ToS(Ip,Buffer1 ) ;
       printf("L'ip de %s est %s \n",NomAResoudre,Buffer1) ;
      }
  return(NEAN) ;
}

enum Evenements ResolutionDNSReseau(struct Segment  *ps,char* NomAResoudre,int *IPDestination,int *Protocole,int *PTS,int *PTD,struct Global *g)
{
// mettre une verification de taille
  memcpy(ps->Buffer,NomAResoudre,sizeof(ps->Buffer)) ; 
  *PTD = 53 ;
  *PTS = g->PortRequeteDNS ;
  *IPDestination = g->IPDNS ;
  *Protocole = UDP ;  
  return(ENVOI) ;
}

enum Evenements ReceptionMessage(char Buffer[],struct Global *g )
{
printf("Le message a ete recu \n") ;
fprintf(stderr,"Application:RECEPTION %s:%d\n",Buffer,(g->prochainalire)+1) ;
strcpy(g->BufferR[g->prochainalire],Buffer) ;
(g->prochainalire)++ ; 
return(NEAN) ;
}

enum Evenements ReponseDNS(char *Buffer,struct Global *g)
{
 char NomDNS[50] ;
 char ADRESSEIP[50] ; 
 int UneIp ;
 /*char Buffer[100] ; Acooriger */

 sscanf(Buffer,"%s %s",NomDNS,ADRESSEIP ) ;  
 printf("Pour %s L'adresse IP est %s\n",NomDNS,ADRESSEIP) ;
 Ipv4ToInt(ADRESSEIP,&UneIp) ; 
 AjoutCacheDNS(g->CacheDNS,NomDNS,UneIp);
 AfficheCacheDNS(g->CacheDNS) ;
 return(NEAN) ;
}


enum Evenements RequeteDNS(char Buffer[],int *PTS,int *PTD,int IPSource, int *IPDestination,int *Protocole,struct Global *g)
{
  int Ip ;
  char NomDNS[50] ;
	
  printf("Traitement d'une requete DNS %s \n",Buffer) ;
  Ip = RechercheNomDB(FICHIERDNS,Buffer) ;
  if(Ip)
    {
     char ChaineIP[80] ;
     Ipv4ToS(Ip,ChaineIP ) ;
     printf("L'ip de %s est %s \n",Buffer,ChaineIP) ;
     /* fabrication de la rï¿½onse */
      strcpy(NomDNS,Buffer ) ;
      sprintf(Buffer,"%s %s",NomDNS,ChaineIP) ;
      *PTD = *PTS ;
      *PTS = 53 ;
      *IPDestination = IPSource ;
      *Protocole = UDP ;  
      return(ENVOI) ;
     }
	 else
	    printf("Resolution impossible !!!\n") ;  
	return(NEAN) ;
}	

int Blanc1013(char *p)
{
 int bon  ;
 bon = 1 ;
 while( *p != 0 && bon )
{
 fprintf(stderr,"%c",*p) ;
 if ( ( *p== 10 ) || ( *p== 13 ) || ( *p==' ') )
    p++ ;
 else
   bon = 0  ;
}
 fprintf(stderr,"\n") ;
 return(bon) ;
}

int GenerationCouches23(struct Trame *UneTrame,struct Paquet *pp,int IPDestination,int Protocole,char *Contenu, struct Global *g )
{
 int rc ;
 rc = GenerationPaquet(pp,IPDestination,Protocole,Contenu,g ) ;
 if ( rc == RECEPTION )
      {
       CoucheReseau( rc,UneTrame->Buffer,sizeof(struct Paquet),g) ;
       return(1) ;
      }
 else
 if ( rc != ENVOI )
       return(0) ; 
   /*  Generation de trame   */
 rc = GenerationTrame(UneTrame,pp,g ) ;
 if ( rc == ENVOI )
      return 1 ;
 else 
      return 0 ;
}

int Connexion( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
 {
   g->Liaison = CreerConnexion(&(g->TPhys),arg1,atoi(arg2),arg3,atoi(arg4)) ;
   if ( g->Liaison == -1 )
       {
        perror("CreerLiaison:") ;
        return(0) ;
       }
   else
      {
       g->HandleL[g->Liaison] = 1 ;
       printf("La Liaison est %d\n",g->Liaison) ;
       return(1) ;
      }
   }

int IpAddress( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
    if (Ipv4ToInt(arg2,&(g->IPInterface))==-1)  /* On rï¿½upï¿½e l'adresse IP */
    {
     printf("Adresse Invalide !!!\n") ;
     return(0) ;
    }
    else
       {
        fprintf(stderr,"ip:%s\n",arg2) ;
        return(1) ;
       }
}

int Netmask( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
       if (Ipv4ToInt(arg1,&(g->NetworkMask))==-1)  /* On rï¿½upï¿½e le masque rï¿½eau */
       {
        printf("Masque Invalide !!!\n") ;
        return(0) ;
       }
       else
          {
           fprintf(stderr,"Masque:%s\n",arg1) ;
	   return(1);
          }
}

int Gateway( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
 {
      if (Ipv4ToInt(arg1,&(g->Gateway))==-1)  /* On rï¿½upï¿½e le masque rï¿½eau */
      {
       fprintf(stderr,"Gateway Invalide !!!\n") ;
       return(0) ;
      }
      else
       {
        fprintf(stderr,"Gateway:%s\n",arg1) ;
        return(1) ;
       }
} 

int Dns( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
     if (Ipv4ToInt(arg1,&(g->IPDNS))==-1)  /* On rï¿½upï¿½e le masque rï¿½eau */
     {
      fprintf(stderr,"Adresse Serveur dns Invalide:%s \n",arg1) ;
      return(0) ;
     }
     else
        return(1) ;
}

int Ports( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
     g->PortApplication = atoi(arg1) ;
     g->PortRequeteDNS = atoi(arg2 ) ;
     if (strcmp(arg3,"UDP")==0)
	 g->Protocole = UDP ;
     else
         if (strcmp(arg3,"TCP")==0)
	     g->Protocole = TCP ;
	 else
	     {
		    fprintf(stderr,"Choix non valable !!!\n") ;
		    return(0) ;
	     }
      fprintf(stderr,"Les ports applic : %d Port Client Dns %d \n", g->PortApplication, g->PortRequeteDNS ) ;
      return(1) ;
     }

int Ping( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
  struct Trame UneTrame ;
  struct Paquet *pp ;
  enum Evenements  rc ;
  int *Code ; 
  char BufferICMP[100] ;
  int IPDestination ;
  
  pp = (struct Paquet *) UneTrame.Buffer ;
  rc =  ResolutionNom(arg1,&IPDestination,g) ;
  if ( !rc )
      return 0 ;
  /* generation entête icmp */

   Code = (int * ) BufferICMP ; ;
   *Code = ICMPECHO ;  /* On rajoute le code ICMP a la place du message transport */ 
          
   rc = GenerationCouches23(&UneTrame,pp,IPDestination,ICMP,BufferICMP,g ) ;
   return(rc) ;
}

int Send( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
  /* arg1 ip arg2 port arg3 message */
  struct Trame UneTrame ;
  struct Paquet *pp ;
  struct Segment *ps ;
  char *DebutMessage ;
  enum Evenements  rc ;
  int IPDestination ;
  int PortSource, PortDestination ;

  pp = (struct Paquet *) UneTrame.Buffer ;
  ps = (struct Segment*) pp->Buffer ;
  
  rc =  ResolutionNom(arg1,&IPDestination,g) ;
  if ( !rc )
      return 0 ;
   /* recopie du message à envoyer */
   /* a adapter */
   PortSource = g->PortApplication ;
   PortDestination = atoi(arg2) ;
   
   /* fprintf(stderr,"arg3 %s\n",arg3 ) ; */
   DebutMessage = strstr(Buffer,arg3 ) ;
   rc  = GenerationSegment(ps ,PortSource,PortDestination,DebutMessage, g )  ; /* arg 3 message */
   rc =  GenerationCouches23(&UneTrame,pp,IPDestination,g-> Protocole ,(char *) ps,g ) ;
   
   return(rc) ;
 }

int Bind( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
   if (strcmp(arg1,"on")==0)
      {
        printf("Service DNS Actif\n") ;
        g->ActivationDNS = 1 ;
        return(1) ;
      }
   else
   if (strcmp(arg1,"off")==0)
      {
        printf("Service DNS desactive\n") ;
        g->ActivationDNS = 0 ;
        return(1) ;
      }
   else
      printf("Erreur de syntaxe \n") ;
  return(0) ;
 }

int NsLookup( char *Buffer,char *arg1,char *arg2,char* arg3, char *arg4,  struct Global *g)
{
  struct Trame UneTrame ;
  struct Paquet *pp ;
  struct Segment *ps ;
  char *DebutMessage ;
  enum Evenements  rc ;
  int Protocole ;
  int IPDestination ;
  int PortSource, PortDestination ;

  pp = (struct Paquet *) UneTrame.Buffer ;
  ps = (struct Segment*) pp->Buffer ;

  /* arg1 Nom à Résoudre */
  rc =  ResolutionDNSReseau( ps, arg1,&IPDestination,&Protocole,&PortSource,&PortDestination,g) ;
   rc  = GenerationSegment(ps ,PortSource,PortDestination,ps->Buffer, g )  ; /* arg 3 message */
   rc =  GenerationCouches23(&UneTrame,pp,IPDestination,Protocole ,(char *) ps,g ) ;
  return(rc) ;
 }

int WaitReceive(struct Global *g)
{
  g->WaitReceive = 1 ; 
  CoucheLiaison(g) ;
  return 1 ;
}

int Interpreteur( char *Buffer, struct Global *g)
{
  char arg0[80],arg1[80],arg2[80],arg3[80],arg4[80] ;
  int rc ;
  bzero(arg0,sizeof(arg1));
  bzero(arg1,sizeof(arg1));
  bzero(arg2,sizeof(arg2));
  bzero(arg3,sizeof(arg3));
  bzero(arg4,sizeof(arg4));
  fprintf(stderr,"Interpreteur ;") ;
  sscanf(Buffer,"%s %s %s %s %s\n",arg0,arg1,arg2,arg3,arg4) ;
  fprintf(stderr,"arg0 %s \n",arg0 ) ;

  /* ATTENTIO? NE PAS OUBLIER ELSE SINON ERREUR DE SYTAXE */
  if (strcmp(arg0,"connexion")==0)  rc=Connexion(Buffer,arg1,arg2,arg3, arg4,g) ;
  else 
  if (strcmp(arg0,"ip")==0 &&( strcmp(arg1,"address")==0) ) rc=IpAddress(Buffer,arg1,arg2,arg3, arg4,g) ;
  else
  if (strcmp(arg0,"netmask")==0 ) rc = Netmask(Buffer,arg1,arg2,arg3, arg4,g) ;
  else 
 if (strcmp(arg0,"gateway")==0 ) rc = Gateway(Buffer,arg1,arg2,arg3, arg4,g) ;
  else
 if (strcmp(arg0,"dns")==0 ) rc = Dns(Buffer,arg1,arg2,arg3, arg4,g) ;
 else
 if (strcmp(arg0,"ports")==0 ) rc = Ports(Buffer,arg1,arg2,arg3, arg4,g) ;
 else
 if (strcmp(arg0,"ping")==0 ) rc = Ping(Buffer,arg1,arg2,arg3, arg4,g) ;
 else
 if (strcmp(arg0,"send")==0 ) rc = Send(Buffer,arg1,arg2,arg3, arg4,g) ;
 else
 if (strcmp(arg0,"bind")==0)  rc = Bind(Buffer,arg1,arg2,arg3, arg4,g) ;
 else
 if (strcmp(arg0,"nslookup")==0 )  rc= NsLookup(Buffer,arg1,arg2,arg3, arg4,g) ;
 else
 if (strcmp(arg0,"waitreceive")==0 ) rc=WaitReceive(g) ;
 else
 if (strcmp(arg0,"read")==0) rc = LireMessage( g ) ;
 else
 if (strcmp(arg0,"exit")==0) exit(0);
 else
 if (strcmp(arg0,"ipconfig")==0) rc = AfficherParametres( g ) ;
 else
 if (strcmp(arg0,"help")==0) rc = Help() ;
 else
 if (Blanc1013(Buffer))
    {
     fprintf(stderr,"Ligne vide \n" ) ;
     rc =  1 ;
    }
 else
    rc = 0 ;
 fprintf(stderr,"fin Interpeteur\n") ;
 return(rc) ;
}


 enum Evenements CoucheApplication(enum Evenements ev,char Buffer[],int tBuffer,int IPSource,int *IPDestination,int *Protocole,int *PTS,int *PTD, struct Global *g)
{
 char Chaine[50] ;
 int choix ;
 int rc ;
 

 switch(ev)
 {
  case RECEPTION:  /* On a un ï¿½ï¿½ent de plus */
        rc =  ReceptionMessage( Buffer, g ) ;
	break ;
  case RECEPTIONICMP:
        rc = ReceptionICMP(Buffer,IPSource ) ;
        break ;
  case REPONSEDNS:
        /* Traitement de la réponse en provenance du serveur dns */	 
        rc = ReponseDNS( Buffer, g) ;
	break ;

  case REQUETEDNS:
        /* traitement de la requete DNS par le serveur DNs RequeteDNS  */
	rc = RequeteDNS( Buffer, PTS, PTD,  IPSource, IPDestination, Protocole, g) ;
	break ;	
  default:
         rc = NEAN ;
  }
 return(rc) ;
}

 enum Evenements CoucheTransport(enum Evenements ev,char Buffer[],int tBuffer,int *Protocole,int IPSource,int *IPDestination,struct Global *g)
{
 static int Numero ;
	int res    ;
 struct Segment *ps ;
 int	PortSource,PortDestination    ;

 /*********************    Phase montante ********************************************************************************************/
 fprintf(stderr,"Transport:debut\n") ;
 ps = (struct Segment*) Buffer ;
 PortSource = ps->PortSource ;
 PortDestination = ps->PortDestination ;
 
 
 switch(ev)
 {
  case MENU:
  case RECEPTIONICMP:
	fprintf(stderr,"Reseau: Recepton d'un message ICMP\n") ;
        res=CoucheApplication(RECEPTIONICMP,ps->Buffer,sizeof(ps->Buffer),IPSource,IPDestination,Protocole,&PortSource,&PortDestination,g) ;
	break ;	  
  case RECEPTION: // Reception d'un message
       
       if ( ps->PortDestination==g->PortApplication && *Protocole == g->Protocole  ) /* destine applic */
          res=CoucheApplication(ev,ps->Buffer,sizeof(ps->Buffer),IPSource,IPDestination,Protocole,&PortSource,&PortDestination,g) ;
       else
          if (ps->PortDestination == 53 && g->ActivationDNS && *Protocole==UDP ) 
	     res=CoucheApplication(REQUETEDNS,ps->Buffer,sizeof(ps->Buffer),IPSource,IPDestination,Protocole,&PortSource,&PortDestination,g) ;  
	  else
	      if (ps->PortDestination == g->PortRequeteDNS && *Protocole==UDP ) 
	          res=CoucheApplication(REPONSEDNS,ps->Buffer,sizeof(ps->Buffer),IPSource,IPDestination,Protocole,&PortSource,&PortDestination,g) ;
	      else
                 {
                  fprintf(stderr,"Transport: Port ou protocole Invalide \n") ;
		  /* ici ajout */ 
                  fprintf(stderr,"Protocole %d \n",*Protocole ) ;
		  fprintf(stderr,"Port Destination  %d \n", ps->PortDestination ) ;
                  fprintf(stderr,"--------------------------------------------------------\n") ;
		  fprintf(stderr,"Port Application  %d \n" , g->PortApplication ) ;
		  fprintf(stderr,"Port Requete DNS  %d \n",g->PortRequeteDNS ) ;
                  fprintf(stderr,"Activation DNS %d \n",g->ActivationDNS ) ;
                  res = NEAN ;
                 }
       break;
   default:
       fprintf(stderr,"Cette option est invalide au niveau transport !!!\n") ;
           
 } ;
 /************ phase descendante ************************************************************/
 switch(res)
       {
       case ENVOI:
            res=GenerationSegment(ps ,PortSource,PortDestination,ps->Buffer,g ) ;
            break ;
       case NEAN:
            break;
       default:
            res=NEAN ;
       };
 
 fprintf(stderr,"Transport:Fin\n") ;
 return res ;
}


enum Evenements CoucheReseau( enum Evenements ev,char Buffer[],int tBuffer,struct Global *g)
{
 static int Numero ;
        int res ;
 struct Paquet *pp ;
        int IPDestination  ;
 int IPD ;
 int Protocole ;

 /********************* Phase Montante *******************************************************/
 fprintf(stderr,"Reseau:Debut\n") ;
 redo:
 pp = (struct Paquet *) Buffer ;
 switch(ev)
 {
  
  case MENU:
  case RECEPTION:
       {
        char Buffer1[30], Buffer2[30] ;
        Ipv4ToS(pp->IPSource,Buffer1 ) ;
        Ipv4ToS(pp->IPDestination,Buffer2 ) ;
        fprintf(stderr,"Reseau:%s:%s: %d  \n",Buffer1,Buffer2,pp->Numero) ;
        if ( pp->IPDestination == g->IPInterface )
	   {
             Protocole = pp->Protocole ;
	     if ( Protocole == ICMP )
                {
                 int *code ;
                 code = (int * ) pp->Buffer ;
                 if ( *code == ICMPRESPONSE )
                    {
                     fprintf(stderr,"Reseau: Reception ICMPRESPONSE \n") ;  
		     res = CoucheTransport(RECEPTIONICMP,pp->Buffer,sizeof(pp->Buffer),&Protocole,pp->IPSource,&IPDestination,g) ;
                    }
                 else
                    if (*code == ICMPECHO )
                        {
                         fprintf(stderr,"Reseau: Reception ICMPECHO et generation ICMP RESPONSE \n") ;
                         /* Generation de la reponse */
                         *code = ICMPRESPONSE ;
                         IPDestination = pp->IPSource ;
                         Protocole = ICMP ;
                         res = ENVOI ;      
                        }
                     else
                        {
                          fprintf(stderr,"Reseau: Code ICMP Inconnu \n") ;
                          res = NEAN ;
                        }       
                } 
             else 	   
                res = CoucheTransport(ev,pp->Buffer,sizeof(pp->Buffer),&Protocole,pp->IPSource,&IPDestination,g) ;
	}  
        else
	  {
           printf("Reseau:Adresse de destination non connue \n") ;
           res = NEAN ;
	  }
       }
        break ;
  default:
         res = NEAN ;
  }
  fprintf(stderr,"reseau:phase descendante\n") ;
 switch(res)
 {
   case ENVOI:
       {
        res = GenerationPaquet(pp,IPDestination,Protocole,pp->Buffer, g ) ;
        if (res==RECEPTION  )
           { 
             ev = res ;
             goto redo;
           }
         break ;
        }
    case NEAN:
              break ;
    default:
              fprintf(stderr,"Reseau: Option non reconnue\n") ;
              break ;
 }
 fprintf(stderr,"Reseau:Fin\n") ;
 return res ;
}

void CoucheLiaison(struct Global *g)
{
 int rc ;
 enum Evenements rce ;
 static char Buffer[TBUFFERTRAME] ;
 
 static struct Trame UneTrame ;
 int EHL,EHE ;
 int Redo = 1 ;

 while(Redo)
 {
  if (g->WaitReceive )
        g->HandleL[0] = 0 ; /* En Mode WaitReceive le clavlier est désactivé */
  else
     g->HandleL[0] = 1 ;
  rc = PrepareEvenement( &(g->gEv),g->HandleL,g->HandleE,100,300,0 ) ;
  /* on s'endort en attendant que quelque chose se produise */
  if (!VericationParametreTransport(g) )
     printf("ENCODEZ VOS PARAMETRES DE TRANSPORT !!!!!\n") ;
  printf(">>>");fflush(stdout);
  rc = AttendreEvenement(&(g->gEv),&EHL,&EHE) ;
  fprintf(stderr,"Liaison:EHL %d\n",EHL) ;
  if ( rc == -1 )
     {
      printf("Liaison:Erreur attendre Evenement \n");
      exit(0) ;
     }
  else
  if ( rc == 0 )
      printf("Liaison:Timeout!!!!\n") ;
  else
     {
      /* gestion de l'evenement */	     
      if ( EHL == 0 ) /* Frappe du clavier */
        {
          /* appel à l interpreteur */
          char Chaine[50] ;
          fgets(Chaine,sizeof(Chaine),stdin) ; /* Evitez le getchar() !!!!! */
          Chaine[strlen(Chaine)-1]=0 ; /* On supprime le newline */
	  fprintf(stderr,"La touche pressï¿½ est %s \n",Chaine) ;
          rc = Interpreteur( Chaine, g) ;
                if ( rc==0 )
                   {
                    fprintf(stderr,"erreur de Syntaxe \n") ;
                    printf("erreur de Syntaxe \n") ;
                   }
        }
      else
        if ( EHL != 0 ) /* evenement reseau */
        {
         int tm=sizeof(UneTrame) ;

         /* Corriger ici */
         if ( g->WaitReceive)
 	    {
              Redo = 0 ;
              g->WaitReceive = 0 ;
            }
         rc = OrigineCouchePhysique(&(g->TPhys),&UneTrame,&tm) ;
         memcpy(Buffer,UneTrame.Buffer,sizeof(UneTrame.Buffer)) ;
         fprintf(stderr,"Liaison::%d bytes lus\n",tm) ;
         if (UneTrame.MacDestination.Numero== g->IPInterface )
            {
             rce = CoucheReseau(RECEPTION,Buffer,sizeof Buffer,g) ;
            }
          else
             {
              char BufferIP[20] ;
              Ipv4ToS(UneTrame.MacDestination.Numero,BufferIP ) ;
              fprintf(stderr,"Liaison la mac n'est pas bonne FF:%s \n",BufferIP) ;
              rce=NEAN ;
             }
        }
      else
        printf("Non connu !!!!!\n") ;

      /***En envoi de la trame *******************************************/
      if ( rce == ENVOI ) /* Bug si mauvaise position */
         {
          rc = GenerationTrame(&UneTrame,Buffer,g ) ;
         }
    }
 }
};

int main(int argc,char *argv[])
{
 
 /*  static struct Physique Phys[1024]  ;*/
 
 static struct Global G ; /* important que tout les champs soient à zéro */
 
 int bidon ;
 int rc ;
 int Ligne=0 ;
 char Buffer[200] ;
 
 /* Attention cette ligne d intialisation cache est importante */
 G.CacheDNS = InitialiseCacheDNS(100) ;
 printf("Demarrage ClientPC \n") ;
 if (argc<2)
    {
     printf("unpc Config \n") ;
     exit(0) ;
    }
  G.FConfig = fopen( argv[1],"r+") ;
  if ( G.FConfig == NULL )
      {
       printf("Fichier Non ouvert %s \n",argv[1] ) ;
       exit(0) ;
      }
  else
      printf("Ouverture de %s \n",argv[1] ) ;
 setbuf(G.FConfig,NULL ) ; /* on supprime la bufferisation */
 fgets(Buffer,sizeof Buffer,G.FConfig ) ;
 while (!feof(G.FConfig))
 {
  Ligne++  ;
  fprintf(stderr,"Ligne %d \n",Ligne) ;
  /*   ici appel système                         */
   rc = Interpreteur( Buffer, &G) ;
   if ( rc==0 )
     {
      fprintf(stderr,"Fichier de Config corrompu \n") ;
      exit(0) ;
      };
   fgets(Buffer,sizeof Buffer,G.FConfig ) ;
 }

 if ( G.Liaison == 0 )
     {
      printf("Pas de connexion dÃ©finie \n") ;
      exit(0) ;
     }
 if ( G.IPInterface == 0 )
     {
      printf("Pas de connexion dÃ©finie \n") ;
      exit(0) ;
     }
 if ( G.NetworkMask == 0 )
     {
      printf("Pas de masque dÃ©finit \n") ;
      exit(0) ;
     }
 if ( G.Gateway == 0 )
     {
      printf("Pas de masque dÃ©finit \n") ;
      exit(0) ;
     }
 if (  G.IPDNS == 0 )
     {
      printf("Pas de masque dÃ©finit \n") ;
      exit(0) ;
     }

 fprintf(stderr,"******************************************\n") ;
 CoucheLiaison(&G) ;
}

