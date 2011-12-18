/*-----------------------------------------------------------------------------
  Vanstapel Herman EPL

  evlib\evlib.h
  Ceci  est la librairie evlib.h 
  Utilisation d'evenements
------------------------------------------------------------------------------*/
#ifndef EVLIB
#define EVLIB

#include <sys/types.h>
#include <sys/time.h>
#include <string.h>

struct gEvenement{
	fd_set rfds ;
        fd_set wfds ;
	struct timeval tv ;
	int maxdesc ;
};

int PrepareEvenement( struct gEvenement *gEv,int HLs[],int HEs[],int nbr, int ts,int tms );
int AttendreEvenement(struct gEvenement *gEv,int *HL,int *HE) ;
void ActiverCouche(struct gEvenement *gEv,int num ) ;
void DesactiverCouche(struct gEvenement *gEv,int num ) ;
#endif
#ifndef NULL
#define NULL 0
#endif  
