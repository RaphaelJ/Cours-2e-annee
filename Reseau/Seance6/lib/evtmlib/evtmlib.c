/*-----------------------------------------------------------------------------
  Vanstapel Herman EPL

  Ceci  est la librairie evlib.c 
  Utilisation d'evenements

  evtmlib.c
------------------------------------------------------------------------------*/

#include "evtmlib.h"

int AttendreEvenementtm(struct gEvenement *gEv,int *HL,int *HE,struct ListeTimer **pl)
{
 int rc ;
 while(1)
 {
   *pl = TestTimer( &rc,*pl ) ;
   if ( rc == -1 ) /* pas de Timer armé */
     {
      rc = AttendreEvenement(gEv,HL,HE) ;
      /*  printf("--> %d \n",rc) ; */ 
      if ( rc == 0 ) /*- Il y a eut un timeout au niveau du select -*/
         continue ;
      else
         return(rc) ;    
     }
   else
      { 
      *HL = TIMEOUT + rc ;
      *HE = TIMEOUT + rc ;
      return ( TIMEOUT + rc ) ;
     }
 }   
}   
