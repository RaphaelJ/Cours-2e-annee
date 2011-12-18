#ifndef CANON_H
#define CANON_H

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

void nouveauCanon();
void* threadCanon(void* vdata);
void pressionTouche(int sig);
void deplacerCanon(int col, int dx);
void lancerMissile(int col);

#endif