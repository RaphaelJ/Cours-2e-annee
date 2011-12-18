#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cls() printf("\033[H\033[2J");

#include "Client.h"

int main(int argc, char *argv[])
{
	FILE* f = OuvrirFichier();
	int rc, Heure;
	struct Physique L; // la structure du message a envoyé
	INFOS infos;
	int Rec;
	
	if(Connect(argc, argv, &L))
	{
		while(1)
		{
			printf("\nHeure du ticket: ");
			scanf("%d", &infos.Heure);
			Rec = sizeof(INFOS);
			if(!Send(&L, &infos, Rec)) return;
			if(!Receive(&L,&infos,&Rec)) return;
			else
			{
				if(infos.NumTicket == -1)
				{
					printf("Nombre de places disponible insuffisant.\n");
				}else printf("Numéro ticket recu : %d\n", infos.NumTicket);
			}
		}
	}
}
