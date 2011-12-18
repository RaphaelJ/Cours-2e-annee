#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "TeamMember.h"

using namespace std;

TeamMember::TeamMember()
	: AuthorizedPerson()
{
	this->setTeam("Inconnue");
	this->setFunction("Inconnue");
}
TeamMember::TeamMember(const TeamMember& tm)
{
	*this = tm;
}
TeamMember::TeamMember(const char* nom, const char* prenom,
		       const Date dateNaissance, const char* nationalite,
		       const char* team, const char* function)
	: AuthorizedPerson(nom, prenom, dateNaissance, nationalite)
{
	this->setTeam(team);
	this->setFunction(function);
}

TeamMember::~TeamMember()
{

}

void TeamMember::setTeam(const char* team)
{
	this->team = team;
}
void TeamMember::setFunction(const char* function)
{
	this->function = function;
}

const char* TeamMember::getTeam() const
{
	return this->team;
}
const char* TeamMember::getFunction() const
{
	return this->function;
}

const char* TeamMember::getIdentification() const
{
	char *id = new char[strlen("TEAM : ##")
		+ strlen(this->getTeam())
		+ strlen(this->getNom())
		+ strlen(this->getFunction())
		+ 1];
	
	sprintf(id, "TEAM : %s#%s#%s", this->getTeam(), 
		this->getNom(), this->getFunction());
	
	return id;
}

void TeamMember::save(ostream& stream) const
{
	AuthorizedPerson::save(stream);
	
	char teamBuff[255];
	strcpy(teamBuff, this->getTeam());
	char functionBuff[255];
	strcpy(functionBuff, this->getFunction());
	
	stream.write(teamBuff, sizeof teamBuff);
	stream.write(functionBuff, sizeof functionBuff);
}

bool TeamMember::load(istream& stream)
{
	if (AuthorizedPerson::load(stream)) {
		char buffer[255 + 255];
	
		stream.read(buffer, sizeof buffer);
		
		this->setTeam(buffer);
		this->setFunction(buffer + 255);
		
		return true;
	} else
		return false;
}

ostream& TeamMember::insert(ostream& output) const
{
	output << "Nom: " << this->getNom() << " - "
	       << "Prenom: " << this->getPrenom() << " - "
	       << "Nationalité: " << this->getNationalite() << " - "
	       << "Team: " << this->getTeam() << " - "
	       << "Fonction: " << this->getFunction()
	       << endl;
	       
	return output;
}

Person& TeamMember::pull(istream& input)
{
	Person::pull(input);
	
	char *team = new char[STRINGS_SIZE],
	     *function = new char[STRINGS_SIZE];
	
	cout << "Team: ";
	input >> team;
	cout << "Function: ";
	input >> function;
	
	this->setTeam(team);
	this->setFunction(function);
	
	return *this;
}

TeamMember& TeamMember::operator=(const TeamMember& tm2)
{
	this->setNom(tm2.getNom());
	this->setPrenom(tm2.getPrenom());
	this->setNationalite(tm2.getNationalite());
	this->setDateNaissance(tm2.getDateNaissance());
	this->setLogin(tm2.getLogin());
	this->setTeam(tm2.getTeam());
	this->setFunction(tm2.getFunction());
}
