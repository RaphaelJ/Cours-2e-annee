#include "SpaceInvader.h"

int tab[NB_LIGNE][NB_COLONNE];
pthread_mutex_t mutexGrille;

int main(int argc, char *argv[])
{
	char buffer[80];
	srand((unsigned) time(NULL));
	
	// Ouverture du fichier Trace.log
// 	FILE *hfErr;
// 	if ((hfErr = fopen("Trace.log", "w")) == (FILE *) NULL) {
// 		Trace("(MAIN) Erreur ouverture fichier Trace.log");
// 		exit(1);
// 	}
// 	
// 	if (dup2(fileno(hfErr), 2) == -1) {
// 		Trace("(MAIN) Erreur de dup2...");
// 		exit(1);
// 	}
	
	// Initialisation
	pthread_mutex_init(&mutexGrille, NULL);
	initialiseGrille();
	initialiseMissiles();
	initialiseAliens();
	initialiseBombes();
	initialiseScore();
	nouveauCanon();
	
	// Jeu
	gestionTouches();
	
	// Fermeture
	FermerGrille();
	terminerMissiles();
	terminerAliens();
	terminerBombes();
	terminerScore();
	pthread_mutex_destroy(&mutexGrille);
	
	exit(0);
}

void initialiseGrille()
{
	printf("Ouverture de la grille de jeu...\n");
	if (OuvrirGrille(NB_LIGNE, NB_COLONNE, 25, // GRILLE_ON affiche la grille
			"Space Invader", GRILLE_OFF) == -1) {
		perror("Erreur de InitGrille");
		exit(-1);
	}
	
	for (int i = 0; i < NB_LIGNE; i++) {
		for (int j = 0; j < NB_COLONNE; j++) {
			tab[i][j] = VIDE;
			DessineVide(i, j);
		}
	}
	
	// Boucliers
	int l = LGN_BOUCLIERS;
	for (int i = LGN_BOUCLIERS; i < LGN_BOUCLIERS + 2; i++) {
		tab[i][3] = BOUCLIER1;
		DessineBouclier(i, 3, 1);
		tab[i][4] = BOUCLIER1;
		DessineBouclier(i, 4, 1);
	
		tab[i][8] = BOUCLIER1;
		DessineBouclier(i, 8, 1);
		tab[i][9] = BOUCLIER1;
		DessineBouclier(i, 9, 1);

		tab[i][13] = BOUCLIER1;
		DessineBouclier(i, 13, 1);
		tab[i][14] = BOUCLIER1;
		DessineBouclier(i, 14, 1);
	}
}

void initialiseBoucliers()
{
	// Boucliers
	int l = LGN_BOUCLIERS;
	for (int i = LGN_BOUCLIERS; i < LGN_BOUCLIERS + 2; i++) {
		tab[i][3] = BOUCLIER1;
		DessineBouclier(i, 3, 1);
		tab[i][4] = BOUCLIER1;
		DessineBouclier(i, 4, 1);
	
		tab[i][8] = BOUCLIER1;
		DessineBouclier(i, 8, 1);
		tab[i][9] = BOUCLIER1;
		DessineBouclier(i, 9, 1);

		tab[i][13] = BOUCLIER1;
		DessineBouclier(i, 13, 1);
		tab[i][14] = BOUCLIER1;
		DessineBouclier(i, 14, 1);
	}
}

void gestionTouches()
{
	char c;
	do {
		c = ReadChar();
		switch (c) {
		case KEY_LEFT:
			kill(getpid(), SIGUSR1);
			break;
		case KEY_RIGHT:
			kill(getpid(), SIGUSR2);
			break;
		case KEY_UP: case KEY_DOWN:
		case KEY_SPACE:
			kill(getpid(), SIGHUP);
			break;
		}
	} while (c != 'q'); // q pour quitter
}