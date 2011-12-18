/*-------------------------------------------------------------------------------------------------------------------------------------
 -------------------------------------------------------------------
 Vanstapel Herman EPL

 L'objectif de ce programme est de construire un routeur

 version 24 -3 - 2006 
 Utilisation d'une trame.
---------------------------------------------------------------------
 C'est la couche liaison
---------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "../protocol/protocol.h"
#include "../filterlib/filterlib.h"
#include "../interfaces/interfaces.h"

#define RECEPTION   6000
#define DECTOUCHE   6100
#define ENVOI	    6200
#define NEAN        6400
#define MENU        6500
#define IPSOURCE    6600
#define IPDEST      6700
#define ROUTAGE     6800
#define AFFICHAGE   6900

struct EntreeTableRoutage
{
 int Adresse ;
 int Ligne   ;
 int Gateway ;
 int Masque  ;
};

struct Global
{
 /* ParamÃ¨tres de gestion des connexions */
FILE * FConfig ;
int HandleL[100] ;
int HandleE[100] ;
struct gEvenement gEv ; 
/*------- La table de routage ---------------------------------------*/
int NbrEntrees ;
struct EntreeTableRoutage TableRoutage[1000] ; 
int NbrLignes ;
/*------- La table de filtrage --------------------------------------*/
int NbrRegles ;
struct Regle TableFiltrage[1000] ;
/*------- gestion des interfaces ------------------------------------*/
char 	CurrentInterface[TAILLENOMINTERFACE] ;
struct Interface *pI ;
} ;


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

void AjoutEntreeTableRoutage(struct EntreeTableRoutage TableRoutage[],int Adresse, int Ligne, int Gateway, int Masque,int *NbrEntrees)
{
 int i ;
 i = *NbrEntrees ;
 TableRoutage[i].Adresse= Adresse ; 
 TableRoutage[i].Ligne  = Ligne ; 
 TableRoutage[i].Gateway= Gateway ;
 TableRoutage[i].Masque = Masque ;
 (*NbrEntrees)++ ;
}

void RemplaceEntreeTableRoutage(struct EntreeTableRoutage TableRoutage[],int Adresse, int Ligne, int Gateway, int Masque,int i)
{
 TableRoutage[i].Adresse= Adresse ; 
 TableRoutage[i].Ligne  = Ligne ; 
 TableRoutage[i].Gateway= Gateway ;
 TableRoutage[i].Masque = Masque ;
}

/*------------  Moteur de commande ----------------------------------*/

int interface(char *Nom,struct Global *g)
{
 struct Interface *pI ;
 bzero(g->CurrentInterface,sizeof(g->CurrentInterface)) ;
 strncpy(g->CurrentInterface,Nom,sizeof(g->CurrentInterface)) ; 
 
 pI=RechercheInterfaceNom(g->CurrentInterface,g->pI) ;
 if (pI == NULL )
    {
      fprintf(stderr,"connexion: %s n existe pas \n",g->CurrentInterface) ;
      /* AfficheInterfaces(g->pI) ; */
      g->pI = AjouteInterface(g->CurrentInterface,g->pI) ;
      /* AfficheInterfaces(g->pI) ; */
      /* On recherche interface pour la modifier */
      pI = RechercheInterfaceNom(g->CurrentInterface,g->pI) ;
      (g->NbrLignes)++ ;
      fprintf(stderr,"L interface est %s et ligne est %d \n",Nom,g->NbrLignes) ;
      ModifieLigne( g->NbrLignes,pI ) ;
      AfficheInterfaces(g->pI) ;
      return 1 ;
    }
 else
   {
     fprintf(stderr,"L'interface existe dÃ©jÃ  \n") ;	
     return 0 ;
   }
}

int connexion(char *Buffer,struct Global *g)
{
   int rc ;
   int Liaison ;
   struct Interface *pI ;
   struct Physique *TPhys ;
   char arg0[80],arg1[80],arg2[80],arg3[80],arg4[80] ;

  fprintf(stderr,"Entree connexion \n") ;

   TPhys = malloc( sizeof(struct Physique) ) ;
   if ( TPhys == NULL ) 
    {
     fprintf(stderr,"Plus de mï¿½oire \n") ;
    };
   bzero(arg0,sizeof(arg0));
   bzero(arg1,sizeof(arg1));
   bzero(arg2,sizeof(arg2));
   bzero(arg3,sizeof(arg3));
   sscanf(Buffer,"%s %s %s %s %s\n",arg0,arg1,arg2,arg3,arg4) ;

   Liaison = CreerConnexion(TPhys,arg1,atoi(arg2),arg3,atoi(arg4)) ;
   if ( Liaison == -1)
      {
       fprintf(stderr,"Creation de la liaison impossible !!!!!!\n\n") ;
       return 0;
      }
   else
     fprintf(stderr,"La Liaison est %d et",Liaison) ;
   g->HandleL[Liaison]=1  ; /* Pour gerer l'evenement */
   pI=RechercheInterfaceNom(g->CurrentInterface,g->pI) ;
   if (pI == NULL )
      {
       fprintf(stderr,"connexion: %s n existe pas \n",g->CurrentInterface) ;
	return 0 ;
      }
   else
      {
	ModifieLiaison(Liaison,pI) ;
        ModifiePhys(TPhys,pI) ;
      }
 AfficheInterfaces(g->pI) ;
 fprintf(stderr,"Sortie connexion \n") ;	
 return 1 ;
}

int ip_address(char *Buffer,struct Global *g)
{
 int rc ;
 char arg0[80],arg0B[80],LIP[80],arg2[80],arg3[80],arg4[80] ;
 struct Interface *pI ;
 int UneIP ;
 fprintf(stderr,"Entree IP adress\n") ;
 AfficheInterfaces(g->pI) ;
 bzero(arg0,sizeof(arg0));
 bzero(LIP,sizeof(LIP));
 sscanf(Buffer,"%s %s %s\n",arg0,arg0B,LIP) ;
/*----------- arg1 est l'adresse IP ------------------------*/
 pI = RechercheInterfaceNom(g->CurrentInterface,g->pI) ;
 if ( pI == NULL )
    {
     fprintf(stderr,"Le nom de l'interface n'existe pas %s \n",g->CurrentInterface) ;
     return (0) ;
    } 
 if (Ipv4ToInt(LIP,&UneIP)!=-1) /* IP ligne valide ? */
   {
    int ETR ;
    int Ligne ;
    char Buf[30] ;
    Ipv4ToS(UneIP,Buf) ;
    Ligne = ObtenirLigne(pI) ;
    fprintf(stderr,"L'adresse Pour la ligne %d est la suivante %s.\n",Ligne, Buf  ) ;
    ETR = ObtenirEntreeTableRoutage(pI) ;
    if (ETR ==-1)
       {
        /* première fois qu on assigne une ip £*/
        AjoutEntreeTableRoutage( g->TableRoutage,UneIP & 0xFFFFFF00 , Ligne, UneIP ,0xFFFFFF00, &g->NbrEntrees) ;
        ModifieEntreeTableRoutage(g->NbrEntrees-1,pI) ;
       }
    else 
       {
        fprintf(stderr,"Modiication de l entrée de la table de routage \n") ;
        RemplaceEntreeTableRoutage( g->TableRoutage,UneIP & 0xFFFFFF00 , Ligne, UneIP ,0xFFFFFF00, ETR) ;
       }
    ModifieIP(UneIP,pI) ;
    AfficheInterfaces(g->pI) ;
   }
 else
    {
     fprintf(stderr,"L'adresse %s est mauvaise.",LIP) ;
     return 0 ;
    }
 AfficheInterfaces(g->pI) ;
 fprintf(stderr,"Sortie Ip_adress\n") ;
 return 1 ;
}

int ip_route(char *Buffer,struct Global *g)
{
     int Adresse ;
     int Ligne ;
     int Gateway ;
     int Masque ;
     int rc ;
     struct Interface *pI ;
     char arg0[80],arg0B[80],arg1[80],arg2[80],arg3[80],arg4[80] ;

     fprintf(stderr,"Entree ip_route\n") ;

     bzero(arg0,sizeof(arg0));
     bzero(arg1,sizeof(arg1));
     bzero(arg2,sizeof(arg0));
     bzero(arg3,sizeof(arg1));
     bzero(arg4,sizeof(arg1));
     /* Syntaxe 10.1.2.0 255.255.255.0 etho  */
     sscanf(Buffer,"%s %s %s %s %s %s\n",arg0,arg0B,arg1,arg2,arg3,arg4) ;
     if (Ipv4ToInt(arg1,&Adresse)!=-1) /* IP ligne valide ? */
     {
      char Buf[30] ;
      Ipv4ToS(Adresse,Buf) ;
      fprintf(stderr,"L'adresse est la suivante %s.\n", Buf  ) ;
     }
     else
         {
          fprintf(stderr,"Adresse IP 1  non valide \n") ;
          return(0) ;
         }
     if (Ipv4ToInt(arg2,&Masque)!=-1) /* IP ligne valide ? */
         {
          char Buf[30] ;
          Ipv4ToS(Masque,Buf) ;
          fprintf(stderr,"L'adresse est la suivante %s.\n", Buf  ) ;
          }
     else
         {
          fprintf(stderr,"Masque IP  non valide \n") ;
          return(0) ;
         }
     /*  RechercheInterface(arg3,g->NomInterface ,g->NbrLignes ,&Ligne ) */
     pI = RechercheInterfaceNom(arg3,g->pI) ;
     
     if ( pI!=NULL )
        {
         Ligne = ObtenirLigne(pI) ;
         printf("Interface valide %d\n",Ligne) ;
         
        }
     else
         {
          printf("Interface non valide \n") ;
          return(0) ;
         }
    if (Ipv4ToInt(arg4,&Gateway)!=-1) /* IP ligne valide ? */
         {
          char Buf[30] ;
          Ipv4ToS(Gateway,Buf) ;
          fprintf(stderr,"L'adresse est la suivante %s.\n", Buf  ) ;
          }
      else
         {
          fprintf(stderr,"Gateway non valide \n") ;
          return(0) ;
         }
     AjoutEntreeTableRoutage(g->TableRoutage,Adresse, Ligne,Gateway,Masque,& (g->NbrEntrees)) ;
     return(1) ;
}

void AfficheTableRoutage(struct EntreeTableRoutage  TableRoutage[],int NbrEntrees )
{
 int i = 0 ;
 while(i < NbrEntrees )
 {
  char Buffer[30]  ;
  char Buffer2[30] ;
  char Buffer3[30] ;
  
  Ipv4ToS(TableRoutage[i].Adresse,Buffer) ;
  Ipv4ToS(TableRoutage[i].Gateway,Buffer2) ;
  Ipv4ToS(TableRoutage[i].Masque,Buffer3) ;
  printf("Adresse reseau %s:Interface %d gateway %s masque %s \n",Buffer,TableRoutage[i].Ligne,Buffer2,Buffer3) ;
  i++ ;
 }
 return ;
}

int show(char *Buffer,struct Global *g )
{
 int rc ;
 char arg0[80],arg1[80],arg2[80],arg3[80],arg4[80] ;
  bzero(arg1,sizeof(arg1));
  bzero(arg2,sizeof(arg2));
  bzero(arg3,sizeof(arg3));
  sscanf(Buffer,"%s %s %s\n",arg1,arg2,arg3 ) ;
 if (!strcmp(arg2,"ip") && ( !strcmp(arg3,"route")))
    {
      rc = 1 ;
      AfficheTableRoutage(g->TableRoutage,g->NbrEntrees)  ;
    }
 else 
 if (!strcmp(arg2,"interfaces"))
    {
      rc = 1 ;
      AfficheInterfaces(g->pI );
    }
else
if  ( strcmp(arg2,"filter") == 0 )
       {
         AffichageTableFiltrage(g->TableFiltrage,g->NbrRegles) ;
         return(NEAN) ;
       }
else
  {
    fprintf(stderr,"Erreur de syntaxe arg 2 ou arg3 \n" ) ;
    rc = 0 ;
   }
return (rc) ;
}

 void AfficheAide() 
{
  printf("interface eth0 \n") ;
  printf("connexion localhost	11254	localhost  11000 \n") ;
  printf("ip address 111.112.113.254 \n") ;
  printf(" show ip route \n") ;
  printf(" show interfaces\n") ;
  printf(" show filter\n") ;
}

int ip(char * Buffer,struct Global *g )
{
 int rc ;
 char arg0[80],arg1[80],arg2[80],arg3[80],arg4[80] ;

  bzero(arg1,sizeof(arg1));
  bzero(arg2,sizeof(arg2));
  bzero(arg3,sizeof(arg3));
  sscanf(Buffer,"%s %s %s\n",arg1,arg2,arg3 ) ;

 if (!strcmp(arg2,"address") )
        rc = ip_address(Buffer,g) ;
  else if (!strcmp(arg2,"route") )
        rc = ip_route( Buffer, g) ;
else
  {
    fprintf(stderr,"Erreur de syntaxe  arg 2 ou arg3 \n" ) ;
    printf("Erreur de syntaxe arg 2 ou arg3\n") ;
    rc = 0 ;
   }
return (rc) ;
}

int Interpreteur(char *Buffer, struct Global *g )
{ 
  /* definir arg1 , arg2 */
  char arg0[80],arg1[80],arg2[80],arg3[80],arg4[80] ;
  int rc ;
  bzero(arg1,sizeof(arg1));
  bzero(arg2,sizeof(arg2));
  bzero(arg3,sizeof(arg3));

  fprintf(stderr,"La chaine a interpreter est %s \n",Buffer ) ;
  sscanf(Buffer,"%s %s %s\n",arg1,arg2,arg3 ) ;
  if (strcmp(arg1,"interface")==0)
      rc = interface(arg2,g) ;
  else if (strcmp(arg1,"connexion")==0)
        rc = connexion(Buffer,g) ;
  else if ( !strcmp(arg1,"ip"))
        rc = ip(Buffer,g) ;
  else if (!strcmp(arg1,"show"))
	rc = show ( Buffer,g ) ;
  else if ( ( strcmp(arg1,"load") == 0 ) && ( strcmp(arg2,"filter") == 0 ))
       {
        LectureTableFiltrage(arg3,g->TableFiltrage,&(g->NbrRegles),g->NbrLignes) ;
        return(NEAN) ;
       }
  else if ( strcmp(arg1,"help")==0)
       AfficheAide() ;
  else if ( strcmp(arg1,"exit")==0 ) 
       exit(0) ;
  else if (Blanc1013(arg1)) fprintf(stderr,"Ligne vide \n" ) ;
  else
      {
       printf("Erreur de syntaxe \n") ;
       return(0) ;
       }
  return(rc) ;
}


char *SaisieChaine(char* Invite,char *chaine,int tc )
{
 printf("%s",Invite) ;
 fgets(chaine,tc,stdin) ;
 chaine[strlen(chaine)-1] = 0 ;
 return chaine ;
}

int CoucheApplication(int ev,char Buffer[],int tBuffer,struct Global *g)
{
 static char BufferR[1000] [TBUFFERPAQUET] ; /* A suprimer */
 static int courant ;
 static int prochainalire ;
 char Chaine[200] ;
 int choix ;
 int Nombre ;

 fprintf(stderr,"Application\n");
 switch(ev)
 {
  case RECEPTION:  /* Code inutile a suprimer  */
	  printf("le Routeur a recu %s \n",Buffer) ;
          strcpy(BufferR[prochainalire],Buffer) ;
          prochainalire++ ;
          return(NEAN) ;
  default:
         return(NEAN) ;
  }
}

int Routage(struct EntreeTableRoutage TableRoutage[],struct Interface *pI,int NbrEntrees,int IPDestination,int *MacD)
{
 int j = 0 ;
 int val ;
 while( j < NbrEntrees)
 {
  val = IPDestination& TableRoutage[j].Masque ;   /*Ici on applique le masque 255.255.255.0 */
 /*fprintf(stderr,"Routage:Valeur %d \n",val) ;*/
 if ( val==TableRoutage[j].Adresse) /* Le gsecond segment */
    {
     struct Interface *pUneI ; 
     pUneI = RechercheInterfaceLigne(TableRoutage[j].Ligne,pI) ;
     if ( pUneI == NULL )
        {
         fprintf(stderr,"Reseau:Routage pas d'interface pour cette ligne\n") ;
	 exit(0) ;
        }
     if (ObtenirIP(pUneI)==TableRoutage[j].Gateway)
        *MacD = IPDestination ;  /* La destination est l'interface reseau associee a l'IP */
     else
       *MacD = TableRoutage[j].Gateway ; /* La destination est un gatewat */
     return TableRoutage[j].Ligne ;
    } 
 j++ ;
 }
 printf("Reseau:Adresse non routable !!!!\n") ;
 return(0) ;
}

int CoucheReseau(int ev,char Buffer[],int tBuffer,int *Ligne,struct Global *g,int *MacD)
{
 static int Numero ;
        int res ;
 struct Paquet  *pp ;
 struct Segment *ps ;
 int	LigneEntree ;
 int    Regle ;
 static int IPS ;
 static int IPD ;
 char Buffer1[30], Buffer2[30] ;
 struct Interface *pUneI ;

 fprintf(stderr,"Reseau:Debut\n") ;
 switch(ev)
 {
  case MENU:
  case RECEPTION:
        LigneEntree = *Ligne ;
        fprintf(stderr,"Ligne Entree %d \n",LigneEntree) ;
        pp = (struct Paquet*) Buffer ;
        Ipv4ToS(pp->IPSource,Buffer1 ) ;
	Ipv4ToS(pp->IPDestination,Buffer2 ) ;
        fprintf(stderr,"Reseau:%s %s %d\n",Buffer1,Buffer2,
                pp->Numero ) ;
	/* *Ligne contient l'interface par laquelle on rentre */
        pUneI = RechercheInterfaceLigne(*Ligne,g->pI) ;
        if ( pUneI == NULL )
           {
            fprintf(stderr,"Pas d'interface pour la ligne %d!",LigneEntree) ;
            exit(0) ;
           }
        
         if (FiltragePaquet(LigneEntree,g->TableFiltrage,g->NbrRegles,pp,&Regle))
	    {
	         res = NEAN ;
		 fprintf(stderr,"Filtrage :Reseau Regle: %d DROP Ligne entree:%d ", Regle ,LigneEntree ) ;
	         fprintf(stderr,"IPS: %s IPD: %s ",Buffer1,Buffer2 ) ;
	         ps = ( struct Segment * ) pp->Buffer ;
	         fprintf(stderr,"Port Source: %d Port Destination: %d ",ps->PortSource ,ps->PortDestination ) ;
	         fprintf(stderr,"\n") ;
             }
          else
	     {
              /* Il faut traiter les paquets non filtré */
               /* Chercher une interface pingée         */
               pUneI = g->pI ;
               while( pUneI)
               {
                fprintf(stderr,"Reseau: Recherche d'interface pingee\n");
                if  ( pp->IPDestination == ObtenirIP(pUneI))
                  {
                   /* traiter ici le ping */
                   int *Code ;
                   Code =(int*)  pp->Buffer ;
                   if ( *Code == ICMPECHO )
                      {
                       int tempo ;
                       fprintf(stderr,"Reception ICMP ECHO et generation ICMP Response \n") ;
                       tempo = pp->IPSource ;
                       pp->IPSource = pp->IPDestination ;
                       pp->IPDestination = tempo ;
                       *Code = ICMPRESPONSE ;
                       break ;
                      }  
                    }
                  pUneI = InterfaceSuivante(pUneI) ;
                 }
                 *Ligne = Routage(g->TableRoutage,g->pI,g->NbrEntrees,pp->IPDestination,MacD) ;
	        // A verifier seule la ligne de sortie est bonne Paramêtre Regle , ligne entrée pas bon 
		fprintf(stderr,"Routqge Regle: %d  ACCEPT Lin %d Lout: %d ",Regle, LigneEntree,*Ligne ) ;
	         fprintf(stderr,"IPS: %s IPD: %s ",Buffer1,Buffer2 ) ;
	         ps = ( struct Segment * ) pp->Buffer ;
	         fprintf(stderr,"Port Source: %d Port Destination: %d ",ps->PortSource ,ps->PortDestination ) ;
	         fprintf(stderr,"\n") ;
                 if (*Ligne) /* Une ligne valide est fournie */
                    res = ROUTAGE ;
                 else
                    res = NEAN ;
	     }
        break ;
  default:
       res = NEAN ;
       break ;
  }
 fprintf(stderr,"Reseau:Fin\n") ;
 return res ;
}

void CoucheLiaison(struct Global *g)
{
 int rc ;
  /* static char Buffer[TBUFFERTRAME] ; */
 
 static struct Trame UneTrame ;
 static int Numero = 0 ;
 int NL ;
 int EHL,EHE ;
 int MacD ;
 
// Ancienne Position de PrepareEvenement
 
 while(1)
 {
  rc = PrepareEvenement( &(g->gEv),g->HandleL,g->HandleE,100,300,0 ) ;
  /* on s'endort en attendant que quelque chose se produise */
  printf(">>>") ; fflush(stdout) ;
  rc = AttendreEvenement(&(g->gEv),&EHL,&EHE) ;
  printf("Liaison:EHL %d\n",EHL) ;
  if ( rc == 0 )
     printf("Liaison:Timeout !!!!!\n") ;
  else
  if ( rc == -1 )
     {
      printf("Liaison:Erreur attendre Evenement !!!\n") ;
      exit(0) ;
     }
  else
     if ( EHL == 0 ) /* Frappe du clavier */
     {
             char Chaine[200] ;
             fgets(Chaine,sizeof Chaine,stdin ) ;
             Interpreteur(Chaine,g) ;
     }
     else
        if ( EHL != 0 ) /* evenement reseau */
        {
	 
         int tm=sizeof(UneTrame)  ;
	 struct Interface *pUneI  ; 

	 pUneI=RechercheInterfaceDesc( EHL,g->pI) ;
         if ( pUneI == NULL )
            	{
             	 fprintf(stderr,"Liaison: Pas d'interface pour evenement %d\n",EHL ) ;
		 exit(0) ;
		}
	 else
	    fprintf(stderr,"l'interface a ete trouvee \n") ;
         rc = OrigineCouchePhysique(ObtenirPhys(pUneI),&UneTrame,&tm) ;
         /* memcpy(Buffer,UneTrame.Buffer,sizeof Buffer) ; */
         fprintf(stderr,"Liaison:%d bytes lus\n",rc) ;
         /* Pour simplifier le code : la mac = IP */
         NL = ObtenirLigne(pUneI) ;
	 
	 if ( UneTrame.MacDestination.Numero == ObtenirIP(pUneI) )
	 {	 
          	rc = CoucheReseau(RECEPTION,UneTrame.Buffer,sizeof (UneTrame.Buffer),&NL,g,&MacD) ;  
	 }		
	 else
            {
             char TamponSource[30] ;
             char TamponDest[30] ;

            bzero(TamponDest,sizeof(TamponDest)) ;
            bzero(TamponSource,sizeof(TamponSource)) ;
            Ipv4ToS(UneTrame.MacSource.Numero,TamponSource) ;
            Ipv4ToS(UneTrame.MacDestination.Numero,TamponDest) ;
             
            fprintf(stderr,"Liaison:La mac recue ne correspond pas  Source FF:%s , dest FF:%s  \n",TamponSource ,TamponDest) ;
            /* Ajouter ici La mac source */
            fprintf(stderr," Le paramêtre gateway de l'émetteur est sans doute faux \n") ;
           }		 
        }
     else
        printf("Non connu !!!!!\n") ;
  /* faut il emettre une trame sur une ligne */
  if ( rc == ROUTAGE || rc==ENVOI )
     {
      char Buffer[20] ;
	struct Interface *pUneI ; 
     
       bzero(Buffer,sizeof(Buffer)) ;
      /*---- On rï¿½crit vers l'interface correspondante ----*/
      UneTrame.MacDestination.Constructeur = 0xFF ;
      UneTrame.MacDestination.Numero = MacD ; /* je n'ai pas implementï¿½arp */
      Ipv4ToS(UneTrame.MacDestination.Numero,Buffer ) ;
      fprintf(stderr,"Liaison;FF:%s\n",Buffer);
      fprintf(stderr,"Liaison: La Ligne de Sorite  est %d \n",NL ) ;
      pUneI = RechercheInterfaceLigne(NL,g->pI) ;
      if ( pUneI == NULL )
          {
           fprintf(stderr,"Liaison: Cette ligne n'existe pas !!!\n") ;
	   exit(0) ;
          }
      rc = VersCouchePhysique(ObtenirPhys(pUneI),&UneTrame,sizeof(UneTrame)) ;
      if (rc == -1 )
          perror("Motif:") ;
      else
          fprintf(stderr,"Liaison: %d bytes ï¿½rits vers FF:%s\n",rc,Buffer) ;
     }
 }
}


int main(int argc,char *argv[])
{
 
 static struct Global g ; /* imperatif que ce soit vide */
 int bidon ;
 int rc ;
 int ligne ;
 char NomFichier[80] ;
 char Buffer[200] ;
 

 int Liaison ;
 int i=1;

 if (argc<2)
 {
    printf("routeur Fichierconfig\n") ;
    exit(1) ;
 }

 g.FConfig = fopen( argv[1],"r+") ;
 if ( g.FConfig == NULL )
    {
     printf("Fichier non ouvert \n") ;
     exit(0) ;
    }
 else
    printf("Ouverture de %s \n",argv[1]) ;

 setbuf(g.FConfig,NULL) ; 

 /*-------------------------------------*/
 /* Preparation du clavier              */
 g.HandleL[0] = 1 ;
 g.NbrLignes= 0 ; /* Pas de ligne au dÃ©part */
 fprintf(stderr,"***********************************\n") ;
 fgets(Buffer,sizeof Buffer,g.FConfig ) ;
 ligne = 0 ;
 while (!feof( g.FConfig ))
{
 ligne ++ ;
 fprintf(stderr,"Je compile ligne %d \n",ligne ) ;
 if (!Interpreteur(Buffer,&g))
    exit(0) ; 
 fgets(Buffer,sizeof Buffer,g.FConfig ) ;
}
 fprintf(stderr,"***********************************\n") ;
 fprintf(stderr," ENTREES %d \n",g.NbrEntrees ) ;
 CoucheLiaison(&g) ;
}

