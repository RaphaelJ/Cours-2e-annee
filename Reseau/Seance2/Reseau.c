#include "Reseau.h"

// Connecte le client
// Retourne un descripteur représentant la connexion
// physique
int ConnecterClient(int argc, char* argv[], struct Physique* conn)
{
	bzero(conn, sizeof(struct Physique));
	if (argc != 5) {
		printf("ConnecterClient: parametres CLI incorrects.\n");
		exit(1);
	}
	
	return CreerConnexion(conn, argv[1], atoi(argv[2]),
			      argv[3], atoi(argv[4]));
}

// Connecte le serveur
// Retourne un descripteur représentant la connexion
// physique
int ConnecterServeur(int argc, char* argv[], struct Physique* conn)
{
	bzero(conn, sizeof(struct Physique));
	if (argc != 3) {
		printf("ConnecterServeur: parametres CLI incorrects.\n");
		
		exit(1);
	}
	
	return CreerConnexion(conn, argv[1], atoi(argv[2]), NULL, 0);
}

int EnvoiClient(struct Physique* conn, void* data, int taille)
{
	return VersCouchePhysique(conn, data, taille);
}

int EnvoiServeur(struct Physique* conn, void* data, int taille)
{
	return Repondre(conn, data, taille);
}

int Reception(struct Physique* conn, void* data, int* taille)
{
	return OrigineCouchePhysique(conn, data, taille);
}

// Crée un gestionnaire d'événement sur *un* descripteur
// de fichier
int CreerEvenement(int desc, struct gEvenement* even, int secsTimeOut)
{
	#define NB_DESC 100
	/*static*/ int descsLecture[NB_DESC];
	/*static*/ int descsEcriture[NB_DESC];
	bzero(descsLecture, sizeof descsLecture);
	bzero(descsEcriture, sizeof descsEcriture);
	
	descsLecture[desc] = 1;
	descsLecture[0] = 1;
	
	return PrepareEvenement(even, descsLecture, descsEcriture,
	                        NB_DESC, secsTimeOut, 0);
}

// Attends la libération de la ressource
// 1 -> ok, desc indique le descripteur ayant du contenu en lecture
//     (0 si clavier)
// -1 -> probleme
// 0 -> timeout
int Attendre(struct gEvenement* even, int* desc)
{
	int descEcriture;
	
	return AttendreEvenement(even, desc, &descEcriture);
}