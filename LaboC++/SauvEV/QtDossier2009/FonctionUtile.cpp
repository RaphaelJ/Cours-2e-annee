/* 
   In.Pr.E.S.
   Denys MERCENIER
   FonctionUtile.c
*/

#include "FonctionUtile.h"

void Trace(char *pszTrace, ... )
{
char szBuffer[80];
va_list arg;
va_start(arg,pszTrace);
vsprintf(szBuffer,pszTrace,arg);
fprintf(stderr,"%s\n",szBuffer);
va_end(arg);
return ;
}
