/*-------------------------------------------------------------------------------------------------
  Vanstapel Herman EPL

  Ceci  est la librairie evlib.c 
  evlib\evlib.c
  Utilisation d'evenements
--------------------------------------------------------------------------------------------------*/

#include "evlib.h"

int PrepareEvenement( struct gEvenement *gEv,int HLs[],int HEs[],int nbr,int ts,int tms ) 
{
 int i ;
 
 FD_ZERO(&(gEv->rfds)) ;
 FD_ZERO(&(gEv->wfds)) ;
 i = 0 ;

 while(i < nbr )
 {
  if ( HLs[i] )
     {
     FD_SET( i ,&(gEv->rfds)) ;
     gEv->maxdesc = i + 1 ;
     }
  if ( HEs[i] )
     {
     FD_SET( i,&(gEv->wfds))  ;
     gEv->maxdesc = i + 1 ; 
     }
  i++ ;
 } 

 gEv->tv.tv_sec  = ts   ;
 gEv->tv.tv_usec = tms  ;
 return(1) ;
}


int AttendreEvenement(struct gEvenement *gEv,int *HL,int *HE)  
{
 fd_set rfds ;
 fd_set wfds ;
 struct timeval tv ;
 int rc ;
 int i ;

 memcpy(&rfds, &(gEv->rfds), sizeof(fd_set) ) ;
 memcpy(&wfds, &(gEv->wfds), sizeof(fd_set) ) ;
 memcpy(&tv, &(gEv->tv), sizeof(struct timeval)) ;

 *HL = -1 ;
 *HE = -1 ;
 rc=select(gEv->maxdesc,&rfds,&wfds,NULL,&tv) ;
 if ( rc > 0 )
    { 
 /* printf("%d \n",rc) ; */
     i = 0 ;    
     while(i < gEv->maxdesc )
     {
      if (FD_ISSET(i,&rfds))
         {
         *HL = i ;
 /* printf("Lecture \n") ; */
          break ;  
         }
      if (FD_ISSET(i,&wfds))
        { 
         *HE = i ;
 /* printf("Ecriture \n") ; */
         break ;
        }
      i++ ;
     } 
    } 
 return( rc ) ;
}

void ActiverCouche(struct gEvenement *gEv,int num)
{
     FD_SET( num ,&(gEv->rfds)) ;
}

void DesactiverCouche(struct gEvenement *gEv,int num)
{
     FD_CLR( num,&(gEv->rfds)) ;
}
