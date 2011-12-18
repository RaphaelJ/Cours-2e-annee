#ifndef ALIENS_H
#define ALIENS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <math.h>

#include "Ecran/Ecran.h"
#include "EcranX/EcranX.h"
#include "Grille/Grille.h"

#include "Defines.h"
#include "Utils.h"
#include "Missile.h"
#include "SpaceInvader.h"

#define LGN_CANONS NB_LIGNE-1

void initialiseAliens();
void terminerAliens();
void* threadInvader(void* vdata);
void* threadFotteAlien(void* vdata);

#endif