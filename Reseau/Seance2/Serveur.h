#ifndef SERVEUR_H
#define SERVEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

#include "Informations.h"
#include "FichierTransactions.h"
#include "Reseau.h"

void GererClient(FILE* f, struct Physique* conn);

// void ReserverTicket(FILE* f, INFOS* infos);
// void PayerTicket(FILE* f);
// void SortirParking(FILE* f);
// void ListerFichier(FILE* f);
// void CreerFichier(FILE* f);

#endif