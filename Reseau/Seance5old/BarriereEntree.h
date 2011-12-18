#ifndef BARRIEREENTREE_H
#define BARRIEREENTREE_H

//#include <setjmp.h>

#include "Informations.h"
#include "Reseau.h"
#include "FichierTransactions.h"

bool EnvoyerDemandeTicket(FILE* f, struct Physique* conn, REQUETE* requete);
void RenvoyerDemandeTicket(struct Physique* conn, REQUETE requete);
void ReceptionTicket(FILE* f, struct Physique* conn);

#endif