#include "Informations.h"

const INFOS infosDefaut = { 0, 0, 0, 0, 99, 0, ENTETE };

void EcrireInformations(FILE* f, INFOS infos)
{
	fwrite(&infos, sizeof (INFOS), 1, f);
	fflush(f);
}

bool LireInformations(FILE* f, INFOS* infos)
{
	return fread(infos, sizeof (INFOS), 1, f);
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
	char* actionTexte;
	switch (infos.Action) {
	case ENTETE:
		actionTexte = "ENTETE";
		break;
	case RESERVATION:
		actionTexte = "RESERVATION";
		break;
	case PAYEMENT:
		actionTexte = "PAYEMENT";
		break;
	case SORTIE:
		actionTexte = "SORTIE";
		break;
	default:
		actionTexte = "INCONNU";
	}
	
	printf("Transaction: %d\tHeure: %d\tPlaces: %d\t"
		"Num Ticket: %d\tAction: %s\n",
		/*infos.IP, infos.Port,*/ infos.NumTransac, infos.Heure, infos.PlacesLibres,
		infos.NumTicket, actionTexte
	);
}