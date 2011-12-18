/*-------------------------------------------------------------------------
  Vanstapel Herman EPL

--------------------------------------------------------------------------

------------------------------------------------------------------------*/

#include <unistd.h>
#include <sys/times.h>
#include "timerlib.h"

int microtoclktck( int micro )
{
 long clktck ;
 clktck = sysconf(_SC_CLK_TCK) ;
 return( ( micro * clktck ) /1000000 ) ;
}

int millitoclktck( int milli )
{
 long clktck ;
 clktck = sysconf(_SC_CLK_TCK) ;
 return( ( milli * clktck ) / 1000 ) ;
}

struct ListeTimer * StartTimer( int num, int to, struct ListeTimer *pl)
{
 long clktck,calcul ;
 struct ListeTimer *pcur,*pprec,*pn ; 
 struct tms tmstart ;

 clktck = times(&tmstart) ;
 pcur = pl ;
 if ( pcur == NULL )
    {
     pcur = (struct ListeTimer *) malloc(sizeof(struct ListeTimer)) ;
     pcur->num = num ;
     pcur->clktck = clktck + millitoclktck(to) ;
     pcur->psuiv = NULL ;
     return(pcur) ;
    }
 else
 {
  /* On ajoute le timer a la fin de la liste  */
 
  calcul = clktck + millitoclktck(to) ; 
  pprec = pcur ;
  while ( pcur != NULL )
    {
     if (  pcur-> clktck > calcul )
        break ;
     pprec = pcur ;
     pcur  = pcur->psuiv ;
    }
  /*---   Construction du nouveau timer                    ---*/
  pn = (struct ListeTimer *) malloc(sizeof(struct ListeTimer)) ;
  pn->num = num ;
  pn->clktck = calcul ;
  pn->psuiv = pcur ;

  /*-----  insertion au bon endroit ------------*/
  if ( pcur == pprec )
     pl = pn ;    	
  else
     pprec -> psuiv = pn ;
  return( pl ) ;
 }
}

struct ListeTimer *TestTimer(int *num , struct ListeTimer *pl)
{
 long clktck ;
 struct tms tmstart ;
 struct ListeTimer *pt ;

 clktck = times(&tmstart) ;
 if ( pl != NULL )
    {
     if ( pl->clktck <= clktck ) /* Une alarme a expire */
        {
         pt   = pl ;    
         *num = pl -> num ;
         pl   = pl -> psuiv ; 
         free(pt) ;
         return(pl) ; 
        }
     else
        *num = -1 ; /* Erreur pas de Timer */
    }
 else
    *num = -1 ; /* Erreur pas de Timer */
 return(pl) ;
}

struct ListeTimer *StopTimer(int num , struct ListeTimer *pl)
{
 struct ListeTimer  *pcur, *pprec ;
 if ( pl == NULL )
    return(NULL) ;
 else
    {
     pprec = pcur = pl ;
     while( pcur != NULL )
     {
      if ( pcur->num == num ) /* Suppression de la tête */
	 if ( pcur == pprec )
            {
              pl = pcur->psuiv ;
              free(pcur) ;
              return(pl) ;  
            }
         else
            {
             pprec->psuiv = pcur ->psuiv ;                 
	     free(pcur) ; 		   
             return(pl) ;
            }
        pprec = pcur ;    
	pcur=pcur->psuiv ; 
     }
     return(pl) ;
    }
}

void AfficheTimer(struct ListeTimer *pl)
{
 while(pl != NULL )
 {
   printf("( %d :",pl->num ) ;
   printf("Cl:%ld),",pl->clktck ) ;
   pl = pl ->psuiv ;
 }
 printf(".\n") ;
}
