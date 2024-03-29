#include "Serveur.h"

void HandlerWait(int);

int main(int argc, char* argv[])
{
	struct Physique conn;
	// Descripteur physique associé à la connexion
	int connDescPhys;
	
	struct gEvenement even;
	
	// Ignore la fin des processus fils.
	// Evite les appels bloquants à wait().
	signal(SIGCHLD, SIG_IGN);
	
	FILE* f = OuvrirFichier(FICHIER_INFOS);
	CreerFichier(f); // Crée le fichier si non valide
	
	if ((connDescPhys = ConnecterServeur(argc, argv, &conn)) == -1) {
		printf("Impossible de démarrer une connexion serveur\n");
		exit(1);
	}
	
	if (CreerEvenement(connDescPhys, &even, 300) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	system("clear");
	printf("Serveur prêt\n");
	ListerFichier(f);
	
	for (;;) {
		char Buffer[100];
		int desc;
		
		switch (Attendre(&even, &desc)) {
		case 1:
			if (desc == 0) {
				fgets(Buffer, sizeof Buffer, stdin);
				system("clear");
				printf("Interruption clavier\n", Buffer);
				ListerFichierAsync(FICHIER_INFOS);
			} else
				GererClient(f, &conn);
			break;
		case 0: // Timeout
			break;
		case -1:
			printf("Erreur lors de l'attente de l'evenement\n");
			exit(1);
			break;
			
		};
	}
	
	fclose(f);
}

void GererClient(FILE* f, struct Physique* conn)
{
	REQUETE requete;
	INFOS entetes;
	int heure;
	int donneesRecues;
	
	donneesRecues = sizeof (REQUETE);
	if (Reception(conn, &requete, &donneesRecues) == -1) {
		printf("Erreur lors de la reception des données");
		exit(1);
	}
	system("clear");
	
	heure = requete.Heure;
	entetes = LireEntetes(f);
	
	if (entetes.PlacesLibres <= 0)
		requete.NumTicket = -1;
	else {
		requete.NumTicket = ReserverTicket(f, requete.Heure);
	}
	
	if (EnvoiServeur(conn, &requete, sizeof (REQUETE)) == -1) {
		printf("Erreur lors de l'envoi des données");
		exit(1);
	}
	ListerFichierAsync(FICHIER_INFOS);
}