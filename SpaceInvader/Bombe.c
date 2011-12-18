#include "Bombe.h"

S_BOMBE* bombes = NULL;
pthread_mutex_t mutexBombes;

extern int tab[NB_LIGNE][NB_COLONNE];
extern pthread_mutex_t mutexGrille;

extern pthread_mutex_t mutexAliens;
extern int nbAliens;

extern S_BOMBE* bombes;
extern pthread_mutex_t mutexMissiles;

void initialiseBombes()
{
	pthread_mutex_init(&mutexBombes, NULL);
}

void terminerBombes()
{
	pthread_mutex_destroy(&mutexBombes);
}

void nouvelleBombe(int ligne, int colonne)
{
	S_BOMBE* bombe = (S_BOMBE*) malloc(sizeof (S_BOMBE));
	
	bombe->colonne = colonne;
	bombe->ligne = ligne;
	
	if (pthread_create(&bombe->tid, NULL, threadBombe, (void*) bombe) != 0) {
		Trace("Erreur lors du lancement du thread de gestion"
		      "de bombe");
		exit(1);
	}
	
	pthread_detach(bombe->tid);
}

void sigintBombe(int sig);
void* threadBombe(void* v_bombe)
{
	S_BOMBE* bombe = (S_BOMBE*) v_bombe;
	
	pthread_cleanup_push(threadBombeCleanup, v_bombe);
	
	// Active la gestion du SIGINT
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	Action.sa_handler = sigintBombe;
	sigaction(SIGINT, &Action, NULL);
	
	printf("%d. Lancement bombe (colonne %d, ligne : %d)\n", pthread_self(), bombe->colonne, bombe->ligne);
	
	Trace("%d. Lock bombe ...", pthread_self());
	pthread_mutex_lock(&mutexGrille);
	pthread_mutex_lock(&mutexMissiles);
	pthread_mutex_lock(&mutexAliens);
	pthread_mutex_lock(&mutexBombes);
	Trace("%d. OK Lock bombe ...", pthread_self());
	
	insereBombe(bombe);
	
	while (bombe->ligne < NB_LIGNE) {
		if (tab[bombe->ligne][bombe->colonne] == ALIEN) {
			// Juste attendre ...
			Trace("La bombe attends ...");
		} else if (tab[bombe->ligne][bombe->colonne] != VIDE) {
			Trace("OK1");
			switch (tab[bombe->ligne][bombe->colonne]) {
			case BOUCLIER2:
				tab[bombe->ligne][bombe->colonne] = VIDE;
				DessineVide(bombe->ligne, bombe->colonne);
				break;
			case BOUCLIER1:
				tab[bombe->ligne][bombe->colonne] = BOUCLIER2;
				DessineBouclier(bombe->ligne, bombe->colonne, 2);
				break;
			case CANON1:
				kill(getpid(), SIGQUIT);
				break;
			};
	
			Trace("%d. Unlock bombe 3...", pthread_self());
			pthread_mutex_unlock(&mutexGrille);
			pthread_mutex_unlock(&mutexMissiles);
			pthread_mutex_unlock(&mutexAliens);
			pthread_mutex_unlock(&mutexBombes);
			pthread_exit(NULL);
			return NULL;
		} else {
			Trace("OK2");
			tab[bombe->ligne][bombe->colonne] = BOMBE;
			DessineBombe(bombe->ligne, bombe->colonne);
		}
		
		Trace("%d. Unlock bombe 2...", pthread_self());
		pthread_mutex_unlock(&mutexGrille);
		pthread_mutex_unlock(&mutexMissiles);
		pthread_mutex_unlock(&mutexAliens);
		pthread_mutex_unlock(&mutexBombes);
		
		milisec_sleep(BOMBE_SLEEP);
		
		Trace("%d. Lock bombe 2 ...", pthread_self());
		pthread_mutex_lock(&mutexGrille);
		pthread_mutex_lock(&mutexMissiles);
		pthread_mutex_lock(&mutexAliens);
		pthread_mutex_lock(&mutexBombes);
		Trace("%d. OK Lock bombe 2 ...", pthread_self());
		
		bombe->ligne += 1;
		if (bombe->ligne >= NB_LIGNE // Si déplacement possible, efface
		    || tab[bombe->ligne][bombe->colonne] != ALIEN) {
			tab[bombe->ligne - 1][bombe->colonne] = VIDE;
			DessineVide(bombe->ligne - 1, bombe->colonne);
		}
	}
	
	Trace("%d. Unlock bombe 1 ...", pthread_self());
	pthread_mutex_unlock(&mutexGrille);
	pthread_mutex_unlock(&mutexMissiles);
	pthread_mutex_unlock(&mutexAliens);
	pthread_mutex_unlock(&mutexBombes);
	pthread_cleanup_pop(1);
	pthread_exit(NULL);
}

void threadBombeCleanup(void* v_bombe)
{
	S_BOMBE* bombe = (S_BOMBE*) v_bombe;
	
	Trace("Fin du bombe");
	
	// Peut provoquer un deadlock :
	//pthread_mutex_lock(&mutexGrille);
	//pthread_mutex_lock(&mutexBombes);
	
	retireBombe(bombe);
}

void sigintBombe(int sig)
{	
	Trace("Bombe : Reception du signal SIGINT");
	pthread_exit(NULL);
}

void insereBombe(S_BOMBE* bombe)
{	
	bombe->suivant = bombes;
	bombes = bombe;
}

S_BOMBE* getBombe(int ligne, int colonne)
{
	S_BOMBE* bombe = bombes;
	while (bombe != NULL) {
		if (bombe->ligne == ligne && bombe->colonne == colonne)
			return bombe;
		
		bombe = bombe->suivant;
	}
	
	return NULL;
}

pthread_t getTidBombe(int ligne, int colonne)
{
	S_BOMBE* bombe = getBombe(ligne, colonne);
	if (bombe == NULL) 
		return -1;
	else
		return bombe->tid;
}

void retireBombe(S_BOMBE* bombe)
{	
	S_BOMBE* iBombe = bombes;
	S_BOMBE** old = &bombes;
	while (iBombe != NULL) {
		if (iBombe == bombe) {
			*old = bombe->suivant;
			Trace("Free bombe");
			free(bombe);
			break;
		} else {
			old = &(iBombe->suivant);
			iBombe = iBombe->suivant;
		}
	}
}