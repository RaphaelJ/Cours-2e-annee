/* Processu qui s'occupe de la reservation
   Denys MERCENIER
   Commons.c
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
#include "Ecran.h"
#include "Commons.h"
#include "DossierFichiersOctobre/LinkedFile.h"

// Lit le numero de la clé à l'aide du dossier 1
key_t LireCleQueue()
{
	LinkedFile<int> f(QUEUE_KEY_FILE);
	
	//int v = 1234;
	//f.add("QUEUE_KEY", &v, 1);
	
	// LinkedFile manipule des vecteurs de T
	int val = *(f.search("QUEUE_KEY").e1);
	delete f.search("QUEUE_KEY").e1;
	
	return (key_t) val;
}

// Lit les différents type d'événements disponibles dans le dossier
// EVENTS_DIR
void ListerTypesEvenements(EVENT_TYPE types[MAX_TYPES])
{
	struct dirent* curr;
	DIR* dir;
	
	dir = opendir(EVENTS_DIR);
	int i = 0;
	while (i < MAX_TYPES) {
		if ((curr = readdir(dir)) != NULL) {
			// Passe . et ..
			if (strcmp(curr->d_name, ".") != 0
			    && strcmp(curr->d_name, "..") != 0) {
				strcpy(types[i].nom, curr->d_name);
				
				i++;
			}
		} else {
			types[i].nom[0] = '\0';
			
			i++;
		}
	}
	closedir(dir);
}

// Charge l'ensemble des événements d'une catégorie
void ListerEvenements(EVENT events[MAX_EVENTS], char eventsDir[200])
{
	// Charge la liste des événements
	struct dirent* curr;
	DIR* dir;
	
	dir = opendir(eventsDir);
	int i = 0;
	while (i < MAX_EVENTS) {
		if ((curr = readdir(dir)) != NULL) {
			// Passe . et ..
			if (strcmp(curr->d_name, ".") != 0
			    && strcmp(curr->d_name, "..") != 0) {
				// Lit les informations sur l'événement
				Trace("Lit les informations sur %s", curr->d_name);
				
				strcpy(events[i].nom, curr->d_name);
				
				char eventDir[200];
				strcpy(eventDir, eventsDir);
				strcat(eventDir, curr->d_name);
				
				LireInfosEvenement(&events[i], eventDir);
				
				i++;
			}
		} else {
			events[i].nom[0] = '\0';
			
			i++;
		}
	}
	closedir(dir);
}


void ListerEvenements(EVENT events[MAX_EVENTS], EVENT_TYPE type)
{
	char eventsDir[200];
	
	strcpy(eventsDir, EVENTS_DIR);
	strcat(eventsDir, "/");
	strcat(eventsDir, type.nom);
	strcat(eventsDir, "/");
	
	ListerEvenements(events, eventsDir);
}

// Lit dans les différents fichiers les infos (nbre de places,
// date et localisation) d'un événement.
void LireInfosEvenement(EVENT* event, char eventDir[200])
{
	char filePath[200];
	int file, n;
	
	// Lit la date
	strcpy(filePath, eventDir);
	strcat(filePath, "/date");
	
	if ((file = open(filePath, O_RDONLY)) == -1) {
		TraceErreur("Erreur d'ouverture de fichier");
		exit(1);
	}
	if ((n = read(file, &(event->date), sizeof event->date - 1)) <= 0) {
		TraceErreur("Erreur de lecture");
		exit(1);
	}
	event->date[n] = '\0';
	
	close(file);
	
	// Lit la localisation
	strcpy(filePath, eventDir);
	strcat(filePath, "/localisation");
	
	if ((file = open(filePath, O_RDONLY)) == -1) {
		TraceErreur("Erreur d'ouverture de fichier");
		exit(1);
	}
	if ((n = read(file, &(event->localisation), sizeof event->localisation - 1)) <= 0) {
		TraceErreur("Erreur de lecture");
		exit(1);
	}
	event->localisation[n] = '\0';
	
	close(file);
	
	// Lit le nombre de places
	strcpy(filePath, eventDir);
	strcat(filePath, "/places");
	
	if ((file = open(filePath, O_RDONLY)) == -1) {
		TraceErreur("Erreur d'ouverture de fichier");
		exit(1);
	}
	
	event->libre = LireNbrePlaces(file);
	
	close(file);
}

// Lit le nombre de places disponibles dans le fichier places
int LireNbrePlaces(int file)
{
	if (lseek(file, 0, SEEK_SET) == -1) {
		TraceErreur("Erreur de lseek()");
		exit(1);
	}
	
	int n;
	char placesAplha[11];
	if ((n = read(file, placesAplha, 10)) <= 0) {
		TraceErreur("Erreur de lecture");
		exit(1);
	}
	placesAplha[n] = '\0';
	
	return atoi(placesAplha);
}

// Ecrit le nombre de places disponibles
void EcrireNbrePlaces(int file, int nbrePlaces)
{
	if (lseek(file, 0, SEEK_SET) == -1) {
		TraceErreur("Erreur de lseek()");
		exit(1);
	}
	
	char placesAplha[11];
	sprintf(placesAplha, "%d", nbrePlaces);
	
	if (write(file, placesAplha, strlen(placesAplha) + 1) <= 0) {
		TraceErreur("Erreur d'écriture");
		exit(1);
	}
}