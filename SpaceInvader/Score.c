#include "Score.h"

pthread_mutex_t mutexScore;
pthread_cond_t condScore;

int score1 = 0;
int score2 = 0;

void initialiseScore()
{
	pthread_mutex_init(&mutexScore, NULL);
	pthread_cond_init(&condScore, NULL);
	
	pthread_t thread_id;
	if (pthread_create(&thread_id, NULL, threadScore, NULL) != 0) {
		Trace("Erreur lors du lancement du thread de gestion"
		      "du score"
		);
		exit(1);
	}
	
	pthread_detach(thread_id);
}

void terminerScore()
{
	pthread_cond_destroy(&condScore);
	pthread_mutex_destroy(&mutexScore);
}

// Active la gestion de la mise à jour du score
void* threadScore(void* vdata)
{
	pthread_mutex_lock(&mutexScore);
	
	for (;;) {
		pthread_cond_wait(&condScore, &mutexScore);
		
		Trace("Score du joueur 1: %d", score1);
		Trace("Score du joueur 2: %d", score2);
	}
	
	pthread_mutex_consistent(&mutexScore);
}
