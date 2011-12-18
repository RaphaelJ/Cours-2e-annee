#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "Person.h"

using namespace std;

Person::Person()
{
	this->setNom("Inconnu");
	this->setPrenom("Inconnu");
	this->setNationalite("Inconnue");
}
Person::Person(const Person& person)
{
	*this = person;
}
Person::Person(const char* nom, const char* prenom, const Date dateNaissance,
	       const char* nationalite)
{
	this->setNom(nom);
	this->setPrenom(prenom);
	this->setDateNaissance(dateNaissance);
	this->setNationalite(nationalite);
}

Person::~Person()
{
}

void Person::setNom(const char* nom)
{
	this->nom = nom;
}
void Person::setPrenom(const char* prenom)
{
	this->prenom = prenom;
}
void Person::setNationalite(const char* nationalite)
{
	this->nationalite = nationalite;
}
void Person::setDateNaissance(const Date dateNaissance)
{
	this->dateNaissance = dateNaissance;
}

const char* Person::getNom() const
{
	cerr << "ok";
	return this->nom;
}
const char* Person::getPrenom() const
{
	return this->prenom;
}
const char* Person::getNationalite() const
{
	return this->nationalite;
}
Date Person::getDateNaissance() const
{
	return this->dateNaissance;
}

const char* Person::getIdentification() const
{
	return this->getNom();
}

void Person::save(ostream& stream) const
{
	char prenomBuff[255];
	strcpy(prenomBuff, this->getPrenom());
	char nomBuff[255];
	strcpy(nomBuff, this->getNom());
	
	char dateBuff[11];
	sprintf(dateBuff, "%02d/%02d/%04d",
		this->getDateNaissance().getJour(),
		this->getDateNaissance().getMois(),
		this->getDateNaissance().getAnnee()
	);
	
	char nationaliteBuff[255];
	strcpy(nationaliteBuff, this->getNationalite());
	
	stream.write(prenomBuff, sizeof prenomBuff);
	stream.write(nomBuff, sizeof nomBuff);
	stream.write(dateBuff, sizeof dateBuff);
	stream.write(nationaliteBuff, sizeof nationaliteBuff);
}

// Retourne true si la personne a bien été chargée
bool Person::load(istream& stream)
{
	char buffer[255 + 255 + 11 + 255];
	
	stream.read(buffer, sizeof buffer);
	
	if (stream.gcount() <= 0) // EOF
		return false;
	else {
		this->setPrenom(buffer);
		this->setNom(buffer + 255);
		this->setDateNaissance(Date(buffer + 255*2));
		this->setNationalite(buffer + 255*3);
		
		return true;
	}
}

ostream& Person::insert(ostream& output) const
{
	output << "Nom: " << this->getNom() << " - "
	       << "Prenom: " << this->getPrenom() << " - "
	       << "Nationalité: " << this->getNationalite()
	       << endl;
	       
	return output;
}

ostream& operator<<(ostream& output, const Person& p)
{
	return p.insert(output);
}

Person& Person::pull(istream& input)
{	
	char *nom = new char[STRINGS_SIZE],
	     *prenom = new char[STRINGS_SIZE],
	     *nationalite = new char[STRINGS_SIZE],
	     *dateNaissance = new char[STRINGS_SIZE];	  
	     
	cout << "Nom: ";
	input >> nom;
	cout << "Prenom: ";
	input >> prenom;
	cout << "Nationalité: ";
	input >> nationalite;
	cout << "Date (##/##/####): ";
	input >> dateNaissance;
	
	this->setNom(nom);
	this->setPrenom(prenom);
	this->setNationalite(nationalite);
	Date date(dateNaissance);
	this->setDateNaissance(date);
	
	return *this;
}

Person& operator>>(istream& input, Person& p)
{
	return p.pull(input);
}

void Person::Affiche() const
{
	cout << *this;
}
void Person::affiche() const
{
	this->Affiche();
}

Person& Person::operator=(const Person& p2)
{
	this->setNom(p2.getNom());
	this->setPrenom(p2.getPrenom());
	this->setNationalite(p2.getNationalite());
	this->setDateNaissance(p2.getDateNaissance());
}

bool Person::operator<=(const Person& p2) const
{
	return strcmp(this->getNom(), p2.getNom()) <= 0;
}

bool Person::operator>=(const Person& p2) const
{
	return strcmp(this->getNom(), p2.getNom()) >= 0;
}