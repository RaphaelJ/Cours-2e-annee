#include "FonctionUtile.h"
#include <stdio.h>

void Trace(const char *pszTrace,...)
{
char szBuffer[256];

va_list	 	arg;
va_start(arg,pszTrace);
vsprintf(szBuffer,pszTrace,arg);
fprintf(stderr,"%s\n",szBuffer);
//fprintf(stderr,"(%s) %s\n",__FILE__,szBuffer);
va_end(arg);
return;
}
