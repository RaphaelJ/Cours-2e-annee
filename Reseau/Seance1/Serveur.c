#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cls() printf("\033[H\033[2J");

#include "Serveur.h"

int main(int argc, char *argv[])
{
	struct Physique L; // la structure du message a envoyé
	INFOS infos;
	int rc, Rec;
	int Heure;
	FILE* f = OuvrirFichier();
	CreerFichier(f);
	
	if(Connect(argc, argv, &L))
	{
		Rec = sizeof(INFOS);
		cls();
		ListerFichier(f);
		printf("\n\n==== En attente de la reception d'une requete. === \n");
		while(1)
		{
			cls();
			if(!Receive(&L,&infos,&Rec)) return;
			else
			{
				Heure = infos.Heure;
				infos = LireEntetes(f);
				infos.Heure = Heure;
				if(infos.PlacesLibres <= 0) infos.NumTicket = -1;
				else ReserverTicket(f, &infos);
				if(!Send(&L, &infos, Rec)) return;
				ListerFichier(f);
				printf("\n\n==== En attente de la reception d'une requete. === \n");
			}
		}
	}
	
}

void CreerFichier(FILE* f)
{
	INFOS entetes = LireEntetes(f);
}

void ReserverTicket(FILE* f, INFOS *infos)
{
	int Heure = infos->Heure;
	// Met à jour les en-têtes
	*infos = LireEntetes(f);
	infos->PlacesLibres -= 1;
	infos->NumTicket += 1;
	fseek(f, 0, SEEK_SET);
	EcrireInformations(f, *infos);
	
	// Crée le nouvel enregistrement
	infos->Heure = Heure;
	infos->Action = RESERVATION;
	fseek(f, 0, SEEK_END);
	EcrireInformations(f, *infos);
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