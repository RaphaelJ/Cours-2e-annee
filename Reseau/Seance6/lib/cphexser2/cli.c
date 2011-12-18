/*---------------------------------------------------------------
   Vanstapel Herman
   cphexser2\cli.c

------------------------------------------------------------------*/
#include <stdio.h>
#include "../physlib/physlib.h"

int main(int argc, char *argv[])
{
 int rc ;
 char *message ;
 struct Physique L ;
 char   Buffer[500] ;
 int	tm  ;

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
    fprintf(stderr,"Liaison Cree\n") ;
 message = "Ceci est un test" ;
 rc = VersCouchePhysique(&L,message,strlen(message)+1 ) ;
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
}
