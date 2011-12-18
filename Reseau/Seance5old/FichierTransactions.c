#include "FichierTransactions.h"

FILE* OuvrirFichier(const char* nomFichier)
{
	FILE* f = fopen(nomFichier, "r+");
	if (f == NULL)
		f = fopen(nomFichier, "w+");
	
	return f;
}

// Crée le fichier si ce n'est déjà fait
void CreerFichier(FILE* f)
{
	INFOS entetes = LireEntetes(f);
	
	if (entetes.Action == ENTETE)
		printf("%d places libres\n", entetes.PlacesLibres);
	else {
		printf("Fichier incorrect.\n");
		exit(1);
	}
}

// Réserve un ticket
// Retourne le numero de ticket
// -1 si plus de places
int ReserverTicket(FILE* f, int heureEntree, int ip, int port, int numTransac)
{
	INFOS infos;
	
	// Met à jour les en-têtes
	infos = LireEntetes(f);
	if (infos.PlacesLibres <= 0)
		return -1;
	else {
		infos.PlacesLibres -= 1;
		infos.NumTicket += 1;
		infos.NumTransac += 1;
		EcrireEntetes(f, infos);
	
		// Crée le nouvel enregistrement
		//printf("Heure d'entrée : ");
		//scanf("%d", &infos.Heure);
		infos.NumTransac = numTransac;
		infos.IP = ip;
		infos.Port = port;
		infos.Heure = heureEntree;
		infos.Action = RESERVATION;
		fseek(f, 0, SEEK_END);
		EcrireInformations(f, infos);
		printf("Reservation ticket n°%d\n", infos.NumTicket);
		
		return infos.NumTicket;
	}
}

// Retourne true si le ticket est payable
// false si ticket déjà payé ou innexistant
int TicketPayable(FILE* f, int numTicket, int heureDepart,
                 int ip, int port, int numTransac)
{
	INFOS infos, entetes;
	
	// Lit le nombre de places libres
	entetes = LireEntetes(f);
	// Recherche l'enregistrement du numero de ticket
	// par la fin
	fseek(f, -sizeof infos, SEEK_END);
	while (LireInformations(f, &infos)) {
		if (infos.Action == RESERVATION
		    && infos.NumTicket == numTicket) {
			printf("Ticket payable.\n");
			return true;
		} else if (infos.Action == PAYEMENT
		           && infos.NumTicket == numTicket) {
			printf("Ticket déjà payé\n");
		
			return false;
		} else if (infos.Action == ENTETE) {
			printf("Pas d'enregistrement pour ce ticket.\n");
			
			return false;
		}
		
		fseek(f, -sizeof (INFOS) * 2, SEEK_CUR);
	}
}

// Retourne true en cas de réussite
// false si ticket déjà payé ou innexistant
int PayerTicket(FILE* f, int numTicket, int heureDepart,
                 int ip, int port, int numTransac)
{
	INFOS infos, entetes;
	
	//int numTicket;
	//printf("Numero de ticket : ");
	//scanf("%d", &numTicket);
	
	// Lit le nombre de places libres
	entetes = LireEntetes(f);
	//int placesLibres = infos.PlacesLibres;
	
	// Recherche l'enregistrement du numero de ticket
	// par la fin
	fseek(f, -sizeof infos, SEEK_END);
	while (LireInformations(f, &infos)) {
		if (infos.Action == RESERVATION
		    && infos.NumTicket == numTicket) {
			// Enregistre l'heure de paiement
			//printf("Heure de départ : ");
			//scanf("%d", &infos.Heure);
			
			entetes.NumTransac += 1;
			EcrireEntetes(f, entetes);

			infos.Heure = heureDepart;
			infos.PlacesLibres = entetes.PlacesLibres;
			infos.NumTransac = numTransac;
			infos.Action = PAYEMENT;
			
			fseek(f, 0, SEEK_END);
			EcrireInformations(f, infos);
			
			printf("Veuillez sortir dans l'heure.\n");
			return true;
		} else if (infos.Action == PAYEMENT
		           && infos.NumTicket == numTicket) {
			printf("Ticket déjà payé\n");
		
			return false;
		} else if (infos.Action == ENTETE) {
			printf("Pas d'enregistrement pour ce ticket.\n");
			
			return false;
		}
		
		fseek(f, -sizeof (INFOS) * 2, SEEK_CUR);
	}
}

void SortirParking(FILE* f, int numTicket, int heureDepart)
{
	INFOS infos, entetes;
	
// 	int numTicket;
// 	printf("Numero de ticket : ");
// 	scanf("%d", &numTicket);
	
	// Lit le nombre de places libres
	entetes = LireEntetes(f);
	
	// Recherche l'enregistrement du paiement du ticket
	// par la fin
	fseek(f, -sizeof infos, SEEK_END);
	while (LireInformations(f, &infos)) {
		if (infos.Action == PAYEMENT
		    && infos.NumTicket == numTicket) {
			// Enregistre l'heure de sortie
// 			int heureDepart;
// 			printf("Heure de sortie : ");
// 			scanf("%d", &heureDepart);
			if (heureDepart == infos.Heure) {
				entetes.NumTransac += 1;
				infos.NumTransac = entetes.NumTransac;
				infos.PlacesLibres = entetes.PlacesLibres;
				infos.Action = SORTIE;
				
				fseek(f, 0, SEEK_END);
				EcrireInformations(f, infos);
				
				entetes.PlacesLibres += 1;
				EcrireEntetes(f, entetes);
			} else {
				printf("Vous devez sortir dans l'heure\n");
			}
			return;
		} else if (infos.Action == SORTIE
		           && infos.NumTicket == numTicket) {
			printf("Sortie déjà effectuée\n");
		
			return;
		} else if (infos.Action == ENTETE) {
			printf("Pas d'enregistrement pour ce ticket.\n");
			
			return;
		}
		
		fseek(f, -sizeof(infos) * 2, SEEK_CUR); // Retour vers le passé
	}
}

void ListerFichier(FILE* f)
{
	INFOS infos;
	
	// Affiche les entetes
	infos = LireEntetes(f);
	AfficherInformations(infos);
	printf("\n");
	
	// Affiche les 20 derniers
	int i = 0;
	fseek(f, -sizeof infos, SEEK_END);
	while (LireInformations(f, &infos)
	       && infos.Action != ENTETE
	       && i < 20) {
		AfficherInformations(infos);
		
		i++;
		fseek(f, -sizeof(infos) * 2, SEEK_CUR); // Retour vers le passé
	}
	
	if (i < 1)
		printf("Fichier vide ou innexistant\n");
}

// Liste le contenu du fichier en rendant immédiatement
// la main à la fonction appelante (fork)
void ListerFichierAsync(const char* nomFichier)
{
	if (fork() == 0) { // Fils
		// Le FILE* doit être différent sinon
		// il est fermé par le fils
		FILE* f = OuvrirFichier(nomFichier);
		ListerFichier(f);
		fclose(f);
		exit(0);
	}
}

// Retourne un nouveau numero de transaction
int NouvelleTransaction(FILE* f)
{
	INFOS infos;
	
	fseek(f, -sizeof infos, SEEK_END);
	LireInformations(f, &infos);
	
	printf("NumTrasac: %d\n", infos.NumTransac + 1);
	return infos.NumTransac + 1;
}

// Retourner le numero de ticket si la transaction a déjà été enregistrée
// 0 sinon.
int Doublon(FILE* f, int ip, int port, int numTransac)
{
	INFOS infos;
	
	fseek(f, -sizeof infos, SEEK_END);
	while (LireInformations(f, &infos)
	       && infos.Action != ENTETE) {
		
		if (infos.Action == RESERVATION && infos.IP == ip
		    && infos.Port == port && infos.NumTransac == numTransac)
		    return infos.NumTicket;
		
		fseek(f, -sizeof(infos) * 2, SEEK_CUR); // Retour vers le passé
	}
	
	return 0;
}