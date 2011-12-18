/*---------------------------------------------------------------
   Vanstapel Herman
   C05\cli.c
 
  Test de la taille  : l'émetteur 
------------------------------------------------------------------*/
#include <stdio.h>
#include "../physlib/physlib.h"

void main(int argc, char *argv[])
{
 int rc ;
 char *message ;
 struct Physique L ;
 char	Tampon[65000] ;
 int	i ;

 if (argc!=5)
 {
    printf("cli client portc serveur ports\n") ;
    exit(1) ;
 }
 rc = CreerConnexion(&L,argv[1],atoi(argv[2]),argv[3],atoi(argv[4])) ;
 if ( rc == -1 )
    perror("CreerLiaison:") ;
 else
    printf("Liaison Créé \n") ;
 message = "Ceci est un test" ;
 i = 1 ;
 memset(Tampon,'X',65000) ;
 while(i < 65000 )
 {
 rc = VersCouchePhysique(&L,message, i ) ;
 if ( rc == -1 )
    perror("VersCouchePhysique") ;
 else
   printf("Envoi de %d bytes\n",rc ) ;
  i = i * 2 ;
 }
}
