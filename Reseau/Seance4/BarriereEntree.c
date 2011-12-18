#include "BarriereEntree.h"

int main(int argc, char *argv[])
{
	struct Physique conn;
	// Descripteur physique associé à la connexion
	int connDescPhys;
	
	struct gEvenement even;
	struct ListeTimer* plt = NULL;
	
	// Ouvre un fichier avec le # de port
	FILE* f = OuvrirFichier(argv[2]);
	CreerFichier(f); // Crée le fichier si non valide
	
	if ((connDescPhys = ConnecterClient(argc, argv, &conn)) == -1) {
		printf("Impossible de se connecter au serveur\n");
		exit(1);
	}
	
	if (CreerEvenementMilisecs(connDescPhys, &even, 0, 200000) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	int nbreTransmissions = 0;
	REQUETE requeteEnvoyee;
	
	system("clear");
	printf("Appuyez sur n+<Enter> pour un nouveau ticket\n");
	for (;;) {
		char Buffer[100];
		int desc;
		
		ListerFichier(f);
		
		printf("\nListe des timers: ");
		AfficheTimer(plt);
		
		int rc = AttendreTimer(&even, &desc, &plt);
		system("clear");
		if (rc == 1) { // OK
			if (desc == 0) { // Interrupt clavier
				fgets(Buffer, sizeof Buffer, stdin);
				if (nbreTransmissions > 0) {
					printf("Transaction précédente non validée\n");
				} else if (strcmp(Buffer, "n\n") == 0) {
					if (EnvoyerDemandeTicket(&conn, &requeteEnvoyee)) {
						// Si pas de timeout sur l'entrée
						plt = StopTimer(1, plt);
						plt = StartTimer(1, 4000, plt);
						nbreTransmissions = 1;
					}
				} else
					printf("Interruption clavier\n", Buffer);
			} else if (desc == connDescPhys) {
				plt = StopTimer(1, plt);
				ReceptionTicket(f, &conn);
				nbreTransmissions = 0;
			}
		} else if (rc >= TIMEOUT) { // Timeout envoi
			plt = StopTimer(1, plt);
			if (nbreTransmissions >= NBRE_RETRANSMISSIONS) {
				nbreTransmissions = 0;
				printf("Erreur lors de la réservation du ticket\n");
			} else { // Réessaye
				RenvoyerDemandeTicket(&conn, requeteEnvoyee);
				plt = StartTimer(1, TIMOUT_RETRANSMISSIONS, plt);
				nbreTransmissions += 1;
				printf("Renvoi de la demande au serveur (%d) ...\n",
					nbreTransmissions
				);
			}
		} else if (rc == 0) { // TIMOUT événement
			printf("Time out\n", Buffer);
			break;
		} else if (rc == -1) { // Erreur
			printf("Erreur lors de l'attente de l'evenement\n");
			exit(1);
		}
	}
	
	fclose(f);
}

// Retourne true si envoyée.
// false si timeout
bool EnvoyerDemandeTicket(struct Physique* conn, REQUETE* requete)
{
	int descClavier = 0;
	struct gEvenement evenClavier;
	
	// Crée un événement pour ne pas attendre plus de 60 secs
	if (CreerEvenement(descClavier, &evenClavier, 15) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	printf("\nHeure du ticket: ");
	fflush(stdout);
	switch (Attendre(&evenClavier, &descClavier)) {
	case 1:
		scanf("%d", &(requete->Heure));
		if (EnvoiClient(conn, requete, sizeof (REQUETE)) == -1) {
			printf("Erreur lors de l'envoi des donnnées");
			exit(1);
		}
	
		system("clear");
		printf("En attente de la réponse du serveur ...\n");
		
		return true;
	case 0: // Timeout -> retour au menu
		system("clear");
		printf("Time out\n");
		
		return false;
	case -1:
		printf("Erreur lors de l'attente de l'evenement\n");
		exit(1);
	};
}

void RenvoyerDemandeTicket(struct Physique* conn, REQUETE requete)
{
	if (EnvoiClient(conn, &requete, sizeof (REQUETE)) == -1) {
		printf("Erreur lors de l'envoi des donnnées");
		exit(1);
	}
}

void ReceptionTicket(FILE* f, struct Physique* conn)
{
	REQUETE requete;
	INFOS infos;
	int donneesRecues = sizeof (REQUETE);
	
	if (Reception(conn, &requete, &donneesRecues) == -1) {
		printf("Erreur lors de la reception des données");
		exit(1);
	}
	
	if (requete.NumTicket == -1) {
		printf("Nombre de places disponibles insuffisant.\n");
	} else {
		printf("Numero ticket recu : %d\n", requete.NumTicket);
	}
	
	infos.Action = RESERVATION;
	infos.Heure = requete.Heure;
	infos.NumTicket = requete.NumTicket;
	infos.PlacesLibres = 0;
	infos.NumTransac = 0;
	
	fseek(f, 0, SEEK_END);
	EcrireInformations(f, infos);
}