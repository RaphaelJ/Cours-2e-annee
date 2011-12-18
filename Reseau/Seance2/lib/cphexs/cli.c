/*-----------------------------------------------------------------
   Vanstapel Herman
   cphexS\cli.c
------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../physlib/physlib.h"
#include "structure.h"

int main(int argc, char *argv[])
{
 int rc ;
 struct Physique L ;
 struct Data UnData ;

 bzero(&L,sizeof(struct Physique)) ;
 if (argc!=5)
  
{
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 rc = CreerConnexion(&L,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) ;
 if ( rc == -1 )
    perror("CreerLiaison:") ;
 else
    fprintf(stderr,"Liaison Cree \n") ;

 UnData.Valeur = 1 ;
 strncpy(UnData.message,"Ceci est un test",sizeof(UnData.message)) ;
 rc = VersCouchePhysique(&L,&UnData,sizeof(struct Data)) ;
 if ( rc == -1 )
    perror("VersCouchePhysique") ;
 else
   fprintf(stderr,"Envoi de %d bytes\n",rc ) ;
}
