/*--------------------------------------
  C05\ser.c
----------------------------------------*/

#include <stdio.h>
#include "../physlib/physlib.h"

void main(int argc,char *argv[])
{
 int rc ;
 static  struct Physique L ; /* pour eviter un bug curieux !!!!!!!*/
 char message[100] ;
 int tm ;
 char Tampon[65000] ;

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
    printf("Liaison Créé \n") ;
 while(1 )
 {
  tm = 65000 ;
  rc = OrigineCouchePhysique(&L,Tampon,&tm ) ;
  if ( rc == -1 )
    perror("OrigineCouchePhysique") ;
  else
    printf("bytes:%d reçus  \n",rc ) ;
 }
}
