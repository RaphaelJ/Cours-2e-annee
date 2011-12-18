/* Processus serveur 
   Denys Mercenier
   Publicite.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <dirent.h>
#include <setjmp.h>
#include <wait.h>

#include "Defines.h"
#include "Ecran.h"

int idFils;
int IdQueue;
jmp_buf Env;

char *NomProcess = "PUB";

struct {
	char message[MAX_PUB_SIZE];
	int seconds;
} Pubs[MAX_PUBS];

char* Shared;

void ChangePubs();
void Quitter(int Sig);

int main(int argc, char *argv[])
{
	// Récupère l'ID de la mémoire partagée via la ligne de commande
	int IdShared = atoi(argv[1]);
	
	// Charge les publicités contenues dans le fichier
	FILE* f;
	
	if ((f = fopen(PUBS_FILE, "r")) == NULL) {
		TraceErreur("Impossible d'ouvrir le fichier de publicités");
		exit(1);
	}
	
	for (int i = 0; i < MAX_PUBS; i++) {
		if (fgets(Pubs[i].message, MAX_PUB_SIZE - 1, f) != NULL) {
			char secondesAlpha[15];
			if (fgets(secondesAlpha, 14, f) == NULL) {
				TraceErreur("Impossible de lire le nombre de places");
				exit(1);
			}
			
			Pubs[i].seconds = atoi(secondesAlpha);
		} else
			Pubs[i].message[0] = '\0';
	}
	
	Trace("Publicités lues");
	
	// S'attache à la mémoire partagée
	if ((Shared = (char*) shmat(IdShared, 0, 0)) == (char*) -1) {
		TraceErreur("Impossible d'attacher la mémoire partagée");
		exit(1);
	}
	
	Trace("Mémoire attachée");
	
	// Arme le d'interruption
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	
	Action.sa_handler = Quitter;
	if (sigaction(SIGINT, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGINT", 1);
		exit(1);
	}
	
	ChangePubs();
}

// Change la publicité et envoie un signal au serveur
void ChangePubs()
{
	int iPub = 0;
	for (;;) {
		Trace("Changement de publicité ([%d] %d secondes)", iPub,
		      Pubs[iPub].seconds);
		
		strcpy(Shared, Pubs[iPub].message);
		kill(getpgid(0), SIGNAL_NOUVELLE_PUB);
		
		sleep(Pubs[iPub].seconds);
		
		iPub = (iPub + 1) % MAX_PUBS;
	
		if (Pubs[iPub].message[0] == '\0') // Fin du fichier
			iPub = 0;	
	}
}

// Détache la mémoire partagée
void Quitter(int Sig)
{
	Trace("Extinction du processus de publicité");
	
	if (shmdt((void*) Shared) == -1) {
		TraceErreur("Impossible de détacher la mémoire partagée");
		exit(1);
	}
	
	exit(0);
}
