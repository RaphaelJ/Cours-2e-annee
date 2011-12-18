#ifndef DEFINE_H
#define DEFINE_H

#include <time.h>

//#define pthread_mutex_lock(m); ;

#define KEY_SPACE  32
#define KEY_DOWN   50
#define KEY_UP     51
#define KEY_LEFT   52
#define KEY_RIGHT  53

#define NB_LIGNE   22
#define NB_COLONNE 18

#define LGN_CANONS NB_LIGNE-1
#define LGN_BOUCLIERS NB_LIGNE-3

#define VIDE             0
#define CANON1           1
#define CANON2           2
#define MISSILE          3
#define BOUCLIER1        4
#define BOUCLIER2        5
#define ALIEN            6
#define BOMBE            7
#define VAISSEAU_AMIRAL  8

#define GAUCHE       10
#define DROITE       11

// Timouts en millisecondes
#define MISSILE_SLEEP 80
#define TIR_SLEEP 600
#define ALIENS_SLEEP 1000
#define BOMBE_SLEEP 160

#endif