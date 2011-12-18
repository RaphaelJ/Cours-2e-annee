#include "BarriereEntree.h"

int main(int argc, char *argv[])
{
	struct Physique conn;
	// Descripteur physique associé à la connexion
	int connDescPhys;
	
	struct gEvenement even;
	
	// Ouvre un fichier avec le # de port
	FILE* f = OuvrirFichier(argv[2]);
	CreerFichier(f); // Crée le fichier si non valide
	
	if ((connDescPhys = ConnecterClient(argc, argv, &conn)) == -1) {
		printf("Impossible de se connecter au serveur\n");
		exit(1);
	}
	
	if (CreerEvenement(connDescPhys, &even, 300) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	system("clear");
	printf("Appuyez sur n+<Enter> pour un nouveau ticket\n");
	for (;;) {
		char Buffer[100];
		int desc;
		
		ListerFichier(f);
		
		switch (Attendre(&even, &desc)) {
		case 1:
			system("clear");
			if (desc == 0) {
				fgets(Buffer, sizeof Buffer, stdin);
				if (strcmp(Buffer, "n\n") == 0)
					EnvoyerDemandeTicket(&conn);
				else
					printf("Interruption clavier\n", Buffer);
			} else
				ReceptionTicket(f, &conn);
			break;
		case 0: // Timeout
			system("clear");
			printf("Time out\n", Buffer);
			break;
		case -1:
			printf("Erreur lors de l'attente de l'evenement\n");
			exit(1);
			break;
		};
		
	}
	
	fclose(f);
}

void EnvoyerDemandeTicket(struct Physique* conn)
{
	REQUETE requete;
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
		scanf("%d", &requete.Heure);
		
		if (EnvoiClient(conn, &requete, sizeof (REQUETE)) == -1) {
			printf("Erreur lors de l'envoi des donnnées");
			exit(1);
		}
	
		system("clear");
		printf("En attente de la réponse du serveur ...\n");
		break;
	case 0: // Timeout
		system("clear");
		printf("Time out\n");
		break;
	case -1:
		printf("Erreur lors de l'attente de l'evenement\n");
		exit(1);
		break;
	};
	
	fclose(f);
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
		printf("Numéro ticket recu : %d\n", requete.NumTicket);
	}
	
	infos.Action = RESERVATION;
	infos.Heure = requete.Heure;
	infos.NumTicket = requete.NumTicket;
	infos.PlacesLibres = 0;
	infos.NumTransac = 0;
	
	fseek(f, 0, SEEK_END);
	EcrireInformations(f, infos);
}