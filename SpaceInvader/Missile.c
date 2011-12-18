#include "Missile.h"

S_MISSILE* missiles = NULL;
pthread_mutex_t mutexMissiles;

extern int tab[NB_LIGNE][NB_COLONNE];
extern pthread_mutex_t mutexGrille;

extern pthread_mutex_t mutexAliens;
extern int nbAliens;

extern pthread_mutex_t mutexScore;
extern pthread_cond_t condScore;
extern int score1;
extern int score2;

void initialiseMissiles()
{
	pthread_mutex_init(&mutexMissiles, NULL);
}

void terminerMissiles()
{
	pthread_mutex_destroy(&mutexMissiles);
}

void nouveauMissile(int ligne, int colonne, int joueur)
{
	S_MISSILE* missile = (S_MISSILE*) malloc(sizeof (S_MISSILE));
	
	missile->colonne = colonne;
	missile->ligne = ligne;
	missile->joueur = joueur;
	
	if (pthread_create(&missile->tid, NULL, threadMissile, (void*) missile) != 0) {
		Trace("Erreur lors du lancement du thread de gestion"
		      "du missile");
		exit(1);
	}
	
	pthread_detach(missile->tid);
}

void sigintMissile(int sig);
void* threadMissile(void* v_missile)
{
	S_MISSILE* missile = (S_MISSILE*) v_missile;
	
	pthread_cleanup_push(threadMissileCleanup, v_missile);
	
	// Active la gestion du SIGINT
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	Action.sa_handler = sigintMissile;
	sigaction(SIGINT, &Action, NULL);
	
	printf("%d. Lancement missile (colonne: %d)\n", pthread_self(), missile->colonne);
	
	Trace("%d. Lock missile ...", pthread_self());
	pthread_mutex_lock(&mutexGrille);
	pthread_mutex_lock(&mutexMissiles);
	Trace("%d. OK Lock missile ...", pthread_self());
	
	insereMissile(missile);
	
	while (missile->ligne >= 0) {
		
		if (missileCollide(missile)) {
			switch (tab[missile->ligne][missile->colonne]) {
			case BOUCLIER2:
				tab[missile->ligne][missile->colonne] = VIDE;
				DessineVide(missile->ligne, missile->colonne);
				break;
			case BOUCLIER1:
				tab[missile->ligne][missile->colonne] = BOUCLIER2;
				DessineBouclier(missile->ligne, missile->colonne, 2);
				break;
			case ALIEN:
				// Détruit l'alien
				pthread_mutex_lock(&mutexAliens);
				tab[missile->ligne][missile->colonne] = VIDE;
				DessineVide(missile->ligne, missile->colonne);
				nbAliens -= 1;
				pthread_mutex_unlock(&mutexAliens);
				
				// Augmente le score du joueur
				pthread_mutex_lock(&mutexScore);
				if (missile->joueur == 1) {
					score1 += 1;
				} else {
					score2 += 1;
				}		
				pthread_mutex_unlock(&mutexScore);
				pthread_cond_signal(&condScore);
				
				break;
			};
	
			Trace("%d. Unlock missile 3...", pthread_self());
			pthread_mutex_unlock(&mutexGrille);
			pthread_mutex_unlock(&mutexMissiles);
			pthread_exit(NULL);
			return NULL;
		} else {
			tab[missile->ligne][missile->colonne] = MISSILE;
			DessineMissile(missile->ligne, missile->colonne);
		}
		
		Trace("%d. Unlock missile 2...", pthread_self());
		pthread_mutex_unlock(&mutexGrille);
		pthread_mutex_unlock(&mutexMissiles);
		
		milisec_sleep(MISSILE_SLEEP);
		
		Trace("%d. Lock missile 2 ...", pthread_self());
		pthread_mutex_lock(&mutexGrille);
		pthread_mutex_lock(&mutexMissiles);
		Trace("%d. OK Lock missile ...", pthread_self());
		
		tab[missile->ligne][missile->colonne] = VIDE;
		DessineVide(missile->ligne, missile->colonne);
		
		missile->ligne -= 1;
	}
	
	Trace("%d. Unlock missile 1 ...", pthread_self());
	pthread_mutex_unlock(&mutexGrille);
	pthread_mutex_unlock(&mutexMissiles);
	pthread_cleanup_pop(1);
	pthread_exit(NULL);
}

void threadMissileCleanup(void* v_missile)
{
	S_MISSILE* missile = (S_MISSILE*) v_missile;
	
	Trace("Fin du missile");
	
	// Peut provoquer un deadlock :
	//pthread_mutex_lock(&mutexGrille);
	//pthread_mutex_lock(&mutexMissiles);
	
	retireMissile(missile);
}

void sigintMissile(int sig)
{	
	Trace("Missile : Reception du signal SIGINT");
	pthread_exit(NULL);
}

bool missileCollide(S_MISSILE* missile)
{
	return tab[missile->ligne][missile->colonne] != VIDE;
}

void insereMissile(S_MISSILE* missile)
{	
	missile->suivant = missiles;
	missiles = missile;
}

S_MISSILE* getMissile(int ligne, int colonne)
{
	S_MISSILE* missile = missiles;
	while (missile != NULL) {
		if (missile->ligne == ligne && missile->colonne == colonne)
			return missile;
		
		missile = missile->suivant;
	}
	
	return NULL;
}

pthread_t getTidMissile(int ligne, int colonne)
{
	S_MISSILE* missile = getMissile(ligne, colonne);
	if (missile == NULL) 
		return -1;
	else
		return missile->tid;
}

void retireMissile(S_MISSILE* missile)
{	
	S_MISSILE* iMissile = missiles;
	S_MISSILE** old = &missiles;
	while (iMissile != NULL) {
		if (iMissile == missile) {
			iMissile->suivant = missile->suivant;
			Trace("Free");
			free(missile);
			break;
		} else {
			old = &(iMissile->suivant);
			iMissile = iMissile->suivant;
		}
	}
}