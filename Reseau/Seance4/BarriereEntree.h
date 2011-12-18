#ifndef BARRIEREENTREE_H
#define BARRIEREENTREE_H

//#include <setjmp.h>

#include "Informations.h"
#include "Reseau.h"
#include "FichierTransactions.h"

#define NBRE_RETRANSMISSIONS 4
#define TIMOUT_RETRANSMISSIONS 4000

bool EnvoyerDemandeTicket(struct Physique* conn, REQUETE* requete);
void RenvoyerDemandeTicket(struct Physique* conn, REQUETE requete);
void ReceptionTicket(FILE* f, struct Physique* conn);

#endif