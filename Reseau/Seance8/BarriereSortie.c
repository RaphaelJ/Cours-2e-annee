#include "BarriereSortie.h"

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
		&conn, connDescPhys, f, "Sortie", true, false,
		EnvoyerDemandeSortie, ReceptionValidationSortie
	);
	
	fclose(f);
}

// Retourne true si envoyée.
// false si timeout
bool EnvoyerDemandeSortie(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requete)
{	
	requete->Code = SORTIE;
	requete->NumTransac = NouvelleTransaction(f);
	
	printf("\nHeure de sortie: ");
	if (EntreeTimeOut(&(requete->Heure))) {
		printf("\nNumero de ticket: ");
		return EntreeTimeOut(&(requete->NumTicket));
	} else { // Timeout -> retour au menu
		return false;
	}
}

void ReceptionValidationSortie(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete)
{
	INFOS infos;
	
	/*if (transactionEnCours != requete.NumTransac) { 
		// Reception d'une transaction annulee
		printf("Transaction recue inattendue : %d.\n", requete.NumTransac);
	} else */
	if (requete.NumTicket == -4) {
		printf("Vous devez sortir dans l'heure.\n");
	} else if (requete.NumTicket == -3) {
		printf("Le ticket n'a pas encore été payé.\n");
	} else if (requete.NumTicket == -2) {
		printf("Le ticket a déjà été utilisé pour une sortie.\n");
	} else if (requete.NumTicket == -1) {
		printf("Le ticket n'existe pas.\n");
	} else {
		fseek(f, -sizeof infos, SEEK_END);
		LireInformations(f, &infos);
		if (infos.NumTransac == requete.NumTransac) {
			printf("Ticket recu en doublon\n", requete.NumTicket);
		} else {
			printf("Ticket de sortie rentré : %d\n", requete.NumTicket);
			
			infos.Action = SORTIE;
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