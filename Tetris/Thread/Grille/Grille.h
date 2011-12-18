#ifndef GRILLE_H
#define GRILLE_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

typedef struct
{
  int TailleCarre;
  int Ligne;
  int Colonne;
  
  TC tc;
  
  pthread_t threadRefresh;
  pthread_mutex_t MUTEX;

  int tab[100][100];
  char alive;
} GRILLE;

int  OuvrirGrille(GRILLE*,int Ligne,int Colonne,int TailleCarre,char* titre);
int  FermerGrille(GRILLE*);
int  DessineCarre(GRILLE*,int ligne,int colonne,int couleur);
void DessinerGrillage(GRILLE*);

#endif

