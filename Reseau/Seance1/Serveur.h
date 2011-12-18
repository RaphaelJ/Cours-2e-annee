#ifndef SERVEUR_H
#define SERVEUR_H
#include "Informations.h"
void ReserverTicket(FILE* f, INFOS*);
void PayerTicket(FILE* f);
void SortirParking(FILE* f);
void ListerFichier(FILE* f);
void CreerFichier(FILE* f);
#endif