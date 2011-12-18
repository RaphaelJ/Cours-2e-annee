#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Race.h"

using namespace std;

Race::Race()
{
	this->setCircuit(new Circuit());
	this->setDate(Date());
	this->setNbTours(1);
}
Race::Race(const Race& race)
{
	*this = race;
}
Race::Race(Circuit* circuit, const Date date, const int nbTours)
{
	this->setCircuit(circuit);
	this->setDate(date);
	this->setNbTours(nbTours);
}
Race::Race(const char* nom, const char* date, const int nbTours)
{
	this->setNom(nom);
	this->setDate(date);
	this->setNbTours(nbTours);
}

Race::~Race()
{
}

void Race::setCircuit(Circuit* circuit)
{
	this->circuit = circuit;
}
void Race::setCircuit(const char* nom)
{
	this->setNom(nom);
}
void Race::setNom(const char* nom)
{
	if (this->circuit == NULL)
		throw "Circuit doit être défini";
	this->circuit->setNom(nom);
}
void Race::setDate(const Date date)
{
	this->date = date;
}
void Race::setDate(const char* date)
{
	this->date = Date(date);
}
void Race::setNbTours(const int nbTours)
{
	if (nbTours <= 0)
		throw InvalidRaceSizeException();
	this->nbTours = nbTours;
}

Circuit* Race::getCircuit() const
{
	return this->circuit;
}
const char* Race::getNom() const
{
	return this->getCircuit()->getNom();
}
Date Race::getDate() const
{
	return this->date;
}
int Race::getNbTours() const
{
	return this->nbTours;
}
float Race::getRaceLength() const
{
	if (this->getCircuit() == NULL)
		throw "Circuit non défini";
	
	return this->getNbTours()
	       *this->getCircuit()->getLongueur();
}

void Race::Affiche() const
{
	cout << *this;
}

void Race::affiche() const
{
	this->Affiche();
}

Race& Race::operator=(const Race& race2)
{
	this->setCircuit(race2.getCircuit());
	this->setDate(race2.getDate());
	this->setNbTours(race2.getNbTours());
}

ostream& operator<<(ostream& stream, Race r)
{
	if (r.getCircuit() == NULL)
		stream << "Circuit non défini" << endl;
	else
		stream << *(r.getCircuit());
	
	stream  << "Nombre de tours : " << r.getNbTours() << endl;
	
	stream  << "Date de la course : " << r.getDate() << endl;
	
	return stream;
}