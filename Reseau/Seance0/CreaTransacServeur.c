#include <stdio.h>

#include "CreaTransacServeur.h"
#define cls() printf("\033[H\033[2J");

int main(void)
{
	int choix;
	FILE* f = OuvrirFichier();
	
	do {
		cls();
		printf("[1] Creer le fichier transactions\n");
		printf("[2] Reserver un ticket\n");
		printf("[3] Payer le ticker\n");
		printf("[4] Sortir du parking\n");
		printf("[5] Lister le contenu du fichier\n");
		printf("[6] Quitter\n");
		
		printf("Votre choix: ");
		scanf("%d", &choix);
		
		switch (choix) {
		case 1:
			CreerFichier(f);
			break;
		
		case 2:
			ReserverTicket(f);
			break;
		
		case 3:
			PayerTicket(f);
			break;
		
		case 4:
			SortirParking(f);
			break;
		
		case 5:
			ListerFichier(f);
			break;
		}
		printf("Appuyez sur une touche pour continuer.\n");
		char c = getchar();
		while(getchar() != '\n');
	} while (choix != 6);
	
	return 0;
}

void CreerFichier(FILE* f)
{
	INFOS entetes = LireEntetes(f);
	if(entetes.Action == 0) printf("%d places libres\n", entetes.PlacesLibres);
	else printf("Fichier incorrect.\n");
}

void ReserverTicket(FILE* f)
{
	INFOS infos;
	
	// Met à jour les en-têtes
	infos = LireEntetes(f);
	infos.PlacesLibres -= 1;
	infos.NumTicket += 1;
	fseek(f, 0, SEEK_SET);
	EcrireInformations(f, infos);
	
	// Crée le nouvel enregistrement
	printf("Heure d'entrée : ");
	scanf("%d", &infos.Heure);
	infos.Action = RESERVATION;
	fseek(f, 0, SEEK_END);
	EcrireInformations(f, infos);
	printf("Votre ticket: %d\n", infos.NumTicket);
}

void PayerTicket(FILE* f)
{
	INFOS infos;
	
	int numTicket;
	printf("Numero de ticket : ");
	scanf("%d", &numTicket);
	
	// Lit le nombre de places libres
	infos = LireEntetes(f);
	int placesLibres = infos.PlacesLibres;
	
	// Recherche l'enregistrement du numero de ticket
	// par la fin
	fseek(f, -sizeof infos, SEEK_END);
	while (LireInformations(f, &infos)) {
		if (infos.Action == RESERVATION
		    && infos.NumTicket == numTicket) {
			// Enregistre l'heure de paiement
			printf("Heure de départ : ");
			scanf("%d", &infos.Heure);

			infos.PlacesLibres = placesLibres;
			infos.Action = PAYEMENT;
			
			fseek(f, 0, SEEK_END);
			EcrireInformations(f, infos);
			printf("Merci pour le payement, vous avez 15 minutes pour sortir.\n");
			return;
		} else if (infos.Action == PAYEMENT
		           && infos.NumTicket == numTicket) {
			printf("Ticket déjà payé\n");
		
			return;
		} else if (infos.Action == ENTETE) {
			printf("Pas d'enregistrement pour ce ticket.\n");
			
			return;
		}
		
		fseek(f, - (sizeof (INFOS)) * 2, SEEK_CUR);
	}
}

void SortirParking(FILE* f)
{
	INFOS infos, entetes;
	
	int numTicket;
	int temp = 0;
	printf("Numero de ticket : ");
	scanf("%d", &numTicket);
	
	// Lit le nombre de places libres
	entetes = LireEntetes(f);
	
	// Recherche l'enregistrement du paiement du ticket
	// par la fin
	fseek(f, -sizeof infos, SEEK_END);
	while (LireInformations(f, &infos)) {
		if (infos.Action == PAYEMENT
		    && infos.NumTicket == numTicket) {
			// Enregistre l'heure de sortie
			printf("Heure de sortie : ");
			scanf("%d", &temp);
			if(temp == infos.Heure)
			{
				infos.PlacesLibres = entetes.PlacesLibres;
				infos.Action = SORTIE;
				
				fseek(f, 0, SEEK_END);
				EcrireInformations(f, infos);
				
				entetes.PlacesLibres += 1;
				EcrireEntetes(f, entetes);
				printf("Bon retour !\n");
			}
			else
			{
				printf("Desole, votre aviez 15 minutes pour sortir..\n");
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
		
		fseek(f, - (sizeof(infos)) * 2, SEEK_CUR);
	}
}

void ListerFichier(FILE* f)
{
	INFOS infos;
	int i = 0;
	fseek(f, 0, SEEK_SET);
	while (LireInformations(f, &infos)) 
	{
		if(i == 1) printf("\n");
		AfficherInformations(infos);
		i++;
	}
	if(!i) printf("Fichier inexistant\n");
}