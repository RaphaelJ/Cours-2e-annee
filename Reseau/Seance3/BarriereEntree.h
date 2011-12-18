#ifndef BARRIEREENTREE_H
#define BARRIEREENTREE_H

#include <setjmp.h>

#include "Informations.h"
#include "Reseau.h"
#include "FichierTransactions.h"

void EnvoyerDemandeTicket(struct Physique* conn);
void ReceptionTicket(FILE* f, struct Physique* conn);

#endif