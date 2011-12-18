/*-------------------------------------------------------------------------
  cphexS\ser.c 
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../physlib/physlib.h"
#include "structure.h"

int main(int argc,char *argv[])
{
 int rc ;
 struct Physique L ;
 struct Data UnData ; 
 int tm ;

 bzero(&L,sizeof(struct Physique)) ;
 printf("Ceci est le serveur\n") ;
 if ( argc!=5)
 {
  printf("ser ser port cli port\n") ;
  exit(1) ;
 }
 rc = CreerConnexion(&L,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) ;
 if ( rc == -1 )
    perror("CreerLiaison:") ;
 else
    printf("Liaison Cree \n") ;
 tm = sizeof(struct Data) ;
 rc = OrigineCouchePhysique(&L,&UnData,&tm ) ;
 if ( rc == -1 )
    perror("OrigineCouchePhysique") ;
 else
   fprintf(stderr,"bytes:%d:%d:%s\n",rc,UnData.Valeur,UnData.message ) ;

  printf("UnData.Valeur= %d\n", UnData.Valeur) ;
  printf("UnData.message= %s\n",UnData.message) ;
}
