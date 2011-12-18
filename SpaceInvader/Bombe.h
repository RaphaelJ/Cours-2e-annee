#ifndef BOMBE_H
#define BOMNE_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#include "Ecran/Ecran.h"
#include "EcranX/EcranX.h"
#include "Grille/Grille.h"

#include "Defines.h"
#include "Utils.h"
#include "Missile.h"

typedef struct _S_BOMBE {
	int ligne;
	int colonne;
	pthread_t tid;
	struct _S_BOMBE* suivant;
} S_BOMBE;

void initialiseBombes();
void terminerBombes();

void nouvelleBombe(int ligne, int colonne);
void* threadBombe(void* v_bombe);
void threadBombeCleanup(void* v_bombe);
void insereBombe(S_BOMBE* bombe);
S_BOMBE* getBombe(int ligne, int colonne);
pthread_t getTidBombe(int ligne, int colonne);
void retireBombe(S_BOMBE* bombe);

#endif