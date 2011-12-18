#include <stdio.h>

#include "CreaTransacServeur.h"

int main(void)
{
	int choix;
	FILE* f = OuvrirFichier(FICHIER_INFOS);
	
	int heureEntree, numTicket, heureDepart;
	
	do {
		printf("[1] Creer le fichier transactions\n");
		printf("[2] Reserver un ticket\n");
		printf("[3] Payer le ticker\n");
		printf("[4] Sortir du parking\n");
		printf("[5] Lister le contenu du fichier\n");
		printf("[6] Quitter\n");
		
		printf("Votre choix: ");
		scanf("%d", &choix);
		printf("\n");
		
		switch (choix) {
		case 1:
			CreerFichier(f);
			break;
		
		case 2:
			printf("Heure d'entrée : ");
			scanf("%d", &heureEntree);
			ReserverTicket(f, heureEntree, 0, 0, 0);
			break;
		
		case 3:
			printf("Numero de ticket : ");
			scanf("%d", &numTicket);
			printf("Heure de départ : ");
			scanf("%d", &heureDepart);
			PayerTicket(f, numTicket, heureDepart);
			break;
		
		case 4:
			printf("Numero de ticket : ");
			scanf("%d", &numTicket);
			printf("Heure de départ : ");
			scanf("%d", &heureDepart);
			SortirParking(f, numTicket, heureDepart);
			break;
		
		case 5:
			ListerFichier(f);
			break;
		}
	} while (choix != 6);
	
	return 0;
}