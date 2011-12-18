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
int ConnecterServeurE(int argc, char* argv[], struct Physique* conn)
{
	bzero(conn, sizeof(struct Physique));
	if (argc != 5) {
		printf("ConnecterServeur: parametres CLI incorrects.\n");
		
		exit(1);
	}
	
	return CreerConnexion(conn, argv[1], atoi(argv[2]), NULL, 0);
}
int ConnecterServeurP(int argc, char* argv[], struct Physique* conn)
{
	bzero(conn, sizeof(struct Physique));
	if (argc != 5) {
		printf("ConnecterServeur: parametres CLI incorrects.\n");
		
		exit(1);
	}
	
	return CreerConnexion(conn, argv[1], atoi(argv[3]), NULL, 0);
}
int ConnecterServeurS(int argc, char* argv[], struct Physique* conn)
{
	bzero(conn, sizeof(struct Physique));
	if (argc != 5) {
		printf("ConnecterServeur: parametres CLI incorrects.\n");
		
		exit(1);
	}
	
	return CreerConnexion(conn, argv[1], atoi(argv[4]), NULL, 0);
}

// unsigned char CalculerCRC(void* data, int taille)
// {
// 	// Polynome de CRC-8
// 	// x**8 + x**7 + x**6 + x**4 + x**2 + x**0
// 	// 1010 1011 = 0xD5
// 	const unsigned char polynome = 0xD5;
// 	
// 	char* idata = (char*) data;
// 	unsigned char reste = *idata >> 1;
// 	int i;
// 	for (i=7; i < taille * 8; i++) { // Parcourt tous les bits
// 		// Shift le reste d'un bit avec report
// 		reste <<= 1;
// 		char nextByte = *(idata + i/8);
// 		if ((nextByte >> (7 - i%8)) & 1) // ie bit activé, report
// 			reste |= (unsigned char) 1;
// 		
// 		reste ^= polynome;
// 	}
// 	
// 	return reste;
// }

unsigned short CalculerCRC(void* data, int taille)
{
	long sum = 0; /* assume 32 bit long, 16 bit short */
	
	while (taille> 1)
	{
		sum += *((unsigned short *) data);
		if (sum & 0x80000000) /* if hogh-order bit set, fold */
			sum = (sum & 0xFFFF) + (sum >> 16);
		taille -= 2;
	}

	if (taille) /* take care of left over byte */
		sum += (unsigned short) * (unsigned char *)data;
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return ~sum;
}

int EnvoiClient(struct Physique* conn, REQUETE* requete)
{	
	requete->crc = CalculerCRC((void*) requete, (void*) &(requete->crc) - (void*) requete);
	return VersCouchePhysique(conn, requete, sizeof (REQUETE));
}

int EnvoiServeur(struct Physique* conn, REQUETE* requete)
{
	requete->crc = CalculerCRC(requete, (void*) &(requete->crc) - (void*) requete);
	return Repondre(conn, requete, sizeof (REQUETE));
}

// -1 : Erreur
// -2 : CRC
// >= 0 : OK
int Reception(struct Physique* conn, REQUETE* requete)
{
	int taille = sizeof (REQUETE);
	int retour = OrigineCouchePhysique(conn, requete, &taille);
	
	if (retour != -1) {
		unsigned short crc = CalculerCRC(requete, (void*) &(requete->crc) - (void*) requete);
		if (crc != requete->crc) {
			printf(
				"CRC non validée ! (%d != %d calculé)\n",
				requete->crc, crc
			);
			return -2;
		} else
			return retour;
	} else 
		return -1;
}

// Crée un gestionnaire d'événement sur *un* descripteur
// de fichier
int CreerEvenement(int desc, struct gEvenement* even, int secsTimeOut)
{
	return CreerEvenementMilisecs(desc, even, secsTimeOut, 0);
}
int CreerEvenementMulti(int desc,int desc2,int desc3, struct gEvenement* even, int secsTimeOut)
{
	return CreerEvenementMilisecsMulti(desc, desc2, desc3, even, secsTimeOut, 0);
}

int CreerEvenementMilisecs(int desc, struct gEvenement* even, int secsTimeOut,
                   int miliSecsTimeOut)
{
	#define NB_DESC 100
	/*static*/ int descsLecture[NB_DESC];
	/*static*/ int descsEcriture[NB_DESC];
	bzero(descsLecture, sizeof descsLecture);
	bzero(descsEcriture, sizeof descsEcriture);
	descsLecture[desc] = 1;
	
	descsLecture[0] = 1;
	
	return PrepareEvenement(even, descsLecture, descsEcriture,
	                        NB_DESC, secsTimeOut, miliSecsTimeOut);
}
int CreerEvenementMilisecsMulti(int desc,int desc2,int desc3, struct gEvenement* even, int secsTimeOut,
                   int miliSecsTimeOut)
{
	#define NB_DESC 100
	/*static*/ int descsLecture[NB_DESC];
	/*static*/ int descsEcriture[NB_DESC];
	bzero(descsLecture, sizeof descsLecture);
	bzero(descsEcriture, sizeof descsEcriture);
	descsLecture[desc] = 1;
	descsLecture[desc2] = 2;
	descsLecture[desc3] = 3;
	
	descsLecture[0] = 1;
	
	return PrepareEvenement(even, descsLecture, descsEcriture,
	                        NB_DESC, secsTimeOut, miliSecsTimeOut);
}

// Attends la libération de la ressource ou du timer
// 1 -> ok, desc indique le descripteur ayant du contenu en lecture
//     (0 si clavier). TIMEOUT si timer.
// -1 -> probleme
// 0 -> timeout de even
int AttendreTimer(struct gEvenement* even, int* desc, struct ListeTimer** Timer)
{
	int descEcriture;

	return AttendreEvenementtm(even, desc, &descEcriture, Timer);
}

// Attends la libération d'une ressource
// 1 -> ok, desc indique le descripteur ayant du contenu en lecture
//     (0 si clavier).
// -1 -> probleme
// 0 -> timeout
int Attendre(struct gEvenement* even, int* desc)
{
	int descEcriture;
	
	return AttendreEvenement(even, desc, &descEcriture);
}

// Demande une entier à l'utilisateur en lui laissant 15 sec
// Returne false si Timeout
bool EntreeTimeOut(int* donnees)
{
	int descClavier = 0;
	struct gEvenement evenClavier;
	
	// Crée un événement pour ne pas attendre plus de 15 secs
	if (CreerEvenement(descClavier, &evenClavier, 15) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	fflush(stdout);
	switch (Attendre(&evenClavier, &descClavier)) {
	case 1:
		scanf("%d", donnees);
			
		return true;
	case 0: // Timeout
		return false;
	case -1:
		printf("Erreur lors de l'attente de l'evenement\n");
		exit(1);
	};
}

// Transmet une requête au client et la renvoi s'il n'y a pas de réponse
// fct_demande est exécutée au départ et lance la première requête.
//	fct_demande retourne true si l'action a réussi, false sinon (timeout
//	sur l'entréee).
// fct_reception est exécutée lorsque la réponse est reçue.
// Si loop est faux, ne boucle plus après la première réception.
// Si annuler vaut true, l'utilisateur pourra stopper la boucle.
void Transmettre(struct Physique* conn, int connDescPhys, FILE* f, const char* nomAction, bool loop, bool annuler,
                 bool (*fct_demande)(FILE* f, struct Physique* conn, int connDescPhys, REQUETE* requeteEnvoyee),
                 void (*fct_reception)(FILE* f, struct Physique* conn, int connDescPhys, REQUETE requete))
{
	struct gEvenement even;
	struct ListeTimer* timers = NULL;
	
	if (CreerEvenementMilisecs(connDescPhys, &even, 0, 200000) == -1) {
		printf("Impossible d'armer l'evenement\n");
		exit(1);
	}
	
	int nbreTransmissions = 0;
	REQUETE requeteEnvoyee;
	
	// Si loop est faux, ne boucle plus après la première réception
	bool continueLoop = true;
	
	system("clear");
	printf("Appuyez sur %c+<Enter> pour l'action \"%s\".",
	       tolower(nomAction[0]), nomAction);
	if (annuler)
		printf(" Appuyez sur a+<Enter> pour annuler.\n");
	else
		printf("\n");
	
	while (continueLoop) {
		char Buffer[100];
		int desc;
		
		ListerFichier(f);
		
		printf("\nListe des timers: ");
		AfficheTimer(timers);
		
		int rc = AttendreTimer(&even, &desc, &timers);
		system("clear");
		if (rc == 1) { // OK
			if (desc == 0) { // Interrupt clavier
				fgets(Buffer, sizeof Buffer, stdin);
				if (nbreTransmissions > 0) {
					printf("Transaction précédente non validée\n");
				} else if (tolower(Buffer[0]) == tolower(nomAction[0])) {
					if (fct_demande(f, conn, connDescPhys, &requeteEnvoyee)) {
						// Si pas de timeout sur l'entrée de la demande
						printf("Num transfert ticket: %d\n", requeteEnvoyee.NumTicket);
						if (EnvoiClient(conn, &requeteEnvoyee) == -1) {
							printf("Erreur lors du renvoi des donnnées");
							exit(1);
						}
						
						timers = StopTimer(1, timers);
						timers = StartTimer(1, TIMOUT_RETRANSMISSIONS, timers);
						nbreTransmissions = 1;
						system("clear");
						printf("En attente de la réponse du serveur ...\n");
					} else {
						system("clear");
						printf("Timeout\n");
					}
				} else if (annuler && tolower(Buffer[0]) == 'a') {
					continueLoop = false;
					
					system("clear");
					printf("Annulation\n");
				} else
					printf("Interruption clavier\n", Buffer);
			} else if (desc == connDescPhys) { // Reception des données
				int donneesRecues = sizeof (REQUETE);
				timers = StopTimer(1, timers);
				
				if (Reception(conn, &requeteEnvoyee) == -1) {
					printf("Erreur lors de la reception des données");
					exit(1);
				}
				fct_reception(f, conn, connDescPhys, requeteEnvoyee);
				
				continueLoop = loop;
				nbreTransmissions = 0;
			}
		} else if (rc >= TIMEOUT) { // Timeout renvoi
			timers = StopTimer(1, timers);
			if (nbreTransmissions >= NBRE_RETRANSMISSIONS) {
				nbreTransmissions = 0;
				//transactionEnCours = -1;
				printf("Erreur lors de la transmission de la demande\n");
			} else { // Réessaye
				if (EnvoiClient(conn, &requeteEnvoyee) == -1) {
					printf("Erreur lors du renvoi des donnnées");
					exit(1);
				}
				timers = StartTimer(1, TIMOUT_RETRANSMISSIONS, timers);
				nbreTransmissions += 1;
				printf("Renvoi de la demande au serveur (%d) ...\n",
					nbreTransmissions
				);
			}
		} else if (rc == 0) { // TIMOUT attente événement
			printf("Time out\n", Buffer);
			break;
		} else if (rc == -1) { // Erreur
			printf("Erreur lors de l'attente de l'evenement\n");
			exit(1);
		}
	}
}