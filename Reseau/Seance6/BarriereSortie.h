#ifndef BARRIEREENTREE_H
#define BARRIEREENTREE_H

//#include <setjmp.h>

#include "Informations.h"
#include "Reseau.h"
#include "FichierTransactions.h"

bool EnvoyerDemandeSortie(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requete);
void ReceptionValidationSortie(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete);

#endif