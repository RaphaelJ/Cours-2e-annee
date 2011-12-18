#ifndef SPACEINVADER_H
#define SPACEINVADER_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>

#include "Ecran/Ecran.h"
#include "EcranX/EcranX.h"
#include "Grille/Grille.h"

#include "Defines.h"
#include "Canon.h"
#include "Missile.h"
#include "Aliens.h"
#include "Bombe.h"
#include "Score.h"
#include "ReadChar.h"

int main(int argc, char *argv[]);
void initialiseGrille();
void initialiseBoucliers();
void gestionTouches();

#endif