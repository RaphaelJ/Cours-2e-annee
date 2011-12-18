#include "Aliens.h"

pthread_mutex_t mutexAliens;

extern int tab[NB_LIGNE][NB_COLONNE];
extern pthread_mutex_t mutexGrille;

extern S_MISSILE* missiles;
extern pthread_mutex_t mutexMissiles;

extern pthread_mutex_t mutexScore;
extern pthread_cond_t condScore;
extern int score1;
extern int score2;

int nbAliens;
int topLeftLn;
int topLeftCol;
int bottomRightLn;
int bottomRightCol;

pthread_t threadInvaderId;
pthread_t threadFlotteId;

// Lance ne thread de gestion des invasions alien
void initialiseAliens()
{
	pthread_mutex_init(&mutexAliens, NULL);
	
	if (pthread_create(&threadInvaderId, NULL, threadInvader, NULL) != 0) {
		Trace("Erreur lors du lancement du thread Invader");
		exit(1);
	}
	
	pthread_detach(threadInvaderId);
}

void terminerAliens()
{
	pthread_kill(threadInvaderId, SIGINT);
	pthread_kill(threadFlotteId, SIGINT);
	
	pthread_mutex_destroy(&mutexAliens);
}

// Gère les invasions d'aliens ainsi que les passages de
// niveau du jeu
void* threadInvader(void* vdata)
{
	int niveau;
	for (niveau = 1;;) {
		int* retVal;
		
		Trace("Démarrage niveau %d", niveau);
		
		if (pthread_create(&threadFlotteId, NULL, threadFotteAlien, &niveau) != 0) {
			Trace("Erreur lors du lancement du thread de timeout");
			exit(1);
		}
		
		pthread_join(threadFlotteId, (void**) &retVal);
		
		if (*retVal == 0) { // Invasion réussie
			Trace("Invasion réussie. Perdu");
			kill(getpid(), SIGQUIT);
			pthread_exit(NULL);
		} else { // Invasion stoppée
			Trace("Invasion stoppée");
			niveau += 1;
		}
		
		free(retVal);
	}
}

void threadFotteAlienCleanup(void* v);
float vitesseAliens(int niveau);
bool deplDroite();
bool deplGauche();
bool deplBas();
void deplacerAlien(int fromLn, int fromCol, int toLn, int toCol);
void calculerTailleFlotte();
// Gère les déplacements des aliens de la flotte
// Retourne 0 en cas de réussite de l'invasion
// 1 en cas de destruction de la flotte.
void* threadFotteAlien(void* vdata)
{
	int niveau = *((int*) vdata);
	int* retour = (int*) malloc(sizeof (int));
	int durreeSleepDepl = (int) (vitesseAliens(niveau) * ALIENS_SLEEP);
	bool (*depl)() = deplDroite;
	
	pthread_cleanup_push(threadFotteAlienCleanup, NULL);
	
	Trace("Lock flotte 1 ...");
	pthread_mutex_lock(&mutexGrille);
	pthread_mutex_lock(&mutexMissiles);
	pthread_mutex_lock(&mutexAliens);
	Trace("OK Lock flotte 1 ...");
	initialiseBoucliers();
	nbAliens = 35;
	topLeftLn = 1;
	topLeftCol = 0;
	bottomRightLn = 9;
	bottomRightCol = 12;
	// Position initiale de la flotte
	for (int l = topLeftLn; l <= bottomRightLn; l+=2) {
		for (int c = topLeftCol; c <= bottomRightCol; c+=2) {
			tab[l][c] = ALIEN;
			DessineAlien(l, c);
		}
	}
	
	pthread_mutex_unlock(&mutexGrille);
	pthread_mutex_unlock(&mutexMissiles);
	pthread_mutex_unlock(&mutexAliens);
	
	for (;;) {
		milisec_sleep(durreeSleepDepl);
		
		if (rand() % (nbAliens * 2))
		
		Trace("Lock flotte 2 ...");
		pthread_mutex_lock(&mutexGrille);
		pthread_mutex_lock(&mutexMissiles);
		pthread_mutex_lock(&mutexAliens);
		Trace("OK Lock flotte 2 ...");
		if (!depl()) { // Déplacement latéral
			if (!deplBas()) {
				// Atteint la ligne des boucliers
				*retour = 0;
				pthread_mutex_unlock(&mutexGrille);
				pthread_mutex_unlock(&mutexMissiles);
				pthread_mutex_unlock(&mutexAliens);
				pthread_exit(retour);
				return retour;
			} else {
				if (depl == deplDroite)
					depl = deplGauche;
				else
					depl = deplDroite;
			}
		}
		
		if (nbAliens <= 0) {
			*retour = 1;
			pthread_mutex_unlock(&mutexGrille);
			pthread_mutex_unlock(&mutexMissiles);
			pthread_mutex_unlock(&mutexAliens);
			pthread_exit(retour);
			return retour;
		}
		
		pthread_mutex_unlock(&mutexGrille);
		pthread_mutex_unlock(&mutexMissiles);
		pthread_mutex_unlock(&mutexAliens);
	}
	
	pthread_cleanup_pop(1);
}

// Nettoie l'écran des invaders
void threadFotteAlienCleanup(void* v)
{
	for (int l = topLeftLn; l <= bottomRightLn; l+=2) { // De haut en bas
		for (int c = topLeftCol; c <= bottomRightCol; c+=2) { // De gauche à droite
			if (tab[l][c] == ALIEN) {
				tab[l][c] = VIDE;
				DessineVide(l, c);
			}
		}
	}
}

// Retourne le multiplicateur du temps d'attente des déplacements
// des aliens pour un niveau du jeu donné
float vitesseAliens(int niveau)
{
	// Réduction de 30% entre chaque niveau
	return pow(1-0.3, niveau - 1);
}

// Fonctions de déplacement.
// Retournent false si le déplacement n'a pas pu
// s'effectuer (bordures de la grille)
bool deplDroite()
{
	if (bottomRightCol + 1 >= NB_COLONNE)
		return false;
	else {
		// Déplacement des aliens
		Trace("Deplacement droite");
		for (int l = topLeftLn; l <= bottomRightLn; l+=2) { // De haut en bas
			for (int c = bottomRightCol; c >= topLeftCol; c-=2) { // De droite à gauche
				if (tab[l][c] == ALIEN) {
					deplacerAlien(l, c, l, c+1);
				}
			}
		}
		Trace("Deplacement droite OK");
		
		topLeftCol += 1;
		bottomRightCol += 1;
		calculerTailleFlotte();
		
		return true;
	}
}

bool deplGauche()
{
	if (topLeftCol - 1 < 0)
		return false;
	else {
		// Déplacement des aliens
		Trace("Deplacement droite");
		for (int l = topLeftLn; l <= bottomRightLn; l+=2) { // De haut en bas
			for (int c = topLeftCol; c <= bottomRightCol; c+=2) { // De gauche à droite
				if (tab[l][c] == ALIEN) {
					deplacerAlien(l, c, l, c-1);
				}
			}
		}
		Trace("Deplacement droite OK");
		
		topLeftCol -= 1;
		bottomRightCol -= 1;
		calculerTailleFlotte();
		
		return true;
	}
}

bool deplBas()
{
	if (bottomRightLn + 1 >= LGN_BOUCLIERS) {
		return false;
	} else {
		// Déplacement des aliens
		Trace("Deplacement droite");
		for (int l = bottomRightLn; l >= topLeftLn; l-=2) { // De bas en haut
			for (int c = topLeftCol; c <= bottomRightCol; c+=2) { // De gauche à droite
				if (tab[l][c] == ALIEN) {
					deplacerAlien(l, c, l+1, c);
				}
			}
		}
		Trace("Deplacement droite OK");
		
		topLeftLn += 1;
		bottomRightLn += 1;
		calculerTailleFlotte();
		
		return true;
	}
}

void deplacerAlien(int fromLn, int fromCol, int toLn, int toCol)
{
	if (tab[toLn][toCol] == MISSILE) {
		Trace("Colision MISSILE");
		// Augmente le score du joueur
		S_MISSILE* missile = getMissile(toLn, toCol);
		pthread_mutex_lock(&mutexScore);
		if (missile->joueur == 1) {
			score1 += 1;
		} else {
			score2 += 1;
		}		
		pthread_mutex_unlock(&mutexScore);
		pthread_cond_signal(&condScore);
		
		nbAliens -= 1;
		
		// Détruit le missile
		tab[missile->ligne][missile->colonne] = VIDE;
		DessineVide(missile->ligne, missile->colonne);
		pthread_kill(getTidMissile(toLn, toCol), SIGINT);
	} else if (tab[toLn][toCol] == BOMBE) {
		Trace("Colision BOMBE");
		Trace("Colision avec une bombe");
		tab[toLn][toCol] = ALIEN;
		DessineAlien(toLn, toCol);
		
		Trace("TID BOMBE");
		getTidBombe(toLn, toCol);
		Trace("Kill BOMBE");
		pthread_kill(getTidBombe(toLn, toCol), SIGINT);
		Trace("NEW BOMBE");
		nouvelleBombe(toLn+1, toCol);
	} else {
		Trace("Colision ALIEN");
		tab[toLn][toCol] = ALIEN;
		DessineAlien(toLn, toCol);
		
		if ((rand() % (nbAliens * 2)) == 0) { // Lache une bombe
			nouvelleBombe(toLn+1, toCol);
		}
	}
	Trace("Colision OK");
	
	tab[fromLn][fromCol] = VIDE;
	DessineVide(fromLn, fromCol);
}

// Calcule les nouvelles coordonnées de la flotte
void calculerTailleFlotte()
{
	if (nbAliens > 0) {
		int minCol = bottomRightCol;
		int maxCol = topLeftCol;
		int minLn = bottomRightLn;
		int maxLn = topLeftLn;
		
		for (int l = topLeftLn; l <= bottomRightLn; l+=2) { // De haut en bas
			for (int c = topLeftCol; c <= bottomRightCol; c+=2) { // De gauche à droite
				if (tab[l][c] == ALIEN) {
					if (c < minCol) {
						minCol = c;
					} else if (c > maxCol) {
						maxCol = c;
					}
					
					if (l < minLn) {
						minLn = l;
					} else if (l > maxLn) {
						maxLn = l;
					}
				}
			}
		}
		
		topLeftCol = minCol;
		topLeftLn = minLn;
		bottomRightCol = maxCol;
		bottomRightLn = maxLn;
	}
}
