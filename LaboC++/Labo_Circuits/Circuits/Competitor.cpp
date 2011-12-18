#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "Competitor.h"

using namespace std;

Competitor::Competitor()
	: Person()
{
	this->setDossard(0);
	this->setScore(0);
}
Competitor::Competitor(const Competitor& competitor)
{
	*this = competitor;
}
Competitor::Competitor(const char* nom, const char* prenom,
		       const Date dateNaissance, const char* nationalite,
		       const int dossard, const int score)
	: Person(nom, prenom, dateNaissance, nationalite)
{
	this->setDossard(dossard);
	this->setScore(score);
}

Competitor::~Competitor()
{
}

void Competitor::setDossard(const int dossard)
{
	this->dossard = dossard;
}
void Competitor::setScore(const int score)
{
	this->score = score;
}

const int Competitor::getDossard() const
{
	return this->dossard;
}
const int Competitor::getScore() const
{
	return this->score;
}

const char* Competitor::getIdentification() const
{
	char* id = new char[strlen("PILOT : ##") 
		+ strlen(this->getNom())
		+ 12 // dossard
		+ 12 // score
		+ 1];
	
	sprintf(id, "PILOT : %s#%d#%d", this->getNom(), 
		this->getDossard(), this->getScore());
	
	return id;
}

void Competitor::save(ostream& stream) const
{
	Person::save(stream);
	
	stream.write((char*) &(this->dossard), sizeof this->dossard);
	stream.write((char*) &(this->score), sizeof this->score);
}

bool Competitor::load(istream& stream)
{
	if (Person::load(stream)) {
		stream.read((char*) &(this->dossard), sizeof this->dossard);
		stream.read((char*) &(this->score), sizeof this->score);
	} else
		return false;
}

ostream& Competitor::insert(ostream& output) const
{
	output << "Nom du pilote: " << this->getNom() << " - "
	       << "Prenom: " << this->getPrenom() << " - "
	       << "Nationalité: " << this->getNationalite() << " - "
	       << "Dossard: " << this->getDossard() << " - "
	       << "Score: " << this->getScore()
	       << endl;
	       
	return output;
}

Person& Competitor::pull(istream& input)
{
	Person::pull(input);
	
	int score, dossard;
	
	cout << "Dossard: ";
	input >> dossard;
	cout << "Score: ";
	input >> score;
	
	this->setDossard(dossard);
	this->setScore(score);
	
	return *this;
}

Competitor& Competitor::operator=(const Competitor& c2)
{
	this->setNom(c2.getNom());
	this->setPrenom(c2.getPrenom());
	this->setNationalite(c2.getNationalite());
	this->setDateNaissance(c2.getDateNaissance());
	this->setDossard(c2.getDossard());
	this->setScore(c2.getScore());
}