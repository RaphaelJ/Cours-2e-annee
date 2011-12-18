/******************************************
  Herman Vanstapel
  2007
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

void DelNewLine(char *Chaine)
{
    Chaine[strlen(Chaine) - 1] = '\0';
}

char ReadChar()
{
    char Tampon[80];
    fgets(Tampon, sizeof Tampon, stdin);
    return Tampon[0];
}


void AfficheRecord(struct Record *UnRecord)
{
    printf("%d\n", UnRecord->Numero);
    printf("%d\n", UnRecord->Valeur);
    printf("%s\n", UnRecord->Memo);
    printf("-----------------------\n");
}

void SaiSieRecord(struct Record *UnRecord)
{
    char Tampon[80];
    printf("Saisie numero :");
    fgets(Tampon, sizeof Tampon, stdin);
    UnRecord->Numero = atoi(Tampon);
    printf("Saisie valeur :");
    fgets(Tampon, sizeof Tampon, stdin);
    UnRecord->Valeur = atoi(Tampon);
    printf("Saisie Tampon :");
    fgets(UnRecord->Memo, sizeof UnRecord->Memo, stdin);
    DelNewLine(UnRecord->Memo);
    AfficheRecord(UnRecord);
    return;
}

main()
{
    struct Record UnRecord;
    FILE *Fichier;
    char NomFichier[80];
    char Tampon[80];
    int Numero;
    int nbr, nbr2;
    int Trouve;

    printf("Le nom de fichier Ã  Lire :)");
    fgets(NomFichier, sizeof NomFichier, stdin);
    DelNewLine(NomFichier);
    Fichier = fopen(NomFichier, "r+");	/* Si le fichier existe, on le cree sinon on ajoute */
    if (Fichier == NULL) {
	fprintf(stderr, "Echec Ouverture\n");
	exit(0);
    } else
	fprintf(stderr, "Ouverture reussie \n");

    printf("Saisie numero :");
    fgets(Tampon, sizeof Tampon, stdin);
    Numero = atoi(Tampon);
    /* pour montrer les possibilités de l accés direct on commence par la fin */

    Trouve = 0;
    nbr = fseek(Fichier, 0, SEEK_END);
    /* fseek ne retourne pas la nouvelle position mais ftell */
    nbr = ftell(Fichier);
    printf("Fin de Fichier %d\n", nbr);

    while ((nbr != 0) && (!Trouve)) {
	/* on recule pour lire le suivant */
	nbr = fseek(Fichier, -sizeof(UnRecord), SEEK_CUR);
	nbr = ftell(Fichier);
	nbr2 = fread(&UnRecord, sizeof(UnRecord), 1, Fichier);
	printf("Premier Record  Position %d Bytes Lus %d Numero %d\n", nbr,
	       nbr2, UnRecord.Numero);
	/* On se replace au debut du record */
	nbr = fseek(Fichier, -sizeof(UnRecord), SEEK_CUR);
	nbr = ftell(Fichier);
	if (UnRecord.Numero == Numero)
	    Trouve = 1;
    }

    if (Trouve)
	AfficheRecord(&UnRecord);
    fclose(Fichier);
}
