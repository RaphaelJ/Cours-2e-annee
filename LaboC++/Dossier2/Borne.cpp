#include <qapplication.h>
#include "BorneReservation.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <signal.h>

#include "Defines.h"
#include "Commons.h"
#include "Ecran.h"

int IdQueue;
int IdShared;
char* SharedMemory;

int ProcessReservation = 0;

char *NomProcess = "Borne";

pid_t ServerPid;
EVENT_TYPE TypesEvenements[MAX_EVENTS];

BorneReservation *Connect;

void OuvrirQueue();
void OuvrirMemoirePartagee();
void SynchroniserBorne();

void AfficherMenuPrincipal(int);
void NouvellePub(int);

void Quitter(int Sig);

int main(int argc, char **argv)
{
	printf("Borne id : %d\n", getpid());
	
	// Remet à zéro les signaux
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	
	// Initialise le signal d'annulation
	Action.sa_handler = AfficherMenuPrincipal;
	if (sigaction(SIGNAL_RESERVATION_ANNULEE, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGNAL_RESERVATION_ANNULEE", 1);
		exit(1);
	}
	
	// Initialise le signal de changement de pub
	Action.sa_handler = NouvellePub;
	if (sigaction(SIGNAL_NOUVELLE_PUB, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGNAL_NOUVELLE_PUB", 1);
		exit(1);
	}
	
	//// Initialise le signal de fin d'éxécution
	Action.sa_handler = Quitter;
	if (sigaction(SIGINT, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGINT", 1);
		exit(1);
	}
	
	OuvrirQueue();
	OuvrirMemoirePartagee();
	
	QApplication a(argc, argv);
	Connect = new BorneReservation();
	
	NouvellePub(0);
	SynchroniserBorne();
	
	Connect->show();
	return a.exec();
}

// Ouvre la queue de message utilisée pour les communications
// avec le serveur.
void OuvrirQueue()
{
	// Se connecte à la queue du serveur
	if ((IdQueue = msgget(LireCleQueue(), 0)) == -1) {
		TraceErreur("Message queue non cree (READQ)");
		exit(1);
	}
}

// Ouvre la mémoire partagée utilisée pour le transfert des
// publicités
void OuvrirMemoirePartagee()
{
	// Se connecte à la shared memoire du serveur
	if ((IdShared = shmget((key_t) 1234, MAX_PUB_SIZE, 0)) == -1) {
		TraceErreur("Mémoire partagée non créée (READQ)");
		exit(1);
	}
	
	if ((SharedMemory = (char*) shmat(IdShared, 0, SHM_RDONLY)) == (char*) -1) {
		TraceErreur("Impossible d'attacher la mémoire partagée");
		exit(1);
	}
}

// Synchronise la borne avec le serveur.
// (obtient le pid du serveur et la liste des types
// d'événements)
void SynchroniserBorne()
{	
	// Informe le serveur du démarrage de la borne
	MESSAGE msg;
	msg.dest = SERVER_RECV;	
	msg.type = NOUVELLE_BORNE;
	msg.sender = getpid();
	
	if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
		TraceErreur("Erreur de msgsnd()...");
		exit(1);
	}
	
	Trace("Message de synchronisation envoyé au serveur");
	
	// Recoit les informations du serveur
	if (msgrcv(IdQueue, &msg, MESSAGE_SIZE, getpid(), 0) == 0) {
		TraceErreur("Erreur de msgsnd()...");
		exit(1);
	}
	
	ServerPid = msg.sender;
	
	// Enregistre la liste des types d'événements
	memcpy(TypesEvenements, msg.data.types, sizeof TypesEvenements);
	
	Trace("Informations du serveur obtenues (pid = %d)", ServerPid);
	AfficherMenuPrincipal(0);
}

void AfficherMenuPrincipal(int Sig)
{	
	char buff[1000];
	buff[0] = '\0';
	
	ProcessReservation = 0;
	
	for (int i = 0; i < MAX_TYPES; i++) {
		if (TypesEvenements[i].nom[0] != '\0') {
			char tempBuff[1000];
			
			sprintf(tempBuff, "%2d - %-20s\n",
				i + 1, TypesEvenements[i].nom);
			
			strcat(buff, tempBuff);
		}
	}
	
	Connect->AffichageMenu(buff);
}

void NouvellePub(int Sig)
{
	Connect->AffichagePublicite(SharedMemory);
	
	Trace("Changement de publicité (%s)", SharedMemory);
}

// Ferme la borne et informe le serveur
void Quitter(int Sig)
{
	Trace("Extinction de la borne (signal %d)", Sig);
	
	// Informe le serveur de la déconnexion de la borne
	MESSAGE msg;
	msg.dest = SERVER_RECV;	
	msg.type = DECONNEXION;
	msg.sender = getpid();
	
	if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0)
		TraceErreur("Impossible d'informer le serveur (serveur éteint ?)");
	else
		Trace("Serveur informé de l'extinction de la borne");
	
	exit(0);
}
