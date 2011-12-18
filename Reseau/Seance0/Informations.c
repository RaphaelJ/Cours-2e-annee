#include <stdio.h>

#include "Informations.h"

const INFOS infosDefaut = { 0, 0, 0, 0, 99, 0, ENTETE };

FILE* OuvrirFichier()
{
	if(!fopen(FICHIER_INFOS, "r+"))
	{
		fopen(FICHIER_INFOS, "w+");
	}
}

void EcrireInformations(FILE* f, INFOS infos)
{
	fwrite(&infos, sizeof(INFOS), 1, f);
}

bool LireInformations(FILE* f, INFOS* infos)
{
	return(fread(infos, sizeof(INFOS), 1, f));
}

INFOS LireEntetes(FILE* f)
{
	INFOS infos;
	fseek(f, 0, SEEK_SET);
	if (!LireInformations(f, &infos)) {
		printf("Creation du fichier\n");
		// Fichier vide, écrit les valeurs par
		// défaut
		infos = infosDefaut;
		EcrireEntetes(f, infos);
	}
	return infos;
}

void EcrireEntetes(FILE* f, INFOS entetes)
{
	fseek(f, 0, SEEK_SET);
	EcrireInformations(f, entetes);
}

void AfficherInformations(INFOS infos)
{
	char* actionName;
	switch (infos.Action) {
	case ENTETE:
		actionName = "ENTETE";
		break;
	case RESERVATION:
		actionName = "RESERVATION";
		break;
	case PAYEMENT:
		actionName = "PAYEMENT";
		break;
	case SORTIE:
		actionName = "SORTIE";
		break;
	default:
		actionName = "INCONNU";
	}
	
	printf("IP: %d\tPort: %d\tNum Transac: %d\tHeure: %d\t"
	       "Places: %d\tNum Ticket: %d\tAction: %s\n",
		infos.IP, infos.Port, infos.NumTransac, infos.Heure,
		infos.PlacesLibres, infos.NumTicket, actionName
	);
}