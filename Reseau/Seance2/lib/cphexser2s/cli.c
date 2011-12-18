/*---------------------------------------------------------------
   Vanstapel Herman
   cphexser2\cli.c

------------------------------------------------------------------*/
#include <stdio.h>
#include "../physlib/physlib.h"

int main(int argc, char *argv[])
{
 int rc ;
 char Message[80] ;
 struct Physique L ;
 char   Buffer[500] ;
 int	tm  ;
 int	i ;

 bzero(&L,sizeof(struct Physique)) ;
 if (argc!=5)
 {
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 i = 0 ;
 while(i<10)
 {
 rc = CreerConnexion(&L,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) ;
 if ( rc == -1 )
    perror("CreerLiaison:") ;
 else
    fprintf(stderr,"Liaison Cree\n") ;
 sprintf(Message,"Ceci est un test %d \n",i) ;
 rc = VersCouchePhysique(&L,Message,strlen(Message)+1 ) ;
 if ( rc == -1 )
    perror("VersCouchePhysique") ;
 else
   fprintf(stderr,"Envoi de %d bytes\n",rc ) ;
 tm = sizeof(Buffer) ;
 rc = OrigineCouchePhysique(&L,Buffer,&tm) ;
 if ( rc == -1 )
    perror("OrigineCouchePhysique") ;
 else
   fprintf(stderr,"Reception de %d bytes %s\n",rc,Buffer ) ;
  FermetureConnexion(&L) ;
  i++ ;
 }
}
