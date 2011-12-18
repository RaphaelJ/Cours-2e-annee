/*--------------------------------------
  cphexser\ser.c
----------------------------------------*/

#include <stdio.h>
#include "../physlib/physlib.h"

int main(int argc,char *argv[])
{
 int rc ;
 struct Physique L ; 
 char message[100] ;
 int tm ;
 char *Chaine ;

 bzero(&L,sizeof(struct Physique)) ;
 printf("Ceci est le serveur\n") ;
 if ( argc!=3)
 {
  printf("ser ser port \n") ;
  exit(1) ;
 }
 rc = CreerConnexion(&L,argv[1],atoi(argv[2]),NULL,0) ;
 if ( rc == -1 )
    perror("CreerLiaison:") ;
 else
    fprintf(stderr,"Liaison Cree \n") ;
 while(1)
 {
 tm = sizeof(message) ;
 rc = OrigineCouchePhysique(&L,message,&tm ) ;
 if ( rc == -1 )
   {
    perror("OrigineCouchePhysique") ;
    return(-1) ;
   }
 else
   fprintf(stderr,"bytes:%d:%s\n",rc,message ) ;

 Chaine = "Bonjour Madame" ;
 rc = Repondre(&L,Chaine,strlen(Chaine)+1) ;
 if ( rc == -1 )
   {
    perror("OrigineCouchePhysique") ;
    return(-1) ;
   }
 else
    fprintf(stderr,"bytes écrits :%d \n",rc ) ;
  printf("La chaine transmise est %s\n",Chaine ) ;
  fflush(stdout) ;
 }
}

