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
	
	printf("Heure: %d\t"
	       "Places: %d\tNum Ticket: %d\tAction: %s\n",
		infos.Heure,
		infos.PlacesLibres, infos.NumTicket, actionName
	);
}

bool Connect(int argc, char* argv[], Physique *s)
{
	int rc;
	bzero(s,sizeof(struct Physique));
	if (argc!=5)
	{
		printf("cli client portc serveur ports\n") ;
		return false;
	}
	
	rc = CreerConnexion(s,argv[1],atoi(argv[2]),argv[3],atoi(argv[4]));
	if (rc == -1) return false;
	else return true;
}

bool Send(Physique *s, INFOS *infos, int Taille)
{
	int rc = VersCouchePhysique(s,infos,Taille);
	if (rc == -1) return false;
	else return true;
}

bool Receive(Physique *s, INFOS *infos, int *Taille)
{
	int rc = OrigineCouchePhysique(s, infos,Taille);
	if (rc == -1) return false;
	else return true;
}