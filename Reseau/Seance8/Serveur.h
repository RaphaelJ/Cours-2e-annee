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

void GererClient(FILE* f, struct Physique* conn, int desc);

void GererReservationClient(FILE* f, struct Physique* conn, REQUETE requete);
void GererDemandePaiementClient(FILE* f, struct Physique* conn, REQUETE requete);
void GererConfirmationPaiementClient(FILE* f, struct Physique* conn, REQUETE requete);
void GererSortieClient(FILE* f, struct Physique* conn, REQUETE requete);

void Patienter();

#endif