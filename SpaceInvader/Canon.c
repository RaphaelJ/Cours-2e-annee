#include "Canon.h"

extern int tab[NB_LIGNE][NB_COLONNE];
extern pthread_mutex_t mutexGrille;

static bool fireOn = true;

// Lance ne thread de gestion du canon
void nouveauCanon()
{
	pthread_t thread_id;
	if (pthread_create(&thread_id, NULL, threadCanon, NULL) != 0) {
		Trace("Erreur lors du lancement du thread de gestion"
			"du canon"
		);
		exit(1);
	}
	
	pthread_detach(thread_id);
}

// Active la gestion des événement et patiente
void* threadCanon(void* vdata)
{	
	// Dessine le canon dans son premier etat
	Trace("Lock canon ...");
	pthread_mutex_lock(&mutexGrille);
	
	tab[LGN_CANONS][NB_COLONNE / 4] = CANON1;
	DessineCanon(LGN_CANONS, NB_COLONNE / 4, 1);
	
	pthread_mutex_unlock(&mutexGrille);
	Trace("OK Lock canon ...");
	
	// Active la gestion des touches
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	Action.sa_handler = pressionTouche;
	
	sigaction(SIGUSR1, &Action, NULL); // Gauche
	sigaction(SIGUSR2, &Action, NULL); // Droite
	sigaction(SIGHUP, &Action, NULL); // Tirer
	sigaction(SIGQUIT, &Action, NULL); // Quitter
	
	pause();
}

// Gère les événements du canon
void pressionTouche(int sig)
{
	Trace("Lock canon ...");
	pthread_mutex_lock(&mutexGrille);
	Trace("OK Lock canon ...");
	
	// Recherche de la position du canon
	int col;
	for (int i = 0; i < NB_COLONNE; i++) {
		if (tab[LGN_CANONS][i] == CANON1) {
			col = i;
			break;
		}
	}
	
	switch (sig) {
	case SIGUSR1: // Gauche
		deplacerCanon(col, -1);
		break;
	case SIGUSR2: // Droite
		deplacerCanon(col, +1);
		break;
	case SIGHUP: // Tirer
		lancerMissile(col);
		break;
	case SIGQUIT: // Quitter
		Trace("Canon détruit");
		pthread_exit(NULL);
		break;
	}
	
	pthread_mutex_unlock(&mutexGrille);
}

// Déplace latéralement le canon
void deplacerCanon(int col, int dx)
{	
	col += dx;
	if (col < 0 || col >= NB_COLONNE || tab[LGN_CANONS][col] != VIDE) {
		// Nouvelle position invalide
		return;
	}
	
	// Efface l'ancien canon
	tab[LGN_CANONS][col - dx] = VIDE;
	DessineVide(LGN_CANONS, col - dx);
	
	// Dessine le nouveau canon
	tab[LGN_CANONS][col] = CANON1;
	DessineCanon(LGN_CANONS, col, 1);
}

void* fireOnThread(void* args);
void lancerMissile(int col)
{
	if (fireOn) {
		nouveauMissile(LGN_CANONS - 1, col, 1);
		
		pthread_t tid;
		if (pthread_create(&tid, NULL, fireOnThread, NULL) != 0) {
			Trace("Erreur lors du lancement du thread de timeout");
			exit(1);
		}
		
		pthread_detach(tid);
	}
}

// Bloque temporairement les tirs de missiles
void* fireOnThread(void* args)
{
	fireOn = false;
	
	milisec_sleep(TIR_SLEEP);
	
	fireOn = true;
}
