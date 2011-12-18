/* Exercice 1 :
   Gestion d'un fichier.
   In.Pr.E.S.
   Denys MERCENIER
   Ecran.c
*/

#include "Ecran.h"

extern	char* NomProcess;

void Trace(char *pszTrace, ... )
{
char szBuffer[80];
va_list arg;
va_start(arg,pszTrace);
vsprintf(szBuffer,pszTrace,arg);
fprintf(stderr,"%s(%d) :  (%s)\n",NomProcess,getpid(),szBuffer);
va_end(arg);
return ;
}

void TraceErreur(char *pszTrace, ... )
{
char szBuffer[80];
char szErreur[80];
va_list arg;
va_start(arg,pszTrace);
vsprintf(szBuffer,pszTrace,arg);
sprintf(szErreur,"%s(%d) : %s",NomProcess,getpid(),szBuffer);
perror(szErreur);
va_end(arg);
return ;
}
