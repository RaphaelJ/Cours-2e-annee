/*---------------------------------------------------------------
   Vanstapel Herman
   cphexser4\cli.c

------------------------------------------------------------------*/
#include <stdio.h>

#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "../evtmlib/evtmlib.h"


void main(int argc, char *argv[])
{
 int rc ;
 char *message ;
 char   Buffer[500] ;
 int	tm  ;
 int HLs[100] ;
 int HEs[100] ;
 struct ListeTimer *plt=NULL ;
 int evenement ;
 int HE ;
 int Connexion ;
 struct Physique L ;
 struct gEvenement gEv ;

 bzero(&L,sizeof(struct Physique))  ;
 bzero(&gEv,sizeof(struct gEvenement)) ;

 bzero(HLs,sizeof(HLs) );
 bzero(HEs,sizeof(HEs) );

 if (argc!=5)
 {
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 Connexion = CreerConnexion(&L,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) ;
 if ( rc == -1 )
    perror("CreerLiaison:") ;
 else
    fprintf(stderr,"Liaison Cree\n") ;

 HLs[Connexion]=1 ;
 HLs[0] = 1 ;

 rc = PrepareEvenement(&gEv,HLs,HEs,100,0,200000) ;
 if ( rc==-1)
    perror("PrepareEvenement") ; 

 while(1)
 {
  printf (" Pressez la touche 1 (enter ) pour envoyer msg \n" ) ;
  rc = AttendreEvenementtm(&gEv,&evenement,&HE,&plt) ;
  if ( rc == -1 )
     fprintf(stderr,"Erreur d'attendreEvenement\n") ;
  if ( evenement == 0 )
     {
      char Buffer[100] ;
      fgets(Buffer,sizeof Buffer,stdin) ;
      if ( Buffer[0] == '1' )
         {
          message = "Ceci est un test" ;
          rc = VersCouchePhysique(&L,message,strlen(message)+1 ) ;
         if ( rc == -1 )
             perror("VersCouchePhysique") ;
         else
           {
            fprintf(stderr,"Envoi de %d bytes\n",rc ) ;
            plt = StopTimer(1,plt) ;
            plt = StartTimer(1,4000,plt) ;
            AfficheTimer(plt) ; 
           }
         }
      sleep(2) ;
     }
  if ( evenement == Connexion  )
  {
  plt = StopTimer(1,plt ) ; 
  tm =  sizeof(Buffer) ;
  rc = OrigineCouchePhysique(&L,Buffer,&tm) ;
  if ( rc == -1 )
    perror("OrigineCouchePhysique") ;
  else
  {
    printf("Reception de %d bytes %s\n",rc,Buffer ) ;
    exit(0) ;
  }
  }
  if ( evenement >= TIMEOUT )
  {
   printf("TIMEOUT !!!!!  \n") ;
   sleep(2) ;
   /*   Reecrire la trame        */

   message = "Ceci est un test" ;
   rc = VersCouchePhysique(&L,message,strlen(message)+1 ) ;
   if ( rc == -1 )
      perror("VersCouchePhysique") ;
   else
      fprintf(stderr,"TIMEOUT:Envoi de %d bytes\n",rc ) ;
  
   plt = StopTimer (1,plt) ;
   plt = StartTimer(1,4000,plt) ;
  }
 }
}
