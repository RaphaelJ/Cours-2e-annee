/*--------------------------------------------------------------------
 Vanstapel Herman EPL
  
 Serveur DNS
-----------------------------------------------------------------------
------------------------------------------------------------------------
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
                 REPONSEDNS
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
struct NomsResolus *CacheDNS ;
int courant ;
int prochainalire ;
char BufferR[1000] [TBUFFERPAQUET] ;
} ;

int VericationParametreTransport(struct Global *g)
{
 int rc ;
 if ( g->PortApplication == 0 || g->PortRequeteDNS == 0 || g-> Protocole == 0 )
    rc=0 ;
 else
    rc=1 ;
 return rc ;
}

void AfficheMenu(struct Global *g)
{
 printf("0 afficher le menu a nouveau\n") ;
 printf("1 envoyer un message\n") ;
 printf("2 lire    un message \n") ;
 printf("3 afficher les param�res r�eaux  \n") ;
 printf("6 modifier les port de l'application & DNS\n") ;

 printf("7 Effectuer une requete locale sur la bd DNS\n") ;
 printf("8 Envoyer une requete au serveur DNS \n") ;
 if (!(g->ActivationDNS))
    printf("9 Activer service DNS\n") ;
 else
    printf("9 Desactiver service DNS\n") ;
 printf("10 pour quitter\n") ;
 return ;
}

/* Sortir les fonctions Pour recevoir les donn�es */

enum Evenements EnvoyerMessage(char Buffer[],int *PTS,int *PTD,int *IPDestination,int *Protocole,struct Global *g)
{
 int PortDestination ;
 char BufferSaisie[80] ;


 printf(" Entrez le nom ou adresse IP dest:") ;
 /* La chaine doit etre contenue dans le segment */
 fgets(BufferSaisie,sizeof BufferSaisie,stdin) ;
 BufferSaisie[strlen(BufferSaisie)-1] = 0 ; /* Bug */
 if (Ipv4ToInt(BufferSaisie, IPDestination)==-1)
    {
     printf(" Ce n'est pas une ip et") ;
     *IPDestination = RechercheNomCacheDNS(g->CacheDNS,BufferSaisie) ;
     if (!(*IPDestination))
	{
	 printf("ce nom n'est pas dans le cache dns %d\n",*IPDestination) ;
         return(NEAN) ; 
	}
     else
	 printf("ce nom est dans le cache dns\n") ;	 
    }
 printf("Entrez Port Destinataire:") ;
 fgets(BufferSaisie,sizeof BufferSaisie,stdin) ;
 Buffer[strlen(BufferSaisie)-1] = 0 ;
 PortDestination=atoi(BufferSaisie) ;
                
 printf("Message:");
 fgets(Buffer,TBUFFERTRANSPORT,stdin);
 Buffer[strlen(Buffer)-1] = 0 ;
 *PTS = g->PortApplication ;
 *PTD = PortDestination ;
 *Protocole = g-> Protocole ; 
 return(ENVOI) ;
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
 printf("Masque R�eau :%s \n",Buffer);
 Ipv4ToS(g->Gateway,Buffer ) ;
 printf("Adresse Passerelle :%s \n",Buffer);
 Ipv4ToS(g->IPDNS,Buffer ) ;
 printf("Adresse serveur DNS :%s \n",Buffer);
 printf("Port pour votre client DNS :%d \n",g->PortRequeteDNS);
 printf("Port Application     :%d \n",g->PortApplication);
 printf("Protocole utilis�:") ;
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

 enum Evenements ModifierParametres( struct Global *g)
{
  char Buffer[20] ;
		   
  printf("Entrez le Portclient DNS:") ;
  fgets(Buffer,sizeof Buffer,stdin) ;
  Buffer[strlen(Buffer)-1] = 0 ;
  g->PortRequeteDNS=atoi(Buffer) ;		   
		   
  printf("Entrez le Port Application:") ;
  fgets(Buffer,sizeof Buffer,stdin) ;
  Buffer[strlen(Buffer)-1] = 0 ;
  g->PortApplication=atoi(Buffer) ;
		   
  redo:
  printf("Entrez le protocole de votre Application ( UDP ou TCP ):") ;
  fgets(Buffer,sizeof Buffer,stdin) ;
  Buffer[strlen(Buffer)-1] = 0 ;
  if (strcmp(Buffer,"UDP")==0)
     g->Protocole = UDP ;
  else
      if (strcmp(Buffer,"TCP")==0)
          g->Protocole = TCP ;
       else
          {
	    printf("Choix non valable !!!\n") ;
	    goto redo ;
	 }
  return(NEAN) ;
 }


enum Evenements ResolutionDNSFichier()
{
  char NomAResoudre[80] ;
  char NomFichier[80] ;
  char Buffer1[80] ;
   int Ip ;

  printf("Entrez le nom a v�ifier:") ;
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

enum Evenements ResolutionDNSReseau(char Buffer[],int tBuffer,int IPSource,int *IPDestination,int *Protocole,int *PTS,int *PTD,struct Global *g)
{
 char NomAResoudre[80] ;
 printf("Entrez le nom a v�ifier:") ;
 fgets(NomAResoudre,sizeof NomAResoudre,stdin) ;
  NomAResoudre[strlen(NomAResoudre)-1] = 0 ;
// mettre une verification de taille
  strcpy(Buffer,NomAResoudre) ; 
  *PTD = 53 ;
  *PTS = g->PortRequeteDNS ;
  *IPDestination = g->IPDNS ;
  *Protocole = UDP ;  
  return(ENVOI) ;
}

enum Evenements ActivationServeurDNS(struct Global *g)
{
if ( !g->ActivationDNS)
    printf("Demarrage service DNS\n") ;
else
   printf("Arret service DNS\n") ;
g->ActivationDNS=!(g->ActivationDNS) ;
return(NEAN) ;
}

enum Evenements ReceptionMessage(char Buffer[],struct Global *g )
{
printf("Le message a ete recu \n") ;
fprintf(stderr,"Application:RECEPTION %s:%d\n",Buffer,(g->prochainalire)+1) ;
strcpy(g->BufferR[g->prochainalire],Buffer) ;
(g->prochainalire)++ ; 
return(NEAN) ;
}

enum Evenements ReponseDNS(struct Global *g)
{
 char NomDNS[50] ;
 char ADRESSEIP[50] ; 
 int UneIp ;
 char Buffer[100] ;

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
     /* fabrication de la r�onse */
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

 enum Evenements CoucheApplication(enum Evenements ev,char Buffer[],int tBuffer,int IPSource,int *IPDestination,int *Protocole,int *PTS,int *PTD, struct Global *g)
{

 
 
 char Chaine[50] ;
 int choix ;
 int rc ;
 

 switch(ev)
 {
  case MENU:
           AfficheMenu(g) ;
           rc = NEAN ;
           break ;
  case DECTOUCHE:
           fgets(Chaine,sizeof(Chaine),stdin) ; /* Evitez le getchar() !!!!! */
           Chaine[strlen(Chaine)-1]=0 ; /* On supprime le newline */
	   fprintf(stderr,"La touche press� est %s \n",Chaine) ;
           choix = atoi(Chaine) ;
           switch(choix)
           {
            case 0:  AfficheMenu(g) ;
                     rc = NEAN ;
                     break ;
            case 1:
                     rc  = EnvoyerMessage( Buffer, PTS,PTD,IPDestination,Protocole,g) ;
                   break ;
            case 2:
		   rc=LireMessage( g ) ;
                   break ;
            case 3:
                  rc = AfficherParametres( g ) ;
                  break ;
	    case 4:
	          /* ajout DNS                 */
	           AfficheCacheDNS(g->CacheDNS) ;
		  rc = NEAN ;
		  break ; 
            case 6:
                  
                  rc = ModifierParametres( g ) ;
                  break ;
	    case 7:
	          rc = ResolutionDNSFichier() ;
                  break ; 
	    case 8:
	      
	          rc = ResolutionDNSReseau( Buffer,tBuffer,IPSource,IPDestination,Protocole,PTS,PTD,g) ;
		  break ;

	    case 9:
	           rc = ActivationServeurDNS( g ) ;
		   break ;
            case 10:exit(0);
            default:
	           printf("Touches non connue \n") ;
	           rc = NEAN ;
          }
          break;

  case RECEPTION:  /* On a un ��ent de plus */
         rc =  ReceptionMessage( Buffer, g ) ;
	break ;

  case REPONSEDNS:	 
        rc = ReponseDNS(g) ;
	break ;

  case REQUETEDNS:
	rc =  RequeteDNS( Buffer,PTS,PTD,IPSource,IPDestination, Protocole, g) ;
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

 fprintf(stderr,"Transport:debut\n") ;
 ps = (struct Segment*) Buffer ;
 PortSource = ps->PortSource ;
 PortDestination = ps->PortDestination ;
 
 
 switch(ev)
 {
  case MENU:	  
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
		  fprintf(stderr,"Port Destination  %d \n", ps->PortDestination ) ;
		  fprintf(stderr,"Port Application  %d \n" , g->PortApplication ) ;
		  fprintf(stderr,"Port Requete DNS  %d \n",g->PortRequeteDNS ) ;
		  fprintf(stderr,"Protocole %d \n",*Protocole ) ;
		  fprintf(stderr,"Activation DNS %d \n",g->ActivationDNS ) ;
                  res = NEAN ;
                 }
       break;
   case DECTOUCHE:
       res=CoucheApplication(ev,ps->Buffer,sizeof(ps->Buffer),0,IPDestination,Protocole,&PortSource,&PortDestination,g) ;
       break ;
   default:
       fprintf(stderr,"Cette option est invalide au niveau transport !!!\n") ;
           
 } ;
 
 switch(res)
       {
      // ENVOI ICMP traiter
       case ENVOI:
            ps->PortSource = PortSource ;
            ps->PortDestination = PortDestination ;
            fprintf(stderr,"Transport:s:%d,d:%d %s\n",ps->PortSource,ps->PortDestination,ps->Buffer) ;
            break ;
       case NEAN:
            break;
       default:
            res=NEAN ;
       };
 
 fprintf(stderr,"Transport:Fin\n") ;
 return res ;
}


enum Evenements CoucheReseau( enum Evenements ev,char Buffer[],int tBuffer,int *nc,struct Global *g)
{
 static int Numero ;
        int res ;
 struct Paquet *pp ;
        int IPDestination  ;
 int IPD ;
 int Protocole ;

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
        fprintf(stderr,"Reseau:%s:%s: %d  \n",Buffer1,Buffer2,
                pp->Numero) ;
        if ( pp->IPDestination == g->IPInterface )
	   {
             Protocole = pp->Protocole ;	   
             res = CoucheTransport(ev,pp->Buffer,sizeof(pp->Buffer),&Protocole,pp->IPSource,&IPDestination,g) ;
	   }  
        else
	  {
           printf("Reseau:Adresse de destination non connue \n") ;
           res = NEAN ;
	  }
       }
        break ;
  case DECTOUCHE:  /* On a un ��ent de plus */
        pp = (struct Paquet *) Buffer ;
	Protocole = pp->Protocole ;
        res = CoucheTransport(ev,pp->Buffer,sizeof(pp->Buffer),&Protocole,0,&IPDestination,g) ;
        
       break ;
  default:
         res = NEAN ;
  }

 /* faut-il �rire un paquet ip en sortie */ 
 switch(res)
 {
   case ENVOI:
       {
        char Buffer1[30], Buffer2[30] ;
        if ( g->NetworkMask == 0 )
           {
            fprintf(stderr,"Reseau: Le masque n'est pas d�ini\n") ;
            res = NEAN ;
           }
        else
          if ( g->Gateway == 0 )
           {
            fprintf(stderr,"Reseau: Le Gateway est non d�ini\n") ;
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
                     fprintf(stderr,"Reseau: Gateway impossible �atteindre\n") ;
                     res = NEAN ;
                    }
            else
                g->MacD = IPDestination ;
           /*   *nc        = Liaison ; */
              pp->Numero = Numero++ ;
              pp->IPSource    = g->IPInterface ;
              Ipv4ToS(pp->IPSource,Buffer1 ) ;
              pp->IPDestination    = IPDestination ;
              Ipv4ToS(pp->IPDestination,Buffer2 ) ;
	      pp->Protocole = Protocole ;
              fprintf(stderr,"Reseau:message %d:%s:%s %d\n",pp->Numero,Buffer1,Buffer2,pp->Protocole) ;
              if ( pp->IPDestination == g->IPInterface )
	         {      /* nous sommes d�a a destination */
		    /* envoi a la couche transport */
		    ev = RECEPTION ;	 
		    goto redo;
		 }   
              }
              break ;
    case NEAN:
              break ;
    default:
              fprintf(stderr,"Reseau: Option non reconnue\n") ;
              break ;
 }
 fprintf(stderr,"Reseau:Fin\n") ;
 return res ;
}

void CoucheLiaison(int HandleL[],struct Physique *Phys,struct Global *g)
{
 int rc ;
 enum Evenements rce ;
 static char Buffer[TBUFFERTRAME] ;
 static int HandleE[100] ;
 static struct gEvenement gEv ;
 static struct Trame UneTrame ;
 static int Numero = 0 ;
 int NC ;
 int EHL,EHE ;
 

 rc = PrepareEvenement( &gEv,HandleL,HandleE,100,300,0 ) ;
 while(1)
 {
  /* on s'endort en attendant que quelque chose se produise */
  if (!VericationParametreTransport(g) )
     printf("ENCODEZ VOS PARAMETRES DE TRANSPORT !!!!!\n") ;
  printf(">>>");fflush(stdout);
  rc = AttendreEvenement(&gEv,&EHL,&EHE) ;
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
         rce = CoucheReseau(DECTOUCHE,Buffer,sizeof Buffer,&NC,g) ;
        }
      else
        if ( EHL != 0 ) /* evenement reseau */
        {
         int tm=sizeof(UneTrame) ;

         /* Corriger ici */
        /* rc = OrigineCouchePhysique(&(Phys[EHL]),&UneTrame,&tm) ;*/
         rc = OrigineCouchePhysique(Phys,&UneTrame,&tm) ;
         memcpy(Buffer,UneTrame.Buffer,sizeof(UneTrame.Buffer)) ;
         fprintf(stderr,"Liaison::%d bytes lus\n",tm) ;
         if (UneTrame.MacDestination.Numero== g->IPInterface )
            {
             NC = EHL ;
             rce = CoucheReseau(RECEPTION,Buffer,sizeof Buffer,&NC,g) ;
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
      if ( rce == ENVOI ) /* Bug si mauvaise position */
         {
         char BufferIP[20] ;
         /* Remplissage de la trame */
         UneTrame.Numero = ++Numero ;
	 UneTrame.MacDestination.Constructeur = 0xFF ;
	 UneTrame.MacDestination.Numero = g->MacD ; /* Je nai pas implement�arp */
         memcpy(UneTrame.Buffer,Buffer,sizeof(UneTrame.Buffer)) ;
         Ipv4ToS(UneTrame.MacDestination.Numero,BufferIP ) ;
         fprintf(stderr,"Liaison: Num�o %d:%s  vers FF:%s \n",NC,UneTrame.Buffer,BufferIP ) ;
     /*    rc = VersCouchePhysique(&(Phys[NC]),&UneTrame,sizeof(UneTrame)) ; */
          rc = VersCouchePhysique(Phys,&UneTrame,sizeof(UneTrame)) ; 
         if (rc == -1 )
            perror("Motif:") ;
         else
            fprintf(stderr,"Liaison: %d bytes �rits\n",rc) ;
        }
     }     
 } 
}

int Blanc1013(char *p)
{
 int bon  ;
 bon = 1 ;
 while( *p != 0 && bon )
{
 fprintf(stderr,"%c",*p) ;
 if ( ( *p!= 10 ) || ( *p!= 13 ) || (*p!=' '))
     bon = 0  ;
  p++ ;
}
 fprintf(stderr,"\n") ;
 return(bon) ;
}

int main(int argc,char *argv[])
{
 static int HandleL[100] ;
 /*  static struct Physique Phys[1024]  ;*/
 static struct Physique TPhys ;
 static struct Global G ;
 int Liaison = 0 ;
 int bidon ;
 int rc ;
 int Ligne=0 ;
 char Buffer[200] ;
 char arg0[80],arg1[80],arg2[80],arg3[80],arg4[80] ;
 
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
  bzero(arg1,sizeof(arg1));
  bzero(arg2,sizeof(arg2));
  sscanf(Buffer,"%s %s\n",arg1,arg2) ;
  if (strcmp(arg1,"connexion")==0)
  {
   bzero(arg1,sizeof(arg1));
   bzero(arg2,sizeof(arg2));
   bzero(arg3,sizeof(arg3));
   bzero(arg4,sizeof(arg4));
   sscanf(Buffer,"%s %s %s %s %s\n",arg0,arg1,arg2,arg3,arg4) ;
   fprintf(stderr,"arg4:%s \n",arg4) ;
   Liaison = CreerConnexion(&TPhys,arg1,atoi(arg2),arg3,atoi(arg4)) ;
   if ( Liaison == -1 )
       {
        perror("CreerLiaison:") ;
        exit(0) ;
       }
   else
       printf("La Liaison est %d\n",Liaison) ;
   }
  else 
  if (strcmp(arg1,"ip_address")==0 )
   {
    if (Ipv4ToInt(arg2,&(G.IPInterface))==-1)  /* On r�up�e l'adresse IP */
    {
     printf("Adresse Invalide !!!\n") ;
     exit(0) ;
    }
    else
        fprintf(stderr,"ip:%s\n",arg2) ;
    }
  else
  if (strcmp(arg1,"netmask")==0 )
      {
       if (Ipv4ToInt(arg2,&(G.NetworkMask))==-1)  /* On r�up�e le masque r�eau */
       {
        printf("Masque Invalide !!!\n") ;
        exit(0) ;
       }
       else
           fprintf(stderr,"Masque:%s\n",arg2) ;
      }
  else 
 if (strcmp(arg1,"gateway")==0 )
     {
      if (Ipv4ToInt(arg2,&(G.Gateway))==-1)  /* On r�up�e le masque r�eau */
      {
       fprintf(stderr,"Gateway Invalide !!!\n") ;
       exit(0) ;
      }
      else
       fprintf(stderr,"Gateway:%s\n",arg2) ;
     } 
  else
 if (strcmp(arg1,"dns")==0 )
    {
     if (Ipv4ToInt(arg2,&(G.IPDNS))==-1)  /* On r�up�e le masque r�eau */
     {
      fprintf(stderr,"Adresse Serveur dns Invalide:%s \n",arg2) ;
      exit(0) ;
     }
    }
 else
 if (strcmp(arg1,"ports")==0 )
    {
   	bzero(arg1,sizeof(arg1));
   	bzero(arg2,sizeof(arg2));
   	bzero(arg3,sizeof(arg3));
   	bzero(arg4,sizeof(arg4));
 	sscanf(Buffer,"%s %s %s %s %s\n",arg0,arg1,arg2,arg3,arg4) ;
     G.PortApplication = atoi(arg1) ;
     G.PortRequeteDNS = atoi(arg2 ) ;
     if (strcmp(arg3,"UDP")==0)
	 G.Protocole = UDP ;
     else
         if (strcmp(arg3,"TCP")==0)
	     G.Protocole = TCP ;
	 else
	     {
		    fprintf(stderr,"Choix non valable !!!\n") ;
		    exit(0) ;
	     }
     }
 else
 if (Blanc1013(arg1)) fprintf(stderr,"Ligne vide \n" ) ;
    else
       {
        fprintf(stderr,"Erreur de syntaxe \n") ;
        exit(0) ;
       }
 fgets(Buffer,sizeof Buffer,G.FConfig ) ;
}
 /* Vérification des paramètres */
 if ( Liaison == 0 )
     {
      printf("Pas de connexion définie \n") ;
      exit(0) ;
     }
 if ( G.IPInterface == 0 )
     {
      printf("Pas de connexion définie \n") ;
      exit(0) ;
     }
 if ( G.NetworkMask == 0 )
     {
      printf("Pas de masque définit \n") ;
      exit(0) ;
     }
 if ( G.Gateway == 0 )
     {
      printf("Pas de masque définit \n") ;
      exit(0) ;
     }
 if (  G.IPDNS == 0 )
     {
      printf("Pas de masque définit \n") ;
      exit(0) ;
     }

 fprintf(stderr,"******************************************\n") ;
 /* Phys[Liaison] = TPhys ; */
 G.CacheDNS = InitialiseCacheDNS(100) ;
 CoucheApplication(MENU,NULL,0,0,&bidon,&bidon,&bidon,&bidon,&G) ;
 HandleL[0] = 1 ;
 HandleL[Liaison] = 1 ;
 CoucheLiaison(HandleL,&TPhys,&G) ;
}

