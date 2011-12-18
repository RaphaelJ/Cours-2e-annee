/* Processu qui s'occupe de la reservation
   Denys MERCENIER
   Reservation.c
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <dirent.h>
#include <signal.h>

#include "Defines.h"
#include "Commons.h"
#include "Ecran.h"

char *NomProcess = "\tRESERVATION";

int IdQueue;

pid_t Borne;

void VerrouillerPlaces(int file);
void DeverrouillerPlaces(int file);

void ReservationExpiree(int Sig);

int main(int argc, char *argv[])
{
	MESSAGE msg;
	
	// Récupération des informations de la ligne de commande
	EVENT_TYPE eventType;
	
	Borne = atoi(argv[1]);
	strcpy(eventType.nom, argv[2]);
	IdQueue = atoi(argv[3]);
	
	// Remet à zéro les signaux
	struct sigaction Action;
	Action.sa_flags = 0;
	sigemptyset(&Action.sa_mask);
	
	// Initialise le signal d'alarme pour l'expiration de la reservation
	Action.sa_handler = ReservationExpiree;
	sigaction(SIGALRM, &Action, NULL);
	
	// Charge la liste des événements
	Trace("Lit les informations sur les %s", eventType.nom);
	
	EVENT events[MAX_EVENTS];
	char eventsDir[200];
	
	strcpy(eventsDir, EVENTS_DIR);
	strcat(eventsDir, "/");
	strcat(eventsDir, eventType.nom);
	strcat(eventsDir, "/");
	
	ListerEvenements(events, eventsDir);
	
	// Envoi de la liste des événements du type
	Trace("Transmet la liste des événements");
	
	msg.dest = Borne;
	msg.sender = getpid();
	msg.type = LISTE_EVENTS;
	
	memcpy(msg.data.events, events, sizeof events);
	
	if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
		TraceErreur("Erreur de msgsnd() ...");
		exit(1);
	}
	
	// Recoit l'événement à réserver
	alarm(DELAI_RESERVATION); // Laisse 20 secondes à l'utilisateur
	if (msgrcv(IdQueue, &msg, MESSAGE_SIZE, getpid(), 0) == -1) {
		TraceErreur("Erreur de msgrcv()...");
		exit(1);
	}
	
	alarm(0);
	
	if (msg.type == ANNULER) {
		TraceErreur("Réservation annulée");
		exit(1);
	}
	
	Trace("Réserve %d places pour %s", msg.data.menu.nPlaces,
	      events[msg.data.menu.choix - 1].nom);
	
	// Vérifie si le nombre de place est disponible,
	// verrouille le fichier de places
	char nomFichierPlaces[200];
	strcpy(nomFichierPlaces, eventsDir);
	strcat(nomFichierPlaces, events[msg.data.menu.choix - 1].nom);
	strcat(nomFichierPlaces, "/places");
	
	int fichierPlaces;
	if ((fichierPlaces = open(nomFichierPlaces, O_RDWR)) == -1) {
		TraceErreur("Erreur d'ouverture de fichier");
		exit(1);
	}
	
	VerrouillerPlaces(fichierPlaces);
	
	int placesDemandees = msg.data.menu.nPlaces;
	int placesLibres = LireNbrePlaces(fichierPlaces);
	
	msg.dest = Borne;
	msg.sender = getpid();
	
	if (placesDemandees > placesLibres) { // Stock insuffisant
		msg.type = STOCK_INSUFFISANT;
		
		if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0)
			TraceErreur("Erreur de msgsnd() ...");
		
		TraceErreur("Réservation annulée : stock insufisant");
		exit(1);
	} else { // Demande de confirmation
		msg.type = OK;
	
		if (msgsnd(IdQueue, &msg, MESSAGE_SIZE, 0) != 0) {
			TraceErreur("Erreur de msgsnd() ...");
			exit(1);
		}
		
		Trace("Demande de confirmation de la réservation envoyée");
	}
	
	// Recoit la confirmation
	alarm(DELAI_RESERVATION); // Laisse 20 secondes à l'utilisateur
	if (msgrcv(IdQueue, &msg, MESSAGE_SIZE, getpid(), 0) == -1) {
		TraceErreur("Erreur de msgrcv()...");
		exit(1);
	}
	
	alarm(0);
	
	if (msg.type == ANNULER) {
		TraceErreur("Réservation annulée");
		exit(1);
	} else {
		EcrireNbrePlaces(fichierPlaces, placesLibres - placesDemandees);
		Trace("Réservation validée");
	}
	
	DeverrouillerPlaces(fichierPlaces);
	
	close(fichierPlaces);
	
	exit(0);
}

// Verrouille l'acces au fichier du nombre de places
void VerrouillerPlaces(int file)
{
	struct flock lock;
	
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0; // Tout le fichier
	
	if (fcntl(file, F_SETLKW, &lock)) {
		TraceErreur("Erreur lors de la pose du verrou");
		exit(1);
	}
}

// Déverrouille l'acces au fichier du nombre de places
void DeverrouillerPlaces(int file)
{
	struct flock lock;
	
	lock.l_type = F_UNLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0; // Tout le fichier
	
	if (fcntl(file, F_SETLK, &lock)) {
		TraceErreur("Erreur lors de la suppression du verrou");
		exit(1);
	}
}

// Exécuté lorsqu'une transaction a fini son éxécution
void ReservationExpiree(int Sig)
{
	if (kill(Borne, SIGNAL_RESERVATION_ANNULEE))
		TraceErreur("Erreur lors de l'envoi du signal d'annulation");
	else
		TraceErreur("Transaction expirée");
	
	exit(1);
}