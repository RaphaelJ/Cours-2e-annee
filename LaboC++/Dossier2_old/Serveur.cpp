/* Processus serveur 
   Denys Mercenier
   Serveur.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <dirent.h>
#include <setjmp.h>
#include <wait.h>

#define SERVEUR

#include "Defines.h"
#include "Commons.h"
#include "Ecran.h"

int IdQueue;
int IdShared;

jmp_buf Env;

char *NomProcess = "SERVEUR";

pid_t Bornes[MAX_BORNES] = { 0 };

EVENT_TYPE TypesEvenements[MAX_TYPES];

void LancerPublicite();

void BouclePrincipale();

void Quitter(int Sig);
void FinFils(int Sig);
void NouvellePub(int Sig);

void SynchroniserBorne(pid_t borne);
void GererReservation(pid_t borne, int choix);

int main(int argc, char *argv[])
{	
	// Lance le serveur en daemon
	// Sauf si option -f (foreground) activée
	if (argc <= 1 || strcmp(argv[1], "-f") != 0) {
		int idFils;
		if ((idFils = fork()) == -1) {
			TraceErreur("Err. de fork()");
			exit(1);
		}
		
		if (idFils) { // Processus père
			Trace("Démarrage en daemon");
			exit(0);
		}
		
		// Ecris les erreurs dans le fichier de log
		FILE* fErr;
		if ((fErr = fopen(LOG, "w")) == NULL) {
			TraceErreur("Err. d'ouverture du fichier de log", 1);
			exit(1);
		}
		
		// Remplace stderr par le log
		if (dup2(fileno(fErr), fileno(stderr)) == -1) {
			TraceErreur("(Ddms) Err. de dup2()", 1);
			exit(1);
		}
	}
	
	// Creation des ressources
	Trace("Creation des ressources ...");
	
	if ((IdQueue = msgget((key_t) LireCleQueue(), IPC_CREAT | IPC_EXCL | 0600)) == -1) {
		TraceErreur("Queue non créée (READQ)");
		exit(1);
	}
	Trace("Queue de message ouverte");
	
	if ((IdShared = shmget((key_t) 1234, MAX_PUB_SIZE, IPC_CREAT | IPC_EXCL | 0600)) == -1) {
		TraceErreur("Mémoire partagée non créée (READQ)");
		exit(1);
	}
	Trace("Mémoire partagée ouverte");
	
	Trace("Listage du dossier %s", EVENTS_DIR);
	
	ListerTypesEvenements(TypesEvenements);

	Trace("Liste des événements lue");
	
	struct sigaction Action;
	sigemptyset(&Action.sa_mask);
	Action.sa_flags = 0;
	
	// Initialise le signal de changement de pub
	Action.sa_handler = NouvellePub;
	if (sigaction(SIGNAL_NOUVELLE_PUB, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGNAL_NOUVELLE_PUB", 1);
		exit(1);
	}
	
	// Signal de fermeture du serveur
	Action.sa_handler = Quitter;
	if (sigaction(SIGINT, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGINT", 1);
		exit(1);
	}
	
	// Signal de fermeture d'un des fils
	Action.sa_handler = FinFils;
	if (sigaction(SIGCHLD, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGCHLD", 1);
		exit(1);
	}

	Trace("Signaux armés");
	
	LancerPublicite();
	
	Trace("Serveur disponible");
	
	BouclePrincipale();
	
	return 0;
}

// Lance le processus de gestion des publicités
void LancerPublicite()
{
	int idFils;
	if ((idFils = fork()) == -1) {
		TraceErreur("Err. de fork()... (CONSULT)");
		exit(1);
	}
	
	if (idFils == 0) { // Fils
		Trace("Fork lancé sur le PID %d pour la gestion des publicités", getpid());
		
		char idSharedAlpha[15];
		
		sprintf(idSharedAlpha, "%d", IdShared);
		
		int e = execlp("./Publicite", "./Publicite", idSharedAlpha, (char*) NULL);

		TraceErreur("Erreur de exec %d", e);
		exit(1);
	}
}

// Boucle de réception des requête des bornes
void BouclePrincipale()
{
	for (;;) {
		MESSAGE msg;
		
		sigsetjmp(Env, 1);
		
		if (msgrcv(IdQueue, &msg, MESSAGE_SIZE, SERVER_RECV, 0) == -1) {
			TraceErreur("Erreur de msgrcv");
			exit(1);
		}
		
		sigsetjmp(Env, 1);
		
		switch (msg.type) {
		case NOUVELLE_BORNE:
			Trace("Nouvelle borne (pid = %d)", (int) msg.sender);
			
			SynchroniserBorne(msg.sender);
			
			break;
		case CONSULTER_EVENTS:
			Trace("Réception d'une demande de consultation (pid = %d)", (int) msg.sender);
			
			GererReservation(msg.sender, msg.data.menu.choix);
			
			break;
		case DECONNEXION:
			Trace("Borne déconnectée (pid = %d)", (int) msg.sender);
			
			for (int i = 0; i < MAX_BORNES; i++) {
				if (Bornes[i] == (int) msg.sender) {
					Bornes[i] = 0;
					break;
				}
			}
			
			break;
		default:
			Trace("Requete non connue...");
			break;
		}
	}
}

// Quitte le serveur et ses ressources
void Quitter(int Sig)
{
	Trace("Extinction du serveur (signal %d)", Sig);
	
	// Fermeture des ressources du serveur
	msgctl(IdQueue, IPC_RMID, 0);
	shmctl(IdShared, IPC_RMID, 0);
	
	// Tue les sous-processus
	kill(-getpgid(0), SIGINT);
	// Tue les bornes
	for (int i = 0; i < MAX_BORNES; i++) {
		if (Bornes[i] != 0)
			kill(Bornes[i], SIGINT);
	}
	
	exit(0);
}

// Ferme le processus fils zombie
void FinFils(int Sig)
{
	Trace("Extinction du fils (PID = %d)", wait(NULL));
	
	siglongjmp(Env, 0);
}

// Transmet le signal de nouvelle pub à l'esemble des bornes
void NouvellePub(int Sig)
{
	for (int i = 0; i < MAX_BORNES; i++) {
		if (Bornes[i] != 0) {
			kill(Bornes[i], SIGNAL_NOUVELLE_PUB);
		}
	}
	
	Trace("Nouvelle pub : transmission du signal aux bornes");
	
	siglongjmp(Env, 0);
}

// Synchronise la borne avec le serveur.
// (envoie le pid du serveur et la liste des types d'événements)
void SynchroniserBorne(pid_t borne)
{
	// Ajoute la borne à la liste des bornes connectées
	int i;
	for (i = 0; i < MAX_BORNES; i++) {
		if (Bornes[i] == 0) {
			Bornes[i] = borne;
			break;
		}
	}
	if (i == MAX_BORNES) {
		TraceErreur("Plus de slot disponible pour de nouvelles bornes");
		exit(1);
	}
	
	// Envoie les informations au client
	MESSAGE msg;
	msg.dest = borne;
	msg.type = LISTE_TYPES;
	msg.sender = getpid();
	memcpy(msg.data.types, TypesEvenements, sizeof TypesEvenements);
	
	if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
		TraceErreur("Erreur de msgsnd()...");
		exit(1);
	}
	
	Trace("Message de synchronisation envoyé à la borne");
}

// Gère le processus de réservation d'une borne
void GererReservation(pid_t borne, int choix)
{
	int idFils;
	if ((idFils = fork()) == -1) {
		TraceErreur("Err. de fork()... (CONSULT)");
		exit(1);
	}
	
	if (idFils == 0) { // Fils
		Trace("Fork lancé sur le PID %d pour la gestion de la réservation", getpid());
		
		char borneAlpha[15], idQueueAlpha[15];
		
		sprintf(borneAlpha, "%d", borne);
		sprintf(idQueueAlpha, "%d", IdQueue);
		
		int e = execlp("./Reservation", "./Reservation", borneAlpha,
		               TypesEvenements[choix - 1].nom, idQueueAlpha, (char*) NULL);

		TraceErreur("Erreur de exec %d", e);
		exit(1);
	}
}
