#ifndef CREATRANSACSERVEUR_H
#define CREATRANSACSERVEUR_H

#include <stdio.h>

#include "Informations.h"

void CreerFichier(FILE* f);
void ReserverTicket(FILE* f);
void PayerTicket(FILE* f);
void SortirParking(FILE* f);
void ListerFichier(FILE* f);

#endif