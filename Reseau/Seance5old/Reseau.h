#ifndef RESEAU_H
#define RESEAU_H

#include <stdio.h>

#include "Informations.h"
#include "lib/physlib/physlib.h"
#include "lib/evlib/evlib.h"
#include "lib/evtmlib/evtmlib.h"
#include "lib/timerlib/timerlib.h"

#define NBRE_RETRANSMISSIONS 4
#define TIMOUT_RETRANSMISSIONS 4000

typedef struct _REQUETE {
	char* IP;
	int Port;
	ACTIONS Code;
	int Heure;
	int NumTransac; // Transaction du client
	int NumTicket; // Le dernier Numéro de ticket attribué
} REQUETE;

int ConnecterClient(int argc, char* argv[], struct Physique* conn);
int ConnecterServeur(int argc, char* argv[], struct Physique* conn);
int EnvoiClient(struct Physique* conn, void* data, int taille);
int EnvoiServeur(struct Physique* conn, void* data, int taille);
int Reception(struct Physique* conn, void* data, int* taille);

int CreerEvenement(int desc, struct gEvenement* even, int secsTimeOut);
int CreerEvenementMilisecs(int desc, struct gEvenement* even, int secsTimeOut,
                   int miliSecsTimeOut);
int AttendreTimer(struct gEvenement* even, int* desc, struct ListeTimer** Timer);
int Attendre(struct gEvenement* even, int* desc);

bool EntreeTimeOut(int* donnees);

void Transmettre(struct Physique* conn, int connDescPhys, FILE* f, const char* nomAction,
                 bool (*fct_demande)(FILE* f, struct Physique* conn, REQUETE* requeteEnvoyee),
		 void (*fct_reception)(FILE* f, struct Physique* conn, REQUETE requete));
#endif