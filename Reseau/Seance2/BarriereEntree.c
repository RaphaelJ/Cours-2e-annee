#include "BarriereEntree.h"

int main(int argc, char *argv[])
{
	struct Physique conn;
	
	struct gEvenement even;
	
	if (ConnecterClient(argc, argv, &conn) == -1) {
		printf("Impossible de se connecter au serveur\n");
		exit(1);
	}
	
	for (;;) {
		REQUETE requete;
		int donneesRecues = sizeof (REQUETE);
		
		printf("\nHeure du ticket: ");
		scanf("%d", &requete.Heure);
		
		if (EnvoiClient(&conn, &requete, sizeof (REQUETE)) == -1) {
			printf("Erreur lors de l'envoi des donnnées");
			exit(1);
		}
	
		if (Reception(&conn, &requete, &donneesRecues) == -1) {
			printf("Erreur lors de la reception des données");
			exit(1);
		}
		
		if (requete.NumTicket == -1) {
			printf("Nombre de places disponibles insuffisant.\n");
		} else {
			printf("Numéro ticket recu : %d\n", requete.NumTicket);
		}
	}
}