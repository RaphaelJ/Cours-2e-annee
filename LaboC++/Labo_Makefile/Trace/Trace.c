#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "Trace.h"

void Trace(const char* pszTrace, ...)
{
	char szBuffer[80];
	va_list arg;
	
	va_start(arg, pszTrace);
	vsprintf(szBuffer, pszTrace, arg);
	fprintf(stderr, "%s\n", szBuffer);
	va_end(arg);
	
	return;
}