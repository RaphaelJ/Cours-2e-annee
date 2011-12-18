/* Exercice 1 :
   Gestion d'un fichier.
   IN.PR.E.S.
   Denys MERCENIER
   Ecran.h
*/

#ifndef        _ECRAN_H_
#define        _ECRAN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef SUN
#include <sys/varargs.h>
#endif

#ifdef COPERNIC
#include <varargs.h>
#include <stdarg.h>
#endif

#ifdef __linux__
#include <stdarg.h>
#endif

/* fonctions simplifiees de gestion d'ecran */

void Trace(char *, ...);
void TraceErreur(char *, ...);

#endif				/* _ECRAN_H_ */
