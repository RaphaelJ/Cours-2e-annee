/*---------------------------------------------------------------
   Vanstapel Herman 2004
   Cpheser4me\cli.c

------------------------------------------------------------------*/
#include <stdio.h>

#include "../evlib/evlib.h"
#include "../reslib/reslib.h"
#include "../physlib/physlib.h"
#include "../evtmlib/evtmlib.h"
#include "message.h"


struct Global {
 struct Physique *L ;
 struct ListeTimer *PLT ;
 struct Message Msg ;
 int Etat ;
};

#define RIEN  1
#define ENVOI 2

int Send(struct Global *pG,void* Message,int TM,int NumTimer,int Delais)
{
 int rc ;

 rc = VersCouchePhysique(pG->L,Message,TM) ;
 if ( rc == -1 )
    {
     perror("VersCouchePhysique") ;
     return(rc ) ;
    }
 else
   printf("Envoi de %d bytes\n",rc ) ;

 pG->PLT = StopTimer(NumTimer,pG->PLT) ;
 pG->PLT = StartTimer(NumTimer,Delais,pG->PLT) ;
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
 printf("1 Calcul d'une somme  \n") ;
 printf("-----------------------\n") ;
}

int SaiSieMessage(struct Message *msg)
{
 char Buffer[100] ;
 printf("Entrez entier1:") ;
 fgets(Buffer,sizeof Buffer,stdin) ;
 Buffer[strlen(Buffer)] = 0  ;
 msg->Entier1 = atoi(Buffer) ;
 printf("Entrez entier2:") ;
 fgets(Buffer,sizeof Buffer,stdin) ;
 Buffer[strlen(Buffer)] = 0 ;
 msg->Entier2 = atoi(Buffer) ;
 printf("Entrez un commentaire:") ;
 fgets(msg->Commentaire,sizeof (msg->Commentaire),stdin) ;
}

int AfficheMessage(struct Message *msg)
{
 printf("Le resultat de %d + %d est %d \n",msg->Entier1,msg->Entier2,msg->Resultat ) ;
}

void TraitementTouche(char touche,char*Message,struct Global *pG )
{
 int rc ;
 if ( touche == '1')
    switch(pG->Etat)
    {
    case RIEN :
         SaiSieMessage(&(pG->Msg)) ;
         rc =Send(pG,&(pG->Msg),sizeof(struct Message),1,4000)  ;
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
 struct Message UnMsg ;
 int	tm  ;

 tm = sizeof(struct Message) ;
 switch (pG->Etat )
 {
  int Entier1 ;
  int Entier2 ;
  int Resultat ;
  char Commentaire[200] ;

  case ENVOI:
     rc = Receive(pG,&UnMsg,&tm) ;
     AfficheMessage(&UnMsg) ;
     pG->Etat = RIEN ;
     break ;
  case RIEN:
     printf("Je n'ai rien demande\n");
     /* Purger neanmoins le Buffer */
     rc = Receive(pG,&UnMsg,&tm) ;
     break ;
  default:
      printf("Etat inconnu :\n") ;
      exit(0) ;
      break ;
 }
}


int main(int argc, char *argv[])
{
 struct Physique Phys  ;
 struct gEvenement gEv ;
 int HLs[100] ;
 int HEs[100] ;
 int evenement ;
 int Connexion ;
 int rc ;
 char   Buffunctionfer[500] ;
 int	tm  ;
 int HE ;
 struct Global G;
 char *message ;

 /*Initialisation des structures globales */

 bzero(&Phys, sizeof ( struct Physique )) ;
 bzero(&gEv,  sizeof ( struct gEvenement )) ;
 bzero(HLs, sizeof HLs ) ;
 bzero(HEs, sizeof HEs ) ;

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
    printf("Liaison Cree \n") ;

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
      printf("Touche pressee !!!!!\n")  ;

      Key = Buffer[0] ;
      TraitementTouche(Key,message,&G ) ;
      sleep(2) ;
     }
  if ( evenement == Connexion  )
      TraitementReception(&G);
  if ( evenement >= TIMEOUT )
  {
     rc =Send(&G,&G.Msg,sizeof(struct Message),1,4000) ;
     G.Etat = ENVOI ;
  }
 }
}
