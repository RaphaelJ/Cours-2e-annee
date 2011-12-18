#ifndef COMMONS_H
#define COMMONS_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <signal.h>

#include "Defines.h"
#include "Ecran.h"

key_t LireCleQueue();

void ListerTypesEvenements(EVENT_TYPE types[MAX_TYPES]);

void ListerEvenements(EVENT events[MAX_EVENTS], char eventsDir[200]);
void ListerEvenements(EVENT events[MAX_EVENTS], EVENT_TYPE type);
void LireInfosEvenement(EVENT* event, char eventDir[200]);

int LireNbrePlaces(int file);
void EcrireNbrePlaces(int file, int nbrePlaces);

#endif