#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Race.h"

using namespace std;

const char* Race::defaultDate = "01/01/1991";

Race::Race()
{
	this->setNom(NULL);
	this->setDate(Race::defaultDate);
	this->setNbTours(0);
}
Race::Race(const Race& race)
{
	char* nomCpy;
	if (race.getNom() == NULL)
		nomCpy = NULL;
	else {
		nomCpy = new char[strlen(race.getNom()) + 1];
		strcpy(nomCpy, race.getNom());
	}
	this->setNom(nomCpy);
	this->setDate(race.getDate());
	this->setNbTours(race.getNbTours());
}
Race::Race(char* nom, char* date, int nbTours)
{
	this->setNom(nom);
	this->setDate(date);
	this->setNbTours(nbTours);
}

Race::~Race()
{
	delete this->Nom;
}

void Race::setNom(char* nom)
{
	if (nom != NULL) {
		if (strlen(nom) > 30)
			throw "Nom ne peut pas faire plus de 30 caractères";
	
		this->Nom = new char[strlen(nom) + 1];
		strcpy(this->Nom, nom);
	} else
		this->Nom = NULL;
}
void Race::setCircuit(char* nom)
{
	this->setNom(nom);
}
void Race::setDate(const char date[11])
{
	if (strlen(date) != 10)
		throw "Date doit faire 10 caractères";
	strcpy(this->Date, date);
}
void Race::setNbTours(const int nbTours)
{
	if (nbTours < 0)
		throw "NbTours doit être positif ou nul";
	this->NbTours = nbTours;
}

char* Race::getNom() const
{
	return this->Nom;
}
char* Race::getCircuit() const
{
	return
	this->getNom();
}
const char* Race::getDate() const
{
	return this->Date;
}
int Race::getNbTours() const
{
	return this->NbTours;
}

void Race::Affiche() const
{
	if (this->getNom() == NULL
	    || this->getDate() == NULL)
		cout << "Circuit non défini" << endl;
	else {
		cout << "Circuit " << this->getNom() << endl;
		cout << endl;
		cout << "Date: " << this->getDate() << endl;
		cout << "Tours: " << this->getNbTours() << endl;
	}
}

void Race::affiche() const
{
	this->Affiche();
}