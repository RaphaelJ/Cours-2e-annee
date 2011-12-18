#ifndef GRILLE_H
#define GRILLE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define GRILLE_ON        100
#define GRILLE_OFF       101

typedef struct {
    int TailleCarre;
    int Ligne;
    int Colonne;
    int modeGrille;

    TC tc;

    pthread_t threadRefresh;
    pthread_mutex_t MUTEX;

    int tab[100][100];
    char alive;
} GRILLE;

int OuvrirGrille(int Ligne, int Colonne, int TailleCarre, const char *titre,
		 int modeG);
int FermerGrille();
int DessineCarre(GRILLE *, int ligne, int colonne, int couleur);
void DessinerGrillage(GRILLE *);

// Fonctions specifique a SpaceInvader
void DessineVide(int ligne, int colonne);
void DessineCanon(int ligne, int colonne, int joueur);
void DessineMissile(int ligne, int colonne);
void DessineBouclier(int ligne, int colonne, int niveau);
void DessineAlien(int ligne, int colonne);
void DessineBombe(int ligne, int colonne);
void DessineVaisseauAmiral(int ligne, int colonne);

#endif
