#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>

#include "Circuits/Race.h"
#include "Circuits/Circuit.h"
#include "Circuits/Date.h"
#include "Circuits/Person.h"
#include "Circuits/Competitor.h"
#include "Circuits/AuthorizedPerson.h"
#include "Circuits/FederationAdmin.h"
#include "Circuits/TeamMember.h"
#include "Circuits/ExceptionBase.h"
#include "Circuits/MyVector.h"
#include "Circuits/MyList.h"
#include "Circuits/MySortedList.h"
#include "Circuits/FichierLog.h"
#include "Circuits/FichierBinaire.h"

// Ouverture du fichier de log
FichierLog log("RacingWorldChampionship.log");

MyVector<Circuit> circuits(20);
MySortedList<TeamMember> teamMembers = MySortedList<TeamMember>();
MySortedList<Competitor> competitors = MySortedList<Competitor>();
MySortedList<FederationAdmin> federationAdmins
	= MySortedList<FederationAdmin>();

void LireCircuits();
void LireTeamMembers();
void LireCompetitors();
void LireFederationAdmins();

void Connexion();

bool UtilisateurAutorise(char utilisateur[255], char motdepasse[255]);

bool EstAdministrateur(char utilisateur[255]);
bool EstTeamMember(char utilisateur[255]);
bool EstFederationAdmin(char utilisateur[255]);

void MenuAdministrateur(char utilisateur[255]);
void AfficherUtilisateurs(char utilisateur[255]);
void CreerFederationAdmin(char utilisateur[255]);
void CreerTeamMember(char utilisateur[255]);
void ChangerMotDePasseAdmin(char utilisateur[255]);
void AjouterCircuit(char utilisateur[255]);
void AfficherCircuits(char utilisateur[255]);

void MenuTeamMember(char utilisateur[255]);
void MenuFederationAdmin(char utilisateur[255]);

int main()
{
	LireCircuits();
	LireTeamMembers();
	LireCompetitors();
	LireFederationAdmins();
	
	Connexion();
}

void LireCircuits()
{
	FichierBinaire<Circuit> f("circuit.dat");
	
	FichierBinaireIterator<Circuit> ite = f.getIterator();
	
	int i = 0;
	while (!ite.end()) {
		circuits.setElement(i, *ite);
		
		++i;
		++ite;
	}
	
	log << "Circuits chargés";
}
void LireTeamMembers()
{
	FichierBinaire<TeamMember> f("TeamMembers.dat");
	
	FichierBinaireIterator<TeamMember> ite = f.getIterator();
	
	while (!ite.end()) {
		teamMembers.insere(*ite);
		++ite;
	}
	
	log << "TeamMembers chargés";
}

void LireCompetitors()
{

}

void LireFederationAdmins()
{
	FichierBinaire<FederationAdmin> f("FedAdmins.dat");
	
	FichierBinaireIterator<FederationAdmin> ite = f.getIterator();
	
	while (!ite.end()) {
		federationAdmins.insere(*ite);
		++ite;
	}
	
	log << "FederationAdmins chargés";
}

// Affiche le menu de connexion (utilisateur et mot de passe)
void Connexion()
{
	char utilisateur[255];
	char motdepasse[255];
	
	for (;;) {
		cout << "*** Welcome to RacingWorldChampionship ***" << endl;
		cout << "Nom d'utilisateur : ";
		cin >> utilisateur;
		cout << "Mot de passe : ";
		cin >> motdepasse;
		
		if (UtilisateurAutorise(utilisateur, motdepasse)) {
			if (EstAdministrateur(utilisateur))
				MenuAdministrateur(utilisateur);
			else if (EstTeamMember(utilisateur))
				MenuTeamMember(utilisateur);
			else if (EstFederationAdmin(utilisateur))
				MenuFederationAdmin(utilisateur);
			else
				cerr << "Pas d'informations sur l'utilisateur" << endl;
		} else {
			cout << "Nom d'utilisateur ou mot de passe invalide" << endl;
		}
	}
}

// Lit les utilisateurs dans le fichier login et retourne true si le mot de
// passe est valide
bool UtilisateurAutorise(char utilisateur[255], char motdepasse[255])
{
	FILE* f;
	if (EstAdministrateur(utilisateur)) {
		if ((f = fopen("Admin.txt", "r")) == NULL) {
			cerr << "Impossible d'ouvrir le fichier de login administrateur" << endl;
			exit(1);
		}
	} else {
		if ((f = fopen("Login.txt", "r")) == NULL) {
			cerr << "Impossible d'ouvrir le fichier de login" << endl;
			exit(1);
		}
	}
	
	char utilisateurBuff[255];
	char motdepasseBuff[255];
	
	while (fgets(utilisateurBuff, 254, f) != NULL
	       && fgets(motdepasseBuff, 254, f) != NULL) {
		// Remplace le \n par \0
		utilisateurBuff[strlen(utilisateurBuff) - 1] = '\0';
		motdepasseBuff[strlen(motdepasseBuff) - 1] = '\0';
		
		if (strcmp(utilisateur, utilisateurBuff) == 0
		    && strcmp(motdepasse, motdepasseBuff) == 0)
			return true;
	}
	
	return false;
}

// Retourne true si utilisateur == "admin"
bool EstAdministrateur(char utilisateur[255])
{
	return strcmp(utilisateur, "admin") == 0;
}
bool EstTeamMember(char utilisateur[255])
{
	ListIterator<TeamMember> ite = teamMembers.getIterator();
	
	while (!ite.end()) {
		if (strcmp((*ite).getLogin(), utilisateur) == 0)
			return true;
	}
	return false;
}

bool EstFederationAdmin(char utilisateur[255])
{
	ListIterator<FederationAdmin> ite = federationAdmins.getIterator();
	
	while (!ite.end()) {
		if (strcmp((*ite).getLogin(), utilisateur) == 0)
			return true;
	}
	return false;
}

void MenuAdministrateur(char utilisateur[255])
{
	log << utilisateur << " connecté en administrateur";
	
	char choix;
	do {
		cout << "*** RacingWorldChampionship – Administrator ***" << endl;
		cout << "***********************************************" << endl;
		cout << "Utilisateurs" << endl;
		cout << "\t1. Afficher la liste des utilisateurs" << endl;
		cout << "\t2. Créer un administrateur de fédération" << endl;
		cout << "\t3. Créer un administrateur d’équipe" << endl;
		cout << "\t4. Changer le mot de passe \"admin\"" << endl;
		cout << "Circuit" << endl;
		cout << "\t5. Ajouter un circuit" << endl;
		cout << "\t6. Afficher la liste des circuits disponibles" << endl;
		cout << "N. Nouvelle session" << endl;
		cout << "Q. Quitter l'application" << endl;
		
		cin >> choix;
		
		switch (choix) {
		case '1':
			AfficherUtilisateurs(utilisateur);
			break;
		case '2':
			CreerFederationAdmin(utilisateur);
			break;
		case '3':
			CreerTeamMember(utilisateur);
			break;
		case '4':
			ChangerMotDePasseAdmin(utilisateur);
			break;
		case '5':
			AjouterCircuit(utilisateur);
			break;
		case '6':
			AfficherCircuits(utilisateur);
			break;
		case 'Q': case 'q':
			log << utilisateur << " ferme l'application";
			exit(0);
			break;
		}
		
	} while (choix != 'N' || choix != 'n');
}

void AfficherUtilisateurs(char utilisateur[255])
{
	cout << "== TeamMembers ==" << endl;
	
	ListIterator<TeamMember> ite = teamMembers.getIterator();
	
	while (!ite.end()) {
		cout << *ite;
	}
}

void CreerFederationAdmin(char utilisateur[255])
{
	log << utilisateur << " crée un nouvel FedAmdmin";
	
	FederationAdmin fedAdm;
	
	cin >> fedAdm;
	
	federationAdmins.insere(fedAdm);
	
	FichierBinaire<FederationAdmin> f("FedAdmins.dat");
	f.save(fedAdm);
}

void CreerTeamMember(char utilisateur[255])
{
	log << utilisateur << " crée un nouveau TeamMember";
	TeamMember teamMem;
	
	cin >> teamMem;
	
	teamMembers.insere(teamMem);
	
	FichierBinaire<TeamMember> f("TeamMembers.dat");
	f.save(teamMem);
}

void ChangerMotDePasseAdmin(char utilisateur[255])
{
	log << utilisateur << " change le mot de passe admin";
	
	FILE* f;
	if ((f = fopen("Admin.txt", "w+")) == NULL) {
		cerr << "Impossible d'ouvrir le fichier de login administrateur" << endl;
		exit(1);
	}
	
	char mdp[255];
	
	cout << "Nouveau mot de passe : ";
	cin >> mdp;
	
	fwrite(mdp, strlen(mdp) + 1, 1, f);
}

void AjouterCircuit(char utilisateur[255])
{
	log << utilisateur << " crée un nouveau cirtcuit";
	char pays[255];
	char nom[255];
	float longueur;
	
	cout << "Pays : ";
	cin >> pays;
	cout << "Nom : ";
	cin >> nom;
	cout << "Longueur : ";
	cin >> longueur;
	
	Circuit c(pays, nom, longueur);
	
	circuits + c;
	
	FichierBinaire<Circuit> f("circuit.dat");
	f.save(c);
}

void AfficherCircuits(char utilisateur[255])
{
}

void MenuTeamMember(char utilisateur[255])
{
}

void MenuFederationAdmin(char utilisateur[255])
{
}