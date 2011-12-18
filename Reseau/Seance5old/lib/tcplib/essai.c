#include <stdio.h>
#include "tcplib.h"

main()
{
  int res ;
  char Buffer[50] ;

 res = generer_masque( 24 ) ;
 Ipv4ToS(res,Buffer) ;
 printf("Le resultat est %s \n",Buffer) ;
}
