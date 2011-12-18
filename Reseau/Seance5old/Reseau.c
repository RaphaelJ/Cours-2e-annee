#include "Reseau.h"

// Connecte le client
// Retourne un descripteur représentant la connexion
// physique
int ConnecterClient(int argc, char* argv[], struct Physique* conn)
{
	bzero(conn, sizeof(struct Physique));
	if (argc != 5) {
		printf("ConnecterClient: parametres CLI incorrects.\n");
		exit(1);
	}
	return CreerConnexion(conn, argv[1], atoi(argv[2]),
			      argv[3], atoi(argv[4]));
}

// Connecte le serveur
// Retourne un descripteur représentant la connexion
// physique
int ConnecterServeur(int argc, char* argv[], struct Physique* conn)
{
	bzero(conn, sizeof(struct Physique));
	if (argc != 3) {
		printf("ConnecterServeur: parametres CLI incorrects.\n");
		
		exit(1);
	}
	
	return CreerConnexion(conn, argv[1], atoi(argv[2]), NULL, 0);
}

int EnvoiClient(struct Physique* conn, void* data, int taille)
{
	return VersCouchePhysique(conn, data, taille);
}

int EnvoiServeur(struct Physique* conn, void* data, int taille)
{
	return Repondre(conn, data, taille);
}

int Reception(struct Physique* conn, void* data, int* taille)
{
	return OrigineCouchePhysique(conn, data, taille);
}

// Crée un gestionnaire d'événement sur *un* descripteur
// de fichier
int CreerEvenement(int desc, struct gEvenement* even, int secsTimeOut)
{
	return CreerEvenementMilisecs(desc, even, secsTimeOut, 0);
}

int CreerEvenementMilisecs(int desc, struct gEvenement* even, int secsTimeOut,
                   int miliSecsTimeOut)
{
	#define NB_DESC 100
	/*static*/ int descsLecture[NB_DESC];
	/*static*/ int descsEcriture[NB_DESC];
	bzero(descsLecture, sizeof descsLecture);
	bzero(descsEcriture, sizeof descsEcriture);
	
	descsLecture[desc] = 1;
	descsLecture[0] = 1;
	
	return PrepareEvenement(even, descsLecture, descsEcriture,
	                        NB_DESC, secsTimeOut, miliSecsTimeOut);
}

// Attends la libération de la ressource ou du timer
// 1 -> ok, desc indique le descripteur ayant du contenu en lecture
//     (0 si clavier). TIMEOUT si timer.
// -1 -> probleme
// 0 -> timeout de even
int AttendreTimer(struct gEvenement* even, int* desc, struct ListeTimer** Timer)
{
	int descEcriture;

	return AttendreEvenementtm(even, desc, &descEcriture, Timer);
}

// Attends la libération d'une ressource
// 1 -> ok, desc indique le descripteur ayant du contenu en lecture
//     (0 si clavier).
// -1 -> probleme
// 0 -> timeout
int Attendre(struct gEvenement* even, int* desc)
{
	int descEcriture;
	
	return AttendreEvenement(even, desc, &descEcriture);
}

// Demande une entier à l'utilisateur en lui laissant 15 sec
// Returne false si Timeout
bool EntreeTimeOut(int* donnees)
{
	int descClavier = 0;
	struct gEvenement evenClavier;
	
	// Crée un événement pour ne pas attendre plus de 15 secs
	if (CreerEvenement(descClavier, &evenClavier, 15) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	fflush(stdout);
	switch (Attendre(&evenClavier, &descClavier)) {
	case 1:
		scanf("%d", donnees);
			
		return true;
	case 0: // Timeout		
		return false;
	case -1:
		printf("Erreur lors de l'attente de l'evenement\n");
		exit(1);
	};
}

// Transmet une requête au client et la renvoi s'il n'y a pas de réponse
// fct_demande est exécutée au départ et lance la première requête.
//	fct_demande retourne true si l'action a réussi, false sinon (timeout
//	sur l'entréee).
// fct_reception est exécutée lorsque la réponse est reçue.
void Transmettre(struct Physique* conn, int connDescPhys, FILE* f, const char* nomAction,
                 bool (*fct_demande)(FILE* f, struct Physique* conn, REQUETE* requeteEnvoyee),
		 void (*fct_reception)(FILE* f, struct Physique* conn, REQUETE requete))
{
	struct gEvenement even;
	struct ListeTimer* timers = NULL;
	
	if (CreerEvenementMilisecs(connDescPhys, &even, 0, 200000) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	int nbreTransmissions = 0;
	REQUETE requeteEnvoyee;
	
	system("clear");
	printf("Appuyez sur %c+<Enter> pour l'action \"%s\"\n",
	       tolower(nomAction[0]), nomAction);
	for (;;) {
		char Buffer[100];
		int desc;
		
		ListerFichier(f);
		
		printf("\nListe des timers: ");
		AfficheTimer(timers);
		
		int rc = AttendreTimer(&even, &desc, &timers);
		system("clear");
		if (rc == 1) { // OK
			if (desc == 0) { // Interrupt clavier
				fgets(Buffer, sizeof Buffer, stdin);
				if (nbreTransmissions > 0) {
					printf("Transaction précédente non validée\n");
				} else if (tolower(Buffer[0]) == tolower(nomAction[0])) {
					if (fct_demande(f, conn, &requeteEnvoyee)) {
						// Si pas de timeout sur l'entrée de la demande
						if (EnvoiClient(conn, &requeteEnvoyee, sizeof (REQUETE)) == -1) {
							printf("Erreur lors du renvoi des donnnées");
							exit(1);
						}
						
						timers = StopTimer(1, timers);
						timers = StartTimer(1, TIMOUT_RETRANSMISSIONS, timers);
						nbreTransmissions = 1;
						system("clear");
						printf("En attente de la réponse du serveur ...\n");
					} else {
						system("clear");
						printf("Timeout");
					}
				} else
					printf("Interruption clavier\n", Buffer);
			} else if (desc == connDescPhys) { // Reception des données
				int donneesRecues = sizeof (REQUETE);
				timers = StopTimer(1, timers);
				
				if (Reception(conn, &requeteEnvoyee, &donneesRecues) == -1) {
					printf("Erreur lors de la reception des données");
					exit(1);
				}
				fct_reception(f, conn, requeteEnvoyee);
				nbreTransmissions = 0;
			}
		} else if (rc >= TIMEOUT) { // Timeout renvoi
			timers = StopTimer(1, timers);
			if (nbreTransmissions >= NBRE_RETRANSMISSIONS) {
				nbreTransmissions = 0;
				//transactionEnCours = -1;
				printf("Erreur lors de la transmission de la demande\n");
			} else { // Réessaye
				if (EnvoiClient(conn, &requeteEnvoyee, sizeof (REQUETE)) == -1) {
					printf("Erreur lors du renvoi des donnnées");
					exit(1);
				}
				timers = StartTimer(1, TIMOUT_RETRANSMISSIONS, timers);
				nbreTransmissions += 1;
				printf("Renvoi de la demande au serveur (%d) ...\n",
					nbreTransmissions
				);
			}
		} else if (rc == 0) { // TIMOUT attente événement
			printf("Time out\n", Buffer);
			break;
		} else if (rc == -1) { // Erreur
			printf("Erreur lors de l'attente de l'evenement\n");
			exit(1);
		}
	}
}