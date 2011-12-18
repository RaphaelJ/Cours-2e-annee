/*---------------------------------------------------------------
   Vanstapel Herman
   CIP\essai.c
------------------------------------------------------------------*/
#include <stdio.h>
#include "../physlib/physlib.h"

void main(int argc, char *argv[])
{
 int rc,ip ;
 char *message ;
 struct Physique L ;
 char tmp[60] ;
 char tmp2[20] ;

 printf(">>>") ;
 fgets(tmp,sizeof tmp,stdin) ;
 tmp[strlen(tmp)-1] = 0 ; /* On supprime le newline */
 if (Ipv4ToInt(tmp,&ip)==-1)
    printf("Erreur !!!!!!") ;
 Ipv4ToS(ip,tmp2) ;
 printf("Test %s\n",tmp2 ) ;
}
