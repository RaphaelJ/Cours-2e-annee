/* Processus serveur 
   Denys Mercenier
   GestServ.cpp
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
#include <sys/stat.h>
#include <dirent.h>
#include <setjmp.h>
#include <wait.h>

#include "Defines.h"
#include "Commons.h"
#include "Ecran.h"

char *NomProcess = "GESTSERV";

void Quitter(int Sig);
void Menu();

void EntrerChaine(char* texte, char* valeur);
void EntrerEvenement(EVENT& event);

void EnregistrerEvenement(EVENT& event, EVENT_TYPE type);
void SupprimerEvenement(EVENT& event, EVENT_TYPE type);

EVENT_TYPE ChoisirTypeEvenement();

void AjouterEvenement();
void ModifierEvenement();

void AjouterPublicite();
void ModifierPublicite();

int main(int argc, char *argv[])
{
	// Vérifie le mot de passe
	int mdp;
	printf("Mot de passe: ");
	scanf("%d", &mdp);
	if (mdp != 1234) {
		TraceErreur("Mot de passe invalide");
		exit(1);
	}
	
	struct sigaction Action;
	sigemptyset(&Action.sa_mask);
	Action.sa_flags = 0;
	
	// Signal de fermeture
	Action.sa_handler = Quitter;
	if (sigaction(SIGINT, &Action, NULL) == -1) {
		TraceErreur("Err. signal SIGINT", 1);
		exit(1);
	}
	
	Menu();

	return 0;
}

// Quitte le processus de gestion
void Quitter(int Sig)
{
	Trace("Extinction du processus de gestion (signal %d)", Sig);
	
	exit(0);
}

void Menu()
{
	int choix;
	do {
		printf("Que faire :\n");
		printf("-----------\n");
		printf("1. Ajouter un événement\n");
		printf("2. Modifier/Supprimer un événement\n");
		printf("3. Ajouter une publicité\n");
		printf("4. Modifier/Supprimer une publicité\n");
		printf("5. Quitter\n");
		
		printf("Choix : ");
		scanf("%d", &choix);
		
		switch (choix) {
		case 1:
			AjouterEvenement();
			break;
		case 2:
			ModifierEvenement();
			break;
		case 3:
			AjouterPublicite();
			break;
		case 4:
			ModifierPublicite();
			break;
		}
	} while (choix != 5); 
}

void EntrerChaine(char* texte, char* valeur)
{
	if (valeur[0] != '\0') { // Modifier
		char entree[255];
		printf("%s [%s] : ", texte, valeur);
		scanf("%s", entree);
		
		if (entree[0] == '\0') // Ne change pas la valeur
			strcpy(valeur, entree);
	} else { // Créer
		printf("%s : ", texte);
		scanf("%s", valeur);
	}
}

// Demande à l'utilisateur les données d'un événement
void EntrerEvenement(EVENT& event)
{
	char libresAlpha[11];
	if (event.nom[0] != '\0')
		sprintf(libresAlpha, "%d", event.libre);
	else
		libresAlpha[0] = '\0';
	
	EntrerChaine("Nom", event.nom);
	EntrerChaine("Date", event.date);
	EntrerChaine("Localisation", event.localisation);
	
	EntrerChaine("Nbre de places libres", libresAlpha);
	event.libre = atoi(libresAlpha);
}

// Enregistre les données d'un événement
// Crée le dossier s'il n'existe pas
void EnregistrerEvenement(EVENT& event, EVENT_TYPE type)
{
	char eventDir[200];
	strcpy(eventDir, EVENTS_DIR);
	strcat(eventDir, "/");
	strcat(eventDir, type.nom);
	strcat(eventDir, "/");
	strcat(eventDir, event.nom);
	strcat(eventDir, "/");
	
	// Crée le dossier
	mkdir(eventDir, 0755); // -1 si existe
	
	FILE* f;
	char fileName[200];
	strcpy(fileName, eventDir);
	strcat(fileName, "/date");
	
	f = fopen(fileName, "w");
	
	if (fwrite(event.date, 1, strlen(event.date) + 1, f) == 0) {
		Trace("Erreur d'écriture de la date");
		exit(1);
	}
	
	fclose(f);
	
	strcpy(fileName, eventDir);
	strcat(fileName, "/localisation");
	
	f = fopen(fileName, "w");
	
	if (fwrite(event.localisation, 1,
	           strlen(event.localisation) + 1, f) == 0) {
		Trace("Erreur d'écriture de la localisation");
		exit(1);
	}
	
	fclose(f);
	
	char libreAlpha[12];
	sprintf(libreAlpha, "%d", event.libre);
	strcpy(fileName, eventDir);
	strcat(fileName, "/libre");
	
	f = fopen(fileName, "w");
	
	if (fwrite(libreAlpha, 1, strlen(libreAlpha) + 1, f) == 0) {
		Trace("Erreur d'écriture du nombre de places");
		exit(1);
	}
	
	fclose(f);
}

// Supprime un événement
void SupprimerEvenement(EVENT& event, EVENT_TYPE type)
{
	char eventDir[200];
	strcpy(eventDir, EVENTS_DIR);
	strcat(eventDir, "/");
	strcat(eventDir, type.nom);
	strcat(eventDir, "/");
	strcat(eventDir, event.nom);
	strcat(eventDir, "/");
	
	// Supprime le dossier
	remove(eventDir);
}

// Laisse l'utilisateur choisir un type d'événement
EVENT_TYPE ChoisirTypeEvenement()
{
	EVENT_TYPE types[MAX_TYPES];
	
	ListerTypesEvenements(types);
	int type;
	do {
		printf("Type d'événement:\n");
		for (int i = 1; i <= MAX_TYPES; i++) {
			if (types[i - 1].nom[0] != '\0') {
				printf("%d %s\n", i,
				       types[i - 1].nom);
			}
		}
		
		printf("Choix: ");
		scanf("%d", &type);
	} while (type <= 0 || type > MAX_TYPES
	         || types[type - 1].nom == '\0');

	return types[type - 1];
}

void AjouterEvenement()
{
	EVENT_TYPE type = ChoisirTypeEvenement();
	
	EVENT event;
	
	event.nom[0] = '\0';
	event.date[0] = '\0';
	event.localisation[0] = '\0';
	
	EntrerEvenement(event);
	
	EnregistrerEvenement(event, type);
}

void ModifierEvenement()
{
	EVENT_TYPE type = ChoisirTypeEvenement();
	
	EVENT events[MAX_EVENTS];
	ListerEvenements(events, type);
	
	int evenement;
	do {
		printf("Evénements:\n");
		for (int i = 1; i <= MAX_EVENTS; i++) {
			if (events[i - 1].nom[0] == '\0') {
				printf("%d %s\n", i,
				       events[i - 1].nom);
			}
		}
		
		printf("Choix: ");
		scanf("%d", &evenement);
	} while (evenement <= 0 || evenement > MAX_EVENTS
	         || events[evenement - 1].nom == '\0');

	printf("Entrez 0 pour le nombre de places pour supprimer\n");
	EntrerEvenement(events[evenement - 1]);
	
	if (events[evenement - 1].libre == 0) {  // Supprimer
		SupprimerEvenement(events[evenement - 1], type);
	} else // Modifier
		EnregistrerEvenement(events[evenement - 1], type);
}

void AjouterPublicite()
{
}

void ModifierPublicite()
{
}