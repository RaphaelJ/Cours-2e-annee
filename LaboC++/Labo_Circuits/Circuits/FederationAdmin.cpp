#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "FederationAdmin.h"

using namespace std;

FederationAdmin::FederationAdmin()
	: AuthorizedPerson()
{
	this->setCompetition("Inconnue");
}
FederationAdmin::FederationAdmin(const FederationAdmin& fedadm)
{
	*this = fedadm;
}
FederationAdmin::FederationAdmin(const char* nom, const char* prenom,
				 const Date dateNaissance, const char* nationalite,
				 const char* competition)
	: AuthorizedPerson(nom, prenom, dateNaissance, nationalite)
{
	this->setCompetition(competition);
}

FederationAdmin::~FederationAdmin()
{

}

void FederationAdmin::setCompetition(const char* competition)
{
	this->competition = competition;
}

const char* FederationAdmin::getCompetition() const
{
	return this->competition;
}

const char* FederationAdmin::getIdentification() const
{
	char* id = new char[strlen("FEDERATION : #")
		+ strlen(this->getCompetition())
		+ strlen(this->getNom())
		+ 1];

	sprintf(id, "FEDERATION : %s#%s", this->getCompetition(), 
		this->getNom());
	
	return id;
}

void FederationAdmin::save(ostream& stream) const
{
	AuthorizedPerson::save(stream);
	
	char competitionBuff[255];
	strcpy(competitionBuff, this->getCompetition());
	
	stream.write(competitionBuff, sizeof competitionBuff);
}

bool FederationAdmin::load(istream& stream)
{
	if (AuthorizedPerson::load(stream)) {
		char buffer[255];
	
		stream.read(buffer, sizeof buffer);
		
		this->setCompetition(buffer);
	} else
		return false;
}

ostream& FederationAdmin::insert(ostream& output) const
{
	output << "Nom: " << this->getNom() << " - "
	       << "Prenom: " << this->getPrenom() << " - "
	       << "Nationalité: " << this->getNationalite() << " - "
	       << "Competition: " << this->getCompetition()
	       << endl;
	       
	return output;
}

Person& FederationAdmin::pull(istream& input)
{
	Person::pull(input);
	
	char *compet = new char[STRINGS_SIZE];
	
	cout << "Competition: ";
	input >> compet;
	
	this->setCompetition(compet);
	
	return *this;
}

FederationAdmin& FederationAdmin::operator=(const FederationAdmin& fa2)
{
	this->setNom(fa2.getNom());
	this->setPrenom(fa2.getPrenom());
	this->setNationalite(fa2.getNationalite());
	this->setDateNaissance(fa2.getDateNaissance());
	this->setCompetition(fa2.getCompetition());
}
