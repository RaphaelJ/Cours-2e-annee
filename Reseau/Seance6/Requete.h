#ifndef REQUETES_H
#define REQUETES_H

#include <stdio.h>

typedef struct _REQUETE {
	int IP;
	int Port;
	int Code;
	int Heure;
	int NumTransac; // Transaction du client
	int NumTicket; // Le dernier Numéro de ticket attribué
} REQUETE;

#endif