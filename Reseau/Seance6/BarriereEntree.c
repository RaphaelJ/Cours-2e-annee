#include "BarriereEntree.h"

//int transactionEnCours = -1;

int main(int argc, char *argv[])
{
	struct Physique conn;
	// Descripteur physique associé à la connexion
	int connDescPhys;
	
	// Ouvre un fichier avec le # de port
	FILE* f = OuvrirFichier(argv[2]);
	CreerFichier(f); // Crée le fichier si non valide
	
	if ((connDescPhys = ConnecterClient(argc, argv, &conn)) == -1) {
		printf("Impossible de se connecter au serveur\n");
		exit(1);
	}
	
	Transmettre(
		&conn, connDescPhys, f, "Nouveau ticket", true, false,
		EnvoyerDemandeTicket, ReceptionTicket
	);
	
	fclose(f);
}

// Retourne true si envoyée.
// false si timeout
bool EnvoyerDemandeTicket(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requete)
{	
	requete->Code = RESERVATION;
	requete->NumTransac = NouvelleTransaction(f);
	
	printf("\nHeure du ticket: ");
	return EntreeTimeOut(&(requete->Heure));
}

void ReceptionTicket(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete)
{
	INFOS infos;
	
	/*if (transactionEnCours != requete.NumTransac) { 
		// Reception d'une transaction annulee
		printf("Transaction recue inattendue : %d.\n", requete.NumTransac);
	} else */if (requete.NumTicket == -1) {
		printf("Nombre de places disponibles insuffisant.\n");
	} else {
		fseek(f, -sizeof infos, SEEK_END);
		LireInformations(f, &infos);
		if (infos.NumTicket == requete.NumTicket) {
			printf("Ticket recu en doublon\n", requete.NumTicket);
		} else {
			printf("Numero ticket recu : %d\n", requete.NumTicket);
			
			infos.Action = RESERVATION;
			infos.Heure = requete.Heure;
			infos.NumTicket = requete.NumTicket;
			infos.PlacesLibres = 0;
			infos.NumTransac = requete.NumTransac;
			
			//transactionEnCours = -1;
			
			fseek(f, 0, SEEK_END);
			EcrireInformations(f, infos);
		}
	}
}