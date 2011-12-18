#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../EcranX/EcranX.h"
#include "Grille.h"

void *FctThreadRefresh(void *p);

#define MY_CANON1           1001
#define MY_CANON2           1002
#define MY_MISSILE          1003
#define MY_ALIEN            1004
#define MY_BOMBE            1005
#define MY_VAISSEAU_AMIRAL  1006

GRILLE grilleSpaceInvader;

/****************************************************************************************/
int OuvrirGrille(int Ligne, int Colonne, int TailleCarre, const char *titre,
		 int modeG)
{
    int i, hauteur, largeur, l, c;
    GRILLE *pg = &grilleSpaceInvader;

    if ((Ligne <= 0) || (Colonne <= 0) || (TailleCarre <= 1)
	|| (Ligne > 100) || (Colonne > 100))
	return -1;

    for (l = 0; l < Ligne; l++)
	for (c = 0; c < Colonne; c++)
	    pg->tab[l][c] = BLANC;

    pg->Ligne = Ligne;
    pg->Colonne = Colonne;
    pg->TailleCarre = TailleCarre;
    pg->modeGrille = modeG;

    hauteur = 1 + Ligne * TailleCarre;
    largeur = 1 + Colonne * TailleCarre;

    if (CreeTermGraph(&(pg->tc), largeur, hauteur, titre) == -1) {
	perror("Erreur de CreeTermGraph ");
	return (-1);
    }

    pthread_mutex_init(&(pg->MUTEX), NULL);
    pg->alive = 1;
    pthread_create(&(pg->threadRefresh), NULL, FctThreadRefresh,
		   (void *) pg);

    return 0;
}

/****************************************************************************************/
void DessinerGrillage(GRILLE * pg)
{
    int i, hauteur, largeur, couleur;
    hauteur = 1 + pg->Ligne * pg->TailleCarre;
    largeur = 1 + pg->Colonne * pg->TailleCarre;
    couleur = GRIS;
    if (pg->modeGrille == GRILLE_OFF)
	couleur = NOIR;

    pthread_mutex_lock(&(pg->MUTEX));
    if (pg->alive) {
	setEpaisseurCrayon(&(pg->tc), 1);

	for (i = 0; i <= pg->Colonne; i++)
	    DessineLigne(&(pg->tc), (i * pg->TailleCarre), 0,
			 (i * pg->TailleCarre), (hauteur - 1), couleur);
	for (i = 0; i <= pg->Ligne; i++)
	    DessineLigne(&(pg->tc), 0, (i * pg->TailleCarre),
			 (largeur - 1), (i * pg->TailleCarre), couleur);
    }
    pthread_mutex_unlock(&(pg->MUTEX));
}

/****************************************************************************************/
int FermerGrille()
{
    GRILLE *pg = &grilleSpaceInvader;

    pthread_cancel(pg->threadRefresh);

    pthread_mutex_lock(&(pg->MUTEX));
    FermeTermGraph(&(pg->tc));
    pg->alive = 0;
    pthread_mutex_unlock(&(pg->MUTEX));

    pthread_mutex_destroy(&(pg->MUTEX));
    return 0;
}

/****************************************************************************************/
int DessineCarre(GRILLE * pg, int ligne, int colonne, int couleur)
{
    int xa, ya, xb, yb;

    if ((ligne >= 0) && (ligne < pg->Ligne) && (colonne >= 0)
	&& (colonne < pg->Colonne)) {
	pthread_mutex_lock(&(pg->MUTEX));
	if (pg->alive) {
	    pg->tab[ligne][colonne] = couleur;

	    xa = 1 + colonne * pg->TailleCarre;
	    ya = 1 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre - 2;
	    yb = ya + pg->TailleCarre - 2;

	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, couleur, PLEIN);
	}
	pthread_mutex_unlock(&(pg->MUTEX));
	return 0;
    }

    return -1;
}

/****************************************************************************************/
void *FctThreadRefresh(void *p)
{
    int l, c;
    int xa, ya, xb, yb;
    struct timespec temps;
    GRILLE *pg = (GRILLE *) p;

    temps.tv_sec = 1;
    temps.tv_nsec = 0;

    while (1) {
	DessinerGrillage(pg);
	pthread_mutex_lock(&(pg->MUTEX));
	if (pg->alive) {
	    for (l = 0; l < pg->Ligne; l++)
		for (c = 0; c < pg->Colonne; c++) {
		    if (pg->tab[l][c] < 1000) {
			xa = 1 + c * pg->TailleCarre;
			ya = 1 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre - 2;
			yb = ya + pg->TailleCarre - 2;

			DessineRectangle(&(pg->tc), xa, ya, xb, yb,
					 pg->tab[l][c], PLEIN);
		    }

		    if (pg->tab[l][c] == MY_CANON1) {
			// Fond noir
			xa = 1 + c * pg->TailleCarre;
			ya = 1 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre - 2;
			yb = ya + pg->TailleCarre - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR,
					 PLEIN);

			// Base du canon
			xa = 1 + pg->TailleCarre / 8 + c * pg->TailleCarre;
			ya = 1 + 5 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 3 * pg->TailleCarre / 4 - 2;
			yb = ya + pg->TailleCarre / 4 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLANC,
					 PLEIN);

			// Tete du canon
			xa = 1 + 3 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + pg->TailleCarre / 8 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre / 4 - 2;
			yb = ya + 3 * pg->TailleCarre / 4 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLANC,
					 PLEIN);
		    }

		    if (pg->tab[l][c] == MY_CANON2) {
			// Fond noir
			xa = 1 + c * pg->TailleCarre;
			ya = 1 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre - 2;
			yb = ya + pg->TailleCarre - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR,
					 PLEIN);

			// Base du canon
			xa = 1 + pg->TailleCarre / 8 + c * pg->TailleCarre;
			ya = 1 + 5 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 3 * pg->TailleCarre / 4 - 2;
			yb = ya + pg->TailleCarre / 4 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);

			// Tete du canon
			xa = 1 + 3 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + pg->TailleCarre / 8 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre / 4 - 2;
			yb = ya + 3 * pg->TailleCarre / 4 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);
		    }

		    if (pg->tab[l][c] == MY_MISSILE) {
			// Fond noir
			xa = 1 + c * pg->TailleCarre;
			ya = 1 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre - 2;
			yb = ya + pg->TailleCarre - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR,
					 PLEIN);

			// Corps du missile
			xa = 1 + 3 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + pg->TailleCarre / 4 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre / 4 - 2;
			yb = ya + pg->TailleCarre / 2 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE,
					 PLEIN);
		    }

		    if (pg->tab[l][c] == MY_BOMBE) {
			// Fond noir
			xa = 1 + c * pg->TailleCarre;
			ya = 1 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre - 2;
			yb = ya + pg->TailleCarre - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR,
					 PLEIN);

			// Corps de la bombe jaune
			xa = 1 + pg->TailleCarre / 3 + c * pg->TailleCarre;
			ya = 1 + pg->TailleCarre / 3 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre / 3 - 2;
			yb = ya + pg->TailleCarre / 3 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, JAUNE,
					 PLEIN);
		    }

		    if (pg->tab[l][c] == MY_VAISSEAU_AMIRAL) {
			// Fond noir
			xa = 1 + c * pg->TailleCarre;
			ya = 1 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre - 2;
			yb = ya + pg->TailleCarre - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR,
					 PLEIN);

			// Corps horizontal
			xa = 1 + pg->TailleCarre / 8 + c * pg->TailleCarre;
			ya = 1 + 2 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 6 * pg->TailleCarre / 8 - 2;
			yb = ya + 3 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);

			// Corps vertical
			xa = 1 + 2 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 1 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 4 * pg->TailleCarre / 8 - 2;
			yb = ya + 5 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);

			// jambe gauche
			xa = 1 + 2 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 1 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 6 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);

			// jambe droite
			xa = 1 + 5 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 1 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 6 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);

			// Pied gauche
			xa = 1 + 1 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 6 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 2 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);

			// Pied droit
			xa = 1 + 5 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 6 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 2 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU,
					 PLEIN);

			// oeil gauche
			xa = 1 + 2 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 3 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE,
					 PLEIN);

			// oeil droit
			xa = 1 + 5 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 3 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE,
					 PLEIN);
		    }

		    if (pg->tab[l][c] == MY_ALIEN) {
			// Fond noir
			xa = 1 + c * pg->TailleCarre;
			ya = 1 + l * pg->TailleCarre;
			xb = xa + pg->TailleCarre - 2;
			yb = ya + pg->TailleCarre - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR,
					 PLEIN);

			// Corps horizontal
			xa = 1 + pg->TailleCarre / 8 + c * pg->TailleCarre;
			ya = 1 + 2 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 6 * pg->TailleCarre / 8 - 2;
			yb = ya + 3 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT,
					 PLEIN);

			// Corps vertical
			xa = 1 + 2 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 1 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 4 * pg->TailleCarre / 8 - 2;
			yb = ya + 5 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT,
					 PLEIN);

			// jambe gauche
			xa = 1 + 2 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 1 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 6 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT,
					 PLEIN);

			// jambe droite
			xa = 1 + 5 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 1 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 6 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT,
					 PLEIN);

			// Pied gauche
			xa = 1 + 1 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 6 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 2 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT,
					 PLEIN);

			// Pied droit
			xa = 1 + 5 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 6 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 2 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT,
					 PLEIN);

			// oeil gauche
			xa = 1 + 2 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 3 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE,
					 PLEIN);

			// oeil droit
			xa = 1 + 5 * pg->TailleCarre / 8 +
			    c * pg->TailleCarre;
			ya = 1 + 3 * pg->TailleCarre / 8 +
			    l * pg->TailleCarre;
			xb = xa + 1 * pg->TailleCarre / 8 - 2;
			yb = ya + 1 * pg->TailleCarre / 8 - 2;
			DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE,
					 PLEIN);
		    }
		}
	}
	pthread_mutex_unlock(&(pg->MUTEX));

	nanosleep(&temps, NULL);
    }
}

/***** Fonctions specifiques à SpaceInvader *****/
void DessineVide(int ligne, int colonne)
{
    DessineCarre(&grilleSpaceInvader, ligne, colonne, NOIR);
}

void DessineCanon(int ligne, int colonne, int joueur)
{
    int xa, ya, xb, yb;
    int couleur;
    GRILLE *pg = &grilleSpaceInvader;

    if ((ligne >= 0) && (ligne < pg->Ligne) && (colonne >= 0)
	&& (colonne < pg->Colonne)) {
	pthread_mutex_lock(&(pg->MUTEX));
	if (pg->alive) {
	    if (joueur == 1) {
		pg->tab[ligne][colonne] = MY_CANON1;
		couleur = BLANC;
	    }

	    if (joueur == 2) {
		pg->tab[ligne][colonne] = MY_CANON2;
		couleur = BLEU;
	    }
	    // Fond noir
	    xa = 1 + colonne * pg->TailleCarre;
	    ya = 1 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre - 2;
	    yb = ya + pg->TailleCarre - 2;

	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR, PLEIN);

	    // Base du canon
	    xa = 1 + pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 5 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 3 * pg->TailleCarre / 4 - 2;
	    yb = ya + pg->TailleCarre / 4 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, couleur, PLEIN);

	    // Tete du canon
	    xa = 1 + 3 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre / 4 - 2;
	    yb = ya + 3 * pg->TailleCarre / 4 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, couleur, PLEIN);

	}
	pthread_mutex_unlock(&(pg->MUTEX));
    }
}

void DessineMissile(int ligne, int colonne)
{
    int xa, ya, xb, yb;
    GRILLE *pg = &grilleSpaceInvader;

    if ((ligne >= 0) && (ligne < pg->Ligne) && (colonne >= 0)
	&& (colonne < pg->Colonne)) {
	pthread_mutex_lock(&(pg->MUTEX));
	if (pg->alive) {
	    pg->tab[ligne][colonne] = MY_MISSILE;

	    // Fond noir
	    xa = 1 + colonne * pg->TailleCarre;
	    ya = 1 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre - 2;
	    yb = ya + pg->TailleCarre - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR, PLEIN);

	    // Corps du missile
	    xa = 1 + 3 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + pg->TailleCarre / 4 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre / 4 - 2;
	    yb = ya + pg->TailleCarre / 2 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE, PLEIN);
	}
	pthread_mutex_unlock(&(pg->MUTEX));
    }
}

void DessineBouclier(int ligne, int colonne, int niveau)
{
    int couleur;
    couleur = BLANC;
    if (niveau == 2)
	couleur = GRIS;

    DessineCarre(&grilleSpaceInvader, ligne, colonne, couleur);
}

void DessineAlien(int ligne, int colonne)
{
    int xa, ya, xb, yb;
    GRILLE *pg = &grilleSpaceInvader;

    if ((ligne >= 0) && (ligne < pg->Ligne) && (colonne >= 0)
	&& (colonne < pg->Colonne)) {
	pthread_mutex_lock(&(pg->MUTEX));
	if (pg->alive) {
	    pg->tab[ligne][colonne] = MY_ALIEN;

	    // Fond noir
	    xa = 1 + colonne * pg->TailleCarre;
	    ya = 1 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre - 2;
	    yb = ya + pg->TailleCarre - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR, PLEIN);

	    // Corps horizontal
	    xa = 1 + pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 2 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 6 * pg->TailleCarre / 8 - 2;
	    yb = ya + 3 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT, PLEIN);

	    // Corps vertical
	    xa = 1 + 2 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 1 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 4 * pg->TailleCarre / 8 - 2;
	    yb = ya + 5 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT, PLEIN);

	    // jambe gauche
	    xa = 1 + 2 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 1 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 6 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT, PLEIN);

	    // jambe droite
	    xa = 1 + 5 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 1 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 6 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT, PLEIN);

	    // Pied gauche
	    xa = 1 + 1 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 6 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 4 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT, PLEIN);

	    // Pied droit
	    xa = 1 + 5 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 6 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 4 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, VERT, PLEIN);

	    // oeil gauche
	    xa = 1 + 2 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 3 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE, PLEIN);

	    // oeil droit
	    xa = 1 + 5 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 3 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE, PLEIN);
	}
	pthread_mutex_unlock(&(pg->MUTEX));
    }
}

void DessineBombe(int ligne, int colonne)
{
    int xa, ya, xb, yb;
    GRILLE *pg = &grilleSpaceInvader;

    if ((ligne >= 0) && (ligne < pg->Ligne) && (colonne >= 0)
	&& (colonne < pg->Colonne)) {
	pthread_mutex_lock(&(pg->MUTEX));
	if (pg->alive) {
	    pg->tab[ligne][colonne] = MY_BOMBE;

	    // Fond noir
	    xa = 1 + colonne * pg->TailleCarre;
	    ya = 1 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre - 2;
	    yb = ya + pg->TailleCarre - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR, PLEIN);

	    // Corps de la bombe jaune
	    xa = 1 + pg->TailleCarre / 3 + colonne * pg->TailleCarre;
	    ya = 1 + pg->TailleCarre / 3 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre / 3 - 2;
	    yb = ya + pg->TailleCarre / 3 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, JAUNE, PLEIN);
	}
	pthread_mutex_unlock(&(pg->MUTEX));
    }
}

void DessineVaisseauAmiral(int ligne, int colonne)
{
    int xa, ya, xb, yb;
    GRILLE *pg = &grilleSpaceInvader;

    if ((ligne >= 0) && (ligne < pg->Ligne) && (colonne >= 0)
	&& (colonne < pg->Colonne)) {
	pthread_mutex_lock(&(pg->MUTEX));
	if (pg->alive) {
	    pg->tab[ligne][colonne] = MY_VAISSEAU_AMIRAL;

	    // Fond noir
	    xa = 1 + colonne * pg->TailleCarre;
	    ya = 1 + ligne * pg->TailleCarre;
	    xb = xa + pg->TailleCarre - 2;
	    yb = ya + pg->TailleCarre - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, NOIR, PLEIN);

	    // Corps horizontal
	    xa = 1 + pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 2 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 6 * pg->TailleCarre / 8 - 2;
	    yb = ya + 3 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU, PLEIN);

	    // Corps vertical
	    xa = 1 + 2 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 1 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 4 * pg->TailleCarre / 8 - 2;
	    yb = ya + 5 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU, PLEIN);

	    // jambe gauche
	    xa = 1 + 2 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 1 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 6 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU, PLEIN);

	    // jambe droite
	    xa = 1 + 5 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 1 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 6 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU, PLEIN);

	    // Pied gauche
	    xa = 1 + 1 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 6 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 4 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU, PLEIN);

	    // Pied droit
	    xa = 1 + 5 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 6 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 4 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, BLEU, PLEIN);

	    // oeil gauche
	    xa = 1 + 2 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 3 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE, PLEIN);

	    // oeil droit
	    xa = 1 + 5 * pg->TailleCarre / 8 + colonne * pg->TailleCarre;
	    ya = 1 + 3 * pg->TailleCarre / 8 + ligne * pg->TailleCarre;
	    xb = xa + 1 * pg->TailleCarre / 8 - 2;
	    yb = ya + 1 * pg->TailleCarre / 8 - 2;
	    DessineRectangle(&(pg->tc), xa, ya, xb, yb, ROUGE, PLEIN);
	}
	pthread_mutex_unlock(&(pg->MUTEX));
    }
}
