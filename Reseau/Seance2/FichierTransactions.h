#ifndef FICHIERTRANSACTION_H
#define FICHIERTRANSACTION_H

#include <stdio.h>
#include <stdlib.h>

#include "Informations.h"

#define FICHIER_INFOS "infos"

FILE* OuvrirFichier(const char* nomFichier);
void CreerFichier(FILE* f);
int ReserverTicket(FILE* f, int heureEntree);
void PayerTicket(FILE* f, int numTicket, int heureDepart);
void SortirParking(FILE* f, int numTicket, int heureDepart);
void ListerFichier(FILE* f);
void ListerFichierAsync(const char* nomFichier);

#endif