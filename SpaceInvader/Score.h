#ifndef SCORE_H
#define SCORE_H

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

void initialiseScore();
void terminerScore();
void* threadScore(void* vdata);

#endif