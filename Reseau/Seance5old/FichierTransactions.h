#ifndef FICHIERTRANSACTION_H
#define FICHIERTRANSACTION_H

#include <stdio.h>
#include <stdlib.h>

#include "Informations.h"

#define FICHIER_INFOS "infos"

FILE* OuvrirFichier(const char* nomFichier);
void CreerFichier(FILE* f);
int TicketPayable(FILE* f, int numTicket, int heureDepart,
                 int ip, int port, int numTransac);
int PayerTicket(FILE* f, int numTicket, int heureDepart,
                 int ip, int port, int numTransac);
void SortirParking(FILE* f, int numTicket, int heureDepart);
void ListerFichier(FILE* f);
void ListerFichierAsync(const char* nomFichier);
int NouvelleTransaction(FILE* f);
int Doublon(FILE* f, int ip, int port, int numTransac);

#endif