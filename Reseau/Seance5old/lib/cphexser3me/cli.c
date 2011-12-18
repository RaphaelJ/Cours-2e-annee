/*---------------------------------------------------------------
   Vanstapel Herman 2004
   C05\cli.c

------------------------------------------------------------------*/
#include <stdio.h>

#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "../evtmlib/evtmlib.h"

struct Global {
 struct Physique *L ;
 struct ListeTimer *PLT ;
 int Etat ;
};

#define RIEN  1
#define ENVOI 2

int Send(struct Global *pG,void* Message,int TM)
{
 int rc ;

 rc = VersCouchePhysique(pG->L,Message,strlen(Message)+1 ) ;
 if ( rc == -1 )
    {
     perror("VersCouchePhysique") ;
     return(rc ) ;
    }
 else
   printf("Envoi de %d bytes\n",rc ) ;

 pG->PLT = StopTimer(1,pG->PLT) ;
 pG->PLT = StartTimer(1,4000,pG->PLT) ;
 AfficheTimer(pG->PLT) ;
 return(rc) ;
}

int Receive(struct Global *pG,void* Message,int *TM)
{
 int rc ;

  pG->PLT = StopTimer(1,pG->PLT ) ;
  rc = OrigineCouchePhysique(pG->L,Message,TM) ;
  if ( rc == -1 )
     perror("OrigineCouchePhysique") ;
  else
 {
     int IPR,PORTD   ;
     char Buffer[30] ;
     IPR   = IPDistante (pG->L) ;
     PORTD = PortDistant(pG->L) ;
     Ipv4ToS(IPR, Buffer ) ;
     printf("Reception de %d bytes %s de %s : %d\n",rc,Message,Buffer,PORTD) ;
 }
 return(rc) ;
}

void AfficheMenu()
{
 printf("1 Envoi d'un message   \n") ;
 printf("-----------------------\n") ;
}


void TraitementTouche(char touche,char*Message,struct Global *pG )
{
 int rc ;
 if ( touche == '1')
    switch(pG->Etat)
    {
    case RIEN :
         rc =Send(pG,Message,strlen(Message)+1) ;
	 pG->Etat = ENVOI ;
	 break ;
    case ENVOI :
        printf("transaction enn cours \n") ;
	break ;
    default:
        printf("Etat inconnu :\n") ;
	exit(0) ;
	break ;
    }
 else
    AfficheMenu() ;
};


void TraitementReception(struct Global *pG )
{
 int rc ;
 char   Buffer[500] ;
 int	tm  ;

 tm = sizeof(Buffer) ;
 switch (pG->Etat )
 {
  case ENVOI:
     rc = Receive(pG,Buffer,&tm) ;
     pG->Etat = RIEN ;
     break ;
  case RIEN:
     printf("Je n'ai rien demandé\n");
     /* Purger néanmoins le Buffer */
     rc = Receive(pG,Buffer,&tm) ;
     break ;
  default:
      printf("Etat inconnu :\n") ;
      exit(0) ;
      break ;
 }
}


int main(int argc, char *argv[])
{
 static struct Physique Phys  ;
 static struct gEvenement gEv ;
 static int HLs[100] ;
 static int HEs[100] ;
 int evenement ;
 int Connexion ;
 int rc ;
 char   Buffunctionfer[500] ;
 int	tm  ;
 int HE ;
 struct Global G;
 char *message ;

 /*Initialisation des structures globales */

 G.L    = &Phys ;
 G.PLT  = NULL ;
 G.Etat = RIEN ;


 if (argc!=5)
 {
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 Connexion = CreerConnexion(G.L,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) ;
 if ( rc == -1 )
    perror("CreerLiaison:") ;
 else
    printf("Liaison Créé \n") ;

 HLs[Connexion]=1 ;
 HLs[0] = 1 ;

 rc = PrepareEvenement(&gEv,HLs,HEs,100,0,200000) ;
 if ( rc==-1)
    perror("PrepareEvenement") ;


 message = "Ceci est un test" ;

 AfficheMenu() ;
 while(1)
 {
  rc = AttendreEvenementtm(&gEv,&evenement,&HE,&(G.PLT)) ;
  if ( rc == -1 )
     printf("Erreur d'attendreEvenement\n") ;
  if ( evenement == 0 )
     {
      char Key ;
      char Buffer[100] ;
      fgets(Buffer,sizeof Buffer,stdin) ;
      printf("Touche pressée !!!!!\n")  ;

      Key = Buffer[0] ;
      TraitementTouche(Key,message,&G ) ;
      sleep(2) ;
     }
  if ( evenement == Connexion  )
      TraitementReception(&G);
  if ( evenement >= TIMEOUT )
  {
     rc =Send(&G,message,strlen(message)+1) ;
     G.Etat = ENVOI ;
  }
 }
}
