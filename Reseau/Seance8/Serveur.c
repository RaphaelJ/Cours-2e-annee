#include "Serveur.h"

int main(int argc, char* argv[])
{
	struct Physique conn;
	struct Physique conn2;
	struct Physique conn3;
	
	// Descripteur physique associé à la connexion
	int connDescPhys;
	int connDescPhys2;
	int connDescPhys3;
	
	struct gEvenement even;
	
	// Ignore la fin des processus fils.
	// Evite les appels bloquants à wait().
	signal(SIGCHLD, SIG_IGN);
	
	FILE* f = OuvrirFichier(FICHIER_INFOS);
	CreerFichier(f); // Crée le fichier si non valide
	
	if ((connDescPhys = ConnecterServeurE(argc, argv, &conn)) == -1) {
		printf("Impossible de démarrer une connexion serveur\n");
		exit(1);
	}
	if ((connDescPhys2 = ConnecterServeurP(argc, argv, &conn2)) == -1) {
		printf("Impossible de démarrer une connexion serveur\n");
		exit(1);
	}
	if ((connDescPhys3 = ConnecterServeurS(argc, argv, &conn3)) == -1) {
		printf("Impossible de démarrer une connexion serveur\n");
		exit(1);
	}
	
	if (CreerEvenementMulti(connDescPhys,connDescPhys2,connDescPhys3, &even, 300) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	system("clear");
	printf("Serveur prêt. s+<enter> pour patienter.\n");
	ListerFichier(f);
	
	REQUETE requete;
	int donneesRecues;
	
	for (;;) {
		char Buffer[100];
		int desc;
		
		switch (Attendre(&even, &desc)) {
		case 1:
			if (desc == 0) {
				fgets(Buffer, sizeof Buffer, stdin);
				if (strcmp(Buffer, "s\n") == 0) {
					Patienter();
					system("clear");
					printf("Délai écoulé\n");
					ListerFichierAsync(FICHIER_INFOS);
				} else {
					system("clear");
					printf("Interruption clavier\n", Buffer);
					ListerFichierAsync(FICHIER_INFOS);
				}
			} else
				//GererClient(f, &conn, &desc);
				donneesRecues = sizeof (REQUETE);
			system("clear");
			if (desc == connDescPhys) {
				int ret;
				if ((ret = Reception(&conn, &requete)) == -1) {
					printf("Erreur lors de la reception des données");
					exit(1);
				} else if (ret >= 0) {
					if (Doublon(f, IPDistante(&conn), PortDistant(&conn), requete.NumTransac)) {
						printf("Reception d'un doublon pour %d\n", requete.NumTransac);
					}
					else
						GererReservationClient(f, &conn, requete);
				}
			}
			else if (desc == connDescPhys2){
				int ret;
				if ((ret = Reception(&conn2, &requete)) == -1) {
					printf("Erreur lors de la reception des données");
					exit(1);
				} else if (ret >= 0) {
					if (Doublon(f, IPDistante(&conn2), PortDistant(&conn2), requete.NumTransac)) {
						printf("Reception d'un doublon pour %d\n", requete.NumTransac);
					} else {
						switch (requete.Code)
						{
							case DEMANDEPAYEMENT:
								GererDemandePaiementClient(f, &conn2, requete);
							break;
							case VALIDERPAYEMENT:
								GererConfirmationPaiementClient(f, &conn2, requete);
							break;
						}
						
					}
				}
			}
			else if (desc == connDescPhys3){
				int ret;
				if ((ret = Reception(&conn3, &requete)) == -1) {
					printf("Erreur lors de la reception des données");
					exit(1);
				} else if (ret >= 0) {
					if (Doublon(f, IPDistante(&conn3), PortDistant(&conn3), requete.NumTransac)) {
					printf("Reception d'un doublon pour %d\n", requete.NumTransac);
					}
					else
					GererSortieClient(f, &conn3, requete);
				}
			}else{
				printf("Réception d'une reqûete inconnue");
			}
			ListerFichierAsync(FICHIER_INFOS);
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

// void GererClient(FILE* f,struct Physique* conn, int desc)
// {
// 	REQUETE requete;
// 	int donneesRecues;
// 	
// 	donneesRecues = sizeof (REQUETE);
// 	if (Reception(conn, &requete) == -1) {
// 		printf("Erreur lors de la reception des données");
// 		exit(1);
// 	}
// 	
// 	system("clear");
// 	
// 	if (Doublon(f, IPDistante(conn), PortDistant(conn), requete.NumTransac)) {
// 		printf("Reception d'un doublon pour %d\n", requete.NumTransac);
// 	} else {/*
// 		switch (requete.Code) {
// 		case RESERVATION:
// 			GererReservationClient(f, conn, requete);
// 			break;
// 		case DEMANDEPAYEMENT:
// 			GererDemandePaiementClient(f, conn, requete);
// 			break;
// 		case VALIDERPAYEMENT:
// 			GererConfirmationPaiementClient(f, conn, requete);
// 			break;
// 		case SORTIE:
// 			GererSortieClient(f, conn, requete);
// 			break;
// 		default:
// 			printf("Réception d'une reqûete inconnue");
// 		};*/
// 		switch(desc)
// 		{
// 			
// 		}
// 	}
// 	
// 	ListerFichierAsync(FICHIER_INFOS);
// }

void GererReservationClient(FILE* f, struct Physique* conn, REQUETE requete)
{
	INFOS entetes;
	
	entetes = LireEntetes(f);
	
	if (entetes.PlacesLibres <= 0) {
		requete.NumTicket = -1;
	} else {
		requete.NumTicket = ReserverTicket(
			f, requete.Heure, IPDistante(conn),
			PortDistant(conn), requete.NumTransac
		);
	}
	
	if (EnvoiServeur(conn, &requete) == -1) {
		printf("Erreur lors de l'envoi des données");
		exit(1);
	}
}

void GererDemandePaiementClient(FILE* f, struct Physique* conn, REQUETE requete)
{
	if (!TicketPayable(f, requete.NumTicket, requete.Heure,
	                   IPDistante(conn), PortDistant(conn),
	                   requete.NumTransac)) {
		requete.NumTicket = -1;
	}
	
	// Envoi -1 comme numero de ticket si le ticket n'existe pas
	if (EnvoiServeur(conn, &requete) == -1) {
		printf("Erreur lors de l'envoi des données");
		exit(1);
	}
}

void GererConfirmationPaiementClient(FILE* f, struct Physique* conn, REQUETE requete)
{
	if (!PayerTicket(f, requete.NumTicket, requete.Heure,
	                 IPDistante(conn), PortDistant(conn),
	                 requete.NumTransac)) {
		requete.NumTicket = -1;
	}
	
	// Envoi -1 comme numero de ticket si le ticket n'existe pas
	if (EnvoiServeur(conn, &requete) == -1) {
		printf("Erreur lors de l'envoi des données");
		exit(1);
	}
}

void GererSortieClient(FILE* f, struct Physique* conn, REQUETE requete)
{
	requete.NumTicket = SortirParking(
		f, requete.NumTicket, requete.Heure,
		IPDistante(conn), PortDistant(conn),
		requete.NumTransac
	);
	
	if (EnvoiServeur(conn, &requete) == -1) {
		printf("Erreur lors de l'envoi des données");
		exit(1);
	}
}

void Patienter()
{
	int secondes;
	char Buffer[10];
	
	printf("Nombre de secondes (-1 si attente clavier) : ");
	fgets(Buffer, sizeof Buffer, stdin);
	secondes = atoi(Buffer);
	
	if (secondes == -1) {
		printf("Enter pour continuer");
		fgets(Buffer, sizeof Buffer, stdin);
	} else {
		while (secondes > 0) {
			fprintf(stderr, "%d ... ", secondes);
			sleep(1);
			secondes -= 1;
		}
	}
}