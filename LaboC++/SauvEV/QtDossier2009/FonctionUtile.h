/* 
   IN.PR.E.S.
   Denys MERCENIER
   FonctionUtile.h
*/

#ifndef        _FONCTIONUTILE_H_
#define        _FONCTIONUTILE_H_

#define        NORM      0
#define        GRAS      1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef SUN
#include <sys/varargs.h>
#endif

#ifdef COMPAC
#include <varargs.h>
#include <stdarg.h>
#endif
/* fonctions simplifiees de gestion d'ecran */

void Trace(char *,...);

#endif
