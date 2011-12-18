#ifndef MISSILE_H
#define MISSILE_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#include "Ecran/Ecran.h"
#include "EcranX/EcranX.h"
#include "Grille/Grille.h"

#include "Defines.h"
#include "Utils.h"

typedef struct _S_MISSILE {
	int ligne;
	int colonne;
	int joueur;
	pthread_t tid;
	struct _S_MISSILE* suivant;
} S_MISSILE;

void initialiseMissiles();
void terminerMissiles();

bool missileCollide(S_MISSILE* missile);

void nouveauMissile(int ligne, int colonne, int joueur);
void* threadMissile(void* v_missile);
void threadMissileCleanup(void* v_missile);
void insereMissile(S_MISSILE* missile);
S_MISSILE* getMissile(int ligne, int colonne);
pthread_t getTidMissile(int ligne, int colonne);
void retireMissile(S_MISSILE* missile);

#endif