#include "BornePaiement.h"

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
		&conn, connDescPhys, f, "Payer un ticket", true, false,
		EnvoyerDemandePaiement, ReceptionDemandeConfirmation
	);
	
	fclose(f);
}

// Demande à l'utilisateur une heure et un numero de ticket.
// Envoie la demande au serveur
// false si timeout
bool EnvoyerDemandePaiement(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requete)
{	
	requete->Code = DEMANDEPAYEMENT;
	requete->NumTransac = NouvelleTransaction(f);
	
	printf("\nHeure de sortie: ");
	if (EntreeTimeOut(&(requete->Heure))) {
		printf("\nNumero de ticket: ");
		if (EntreeTimeOut(&(requete->NumTicket))) {
			return true;
		} else { // Timeout -> retour au menu
			return false;
		}
	} else { // Timeout -> retour au menu
		return false;
	}
}

// Recoit le message affirmant l'existance du ticket
void ReceptionDemandeConfirmation(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete)
{
	INFOS infos;
	
	/*if (transactionEnCours != requete.NumTransac) { 
		// Reception d'une transaction annulee
		printf("Transaction recue inattendue : %d.\n", requete.NumTransac);
	} else */
	if (requete.NumTicket == -1) {
		printf("Le numéro de ticket n'est pas valide ou a déjà été payé.\n");
	} else {
		fseek(f, -sizeof infos, SEEK_END);
		LireInformations(f, &infos);
		if (infos.NumTransac == requete.NumTransac) {
			printf("Demande de confirmation recue en doublon\n");
		} else {
			printf("Demande de confirmation recue\n");
			
			infos.Action = DEMANDEPAYEMENT;
			infos.Heure = requete.Heure;
			infos.NumTicket = requete.NumTicket;
			infos.PlacesLibres = 0;
			infos.NumTransac = requete.NumTransac;
			
			//transactionEnCours = -1;
			
			fseek(f, 0, SEEK_END);
			EcrireInformations(f, infos);
			
			Transmettre(
				conn, connDescPhys, f, "Confirmer le paiement", false, true,
				EnvoyerConfirmationPaiement, ReceptionValidationPaiement
			);
		}
	}
}

// Envoie la confirmation du paiement
bool EnvoyerConfirmationPaiement(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requete)
{	
	INFOS infos;
	
	// Récupère le numéro du ticket et l'heure
	fseek(f, -sizeof infos, SEEK_END);
	LireInformations(f, &infos);
	requete->NumTicket = infos.NumTicket;
	requete->Heure = infos.Heure;
	
	requete->Code = VALIDERPAYEMENT;
	requete->NumTransac = NouvelleTransaction(f);
	
	return true;
}

// Recoit le message validant le paiement
void ReceptionValidationPaiement(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete)
{
	INFOS infos;
	
	/*if (transactionEnCours != requete.NumTransac) { 
		// Reception d'une transaction annulee
		printf("Transaction recue inattendue : %d.\n", requete.NumTransac);
	} else */
	if (requete.NumTicket == -1) {
		printf("Le numéro de ticket n'est pas valide ou a déjà été payé.\n");
	} else {
		fseek(f, -sizeof infos, SEEK_END);
		LireInformations(f, &infos);
		if (infos.NumTransac == requete.NumTransac) {
			printf("Validation du paiement recue en doublon\n");
		} else {
			printf("Validation du paiement recue\n");
			
			infos.Action = VALIDERPAYEMENT;
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


