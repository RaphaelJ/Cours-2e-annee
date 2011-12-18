/*--------------------------------------------------------------------------
  Vanstapel Herman EPL

  Ceci  est la librairie evtmlib.c 
  Utilisation d'evenements

  evtmlib.h
--------------------------------------------------------------------------*/

#ifndef EVTMLIB
#define EVTMLIB

#include "../evlib/evlib.h"
#include "../timerlib/timerlib.h"

/*       attendre un timeout          */
#define TIMEOUT 500000

int AttendreEvenementtm(struct gEvenement *gEv,int *HL,int *HE,struct ListeTimer **pl) ;  
#endif
