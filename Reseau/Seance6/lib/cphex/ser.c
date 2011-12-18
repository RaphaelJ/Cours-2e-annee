/*--------------------------------------
  cphex\ser.c 
----------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../physlib/physlib.h"

int main(int argc,char *argv[])
{
 int rc ;
 struct Physique L ; 
 char message[100] ;
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
 tm = sizeof(message) ;
 rc = OrigineCouchePhysique(&L,message,&tm ) ;
 if ( rc == -1 )
    perror("OrigineCouchePhysique") ;
 else
   fprintf(stderr,"bytes:%d:%s\n",rc,message ) ;
}
