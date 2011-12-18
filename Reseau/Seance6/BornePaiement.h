#ifndef BORNEPAIEMENT_H
#define BORNEPAIEMENT_H

//#include <setjmp.h>

#include "Informations.h"
#include "Reseau.h"
#include "FichierTransactions.h"

#define NBRE_RETRANSMISSIONS 4
#define TIMOUT_RETRANSMISSIONS 4000

bool EnvoyerDemandePaiement(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requete);
void ReceptionDemandeConfirmation(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete);
bool EnvoyerConfirmationPaiement(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requete);
void ReceptionValidationPaiement(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete);

#endif