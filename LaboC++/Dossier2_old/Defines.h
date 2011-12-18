#ifndef DEFINES_H
#define DEFINES_H

typedef enum {
	// Borne :
	NOUVELLE_BORNE,
	// Serveur :
	LISTE_TYPES, // Envoie les différents types d'événements
	
	// Borne :
	CONSULTER_EVENTS, // Consulte/envoie les différents événements d'un type
	// Réservation :
	LISTE_EVENTS,
	
	// Borne :
	RESERVATION, // Réserve un événement
	// Réservation :
	OK, // Assez de places pour l'événement
	STOCK_INSUFFISANT, // Pas assez de places
	
	// Borne :
	CONFIRMATION, // Valider la réservation
	ANNULER, // Annuler la réservation
	
	// Borne :
	DECONNEXION, // Extinction d'une borne
} MESSAGES_TYPES;

typedef long RECV;

#define SERVER_RECV 1L // Le serveur prends tous les messages à destination de 1

typedef struct {
	char nom[30];
} EVENT_TYPE;

typedef struct {
	char nom[30];
	char date[20];
	char localisation[20];
	int libre;
} EVENT;

typedef struct {
	int choix;
	int nPlaces;
} MENU;

#define MAX_TYPES 10
#define MAX_EVENTS 10
#define MAX_BORNES 10
#define MAX_PUBS 10
#define MAX_PUB_SIZE 500

typedef union {
	EVENT_TYPE types[MAX_TYPES];
	EVENT events[MAX_EVENTS];
	MENU menu;
} MESSAGE_DATA;

typedef struct {
	RECV dest;
	MESSAGES_TYPES type;
	pid_t sender;
	MESSAGE_DATA data;
} MESSAGE;

#define MESSAGE_SIZE sizeof (MESSAGE) - sizeof (RECV)
#define DATA_SIZE(l) l - sizeof (MESSAGES_TYPES) - sizeof (pid_t)
#define DELAI_RESERVATION 20

#define LOG "Trace.log"

#define SIGNAL_NOUVELLE_PUB SIGUSR2 // Envoyé aux processus du groupe lors du changement de pub
#define SIGNAL_RESERVATION_ANNULEE SIGUSR1 // Envoyé par le processus de réservation après les 20 secondes

#define EVENTS_DIR "../events" // Dossier contenent les fichier de données de différents événements
#define PUBS_FILE "../Publicite.dat" // Fichier contenant les publicités

#define QUEUE_KEY_FILE "../Queue.dat" // Fichier contenant le n° de la clé de la queue

#endif