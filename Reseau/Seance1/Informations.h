#ifndef INFORMATIONS_H
#define INFORMATIONS_H

#include <stdio.h>
#include "../lib/physlib/physlib.h"

#define FICHIER_INFOS "infos"

typedef enum _bool {
	false,
	true
} bool;

typedef enum _ACTIONS {
	ENTETE,
	RESERVATION,
	PAYEMENT,
	SORTIE 
} ACTIONS;

typedef struct _INFOS {
	int IP; // IP de l’émetteur   
	int Port; // Port de l émetteur   
	int NumTransac; // Transaction du client  
	int Heure; // Heure de l’action ( Chiffre entre 0 et 24 )
	int PlacesLibres; // Le nombre de places restantes
	int NumTicket; // Le dernier Numéro de ticket attribué
	ACTIONS Action; // Action Man
} INFOS;

typedef struct Physique Physique;

FILE* OuvrirFichier();
void EcrireInformations(FILE* f, INFOS info);
bool LireInformations(FILE* f, INFOS* infos);
INFOS LireEntetes(FILE* f);
void EcrireEntetes(FILE* f, INFOS entetes);
void AfficherInformations(INFOS infos);
bool Connect(int argc, char* argv[], Physique*);
bool Send(Physique *s, INFOS *infos, int Taille);
bool Receive(Physique *s, INFOS *infos, int *Taille);
#endif