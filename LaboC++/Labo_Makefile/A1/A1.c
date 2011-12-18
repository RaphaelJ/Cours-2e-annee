#include <stdio.h>
#include <stdlib.h>

#include "Ecran.h"
#include "Trace.h"

int main(void)
{
	char* ch;
	
	Trace("Debut de l'appel");
	
	ch = LireChaine();
	AfficheChaine(ch);
	
	Trace("Fin de l'appel");
	
	return 0;
}