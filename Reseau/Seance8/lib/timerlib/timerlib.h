/*----------------------------------------------------------------------------
  Vanstapel Herman EPL

   Prototype pour la librairie timerlib.h

--------------------------------------------------------------------------*/
#ifndef TIMERLIB
#define TIMERLIB
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>

struct ListeTimer 
{
 int num    ;
 long clktck ;
 struct ListeTimer *psuiv ;
};

int microtoclktck( int micro ) ;
int millitoclktck( int milli ) ;
struct ListeTimer * StartTimer( int num, int to, struct ListeTimer *pl) ;
struct ListeTimer *TestTimer(int *num , struct ListeTimer *pl) ;
struct ListeTimer *StopTimer(int num , struct ListeTimer *pl ) ;
void   AfficheTimer(struct ListeTimer *pl) ;
#endif 
