/*---------------------------------------------------------------
   Vanstapel Herman
   cphexser3\cli.c

------------------------------------------------------------------*/
#include <stdio.h>

#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "../evtmlib/evtmlib.h"
#include <string.h>

static struct gEvenement gEv ;

int main(int argc, char *argv[])
{
 int rc ;
 char *message ;
 struct Physique L ;
 struct gEvenement gEv ;

 char   Buffer[500] ;
 int	tm  ;
 static int HLs[100] ;
 static int HEs[100] ;
 int evenement ;
 int HE ;
 int Connexion ;

 bzero(&L,sizeof( struct Physique )) ;
 bzero(&gEv,sizeof( struct gEvenement )) ;

 if (argc!=5)
 {
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 Connexion = CreerConnexion(&L,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) ;
 if ( Connexion == -1 )
    perror("CreerLiaison:") ;
 else
    fprintf(stderr,"Liaison Cree\n") ;

 HLs[Connexion]=1 ;
 HLs[0] = 1 ;

 rc = PrepareEvenement(&gEv,HLs,HEs,100,300,0) ;
 if ( rc==-1)
    perror("PrepareEvenement") ; 

 
 
 while(1)
 {
  printf (" Pressez la touche 1 (enter ) pour envoyer msg \n" ) ;
  rc = AttendreEvenement(&gEv,&evenement,&HE) ;
  if ( rc == 0 )
     printf("timeout !!\n") ;
  if ( rc == -1 )
     printf("Erreur d'attendreEvenement\n") ;
  printf("Evenement %d \n",evenement) ;
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
            fprintf(stderr,"Envoi de %d bytes\n",rc ) ;
         }
      sleep(2) ;
     }
  if ( evenement == Connexion  )
  {
  tm = sizeof(Buffer ) ;
  rc = OrigineCouchePhysique(&L,Buffer,&tm) ;
  if ( rc == -1 )
    perror("OrigineCouchePhysique") ;
  else
  {
    fprintf(stderr,"Reception de %d bytes %s\n",rc,Buffer ) ;
    exit(0) ;
  }
  }
 }
}
