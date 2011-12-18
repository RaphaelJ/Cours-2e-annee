#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Circuit.h"

using namespace std;

Circuit Circuit::SPA_FRANCORCHAMPS("Belgique", "Spa-Francorchamps", 7.004f);
Circuit Circuit::SILVERSTONE("Angleterre", "Silverstone", 5.900f);

Circuit::Circuit()
{
	this->setPays(NULL);
	this->setNom(NULL);
	this->setLongueur(0.0f);
}
Circuit::Circuit(const Circuit& circuit)
{
	*this = circuit;
}
Circuit::Circuit(const char* pays, const char* nom, const float longueur)
{
	this->setPays(pays);
	this->setNom(nom);
	this->setLongueur(longueur);
}

Circuit::~Circuit()
{
}

void Circuit::setPays(const char* pays)
{
	this->pays = pays;
}
void Circuit::setNom(const char* nom)
{
	this->nom = nom;
}
void Circuit::setLongueur(const float longueur)
{
	if (longueur < 0.0f)
		throw "La longueur doit être positive ou nulle";
	this->longueur = longueur;
}

const char* Circuit::getPays() const
{
	return this->pays;
}
const char* Circuit::getNom() const
{
	return this->nom;
}
float Circuit::getLongueur() const
{
	return this->longueur;
}

void Circuit::Affiche() const
{
	cout << *this;
}

void Circuit::affiche() const
{
	this->Affiche();
}

void Circuit::save(ostream& stream) const
{
	char paysBuff[255];
	strcpy(paysBuff, this->getPays());
	char nomBuff[255];
	strcpy(nomBuff, this->getNom());
	double longueur = (double) this->getLongueur();
	
	stream.write(paysBuff, sizeof paysBuff);
	stream.write(nomBuff, sizeof nomBuff);
	stream.write((char*) &longueur, sizeof longueur);
}

// Retourne true si le circuit a bien été chargé
bool Circuit::load(istream& stream)
{
	char buffer[255 + 255 + sizeof (double)];
	
	stream.read(buffer, sizeof buffer);
	
	if (stream.gcount() <= 0) // EOF
		return false;
	else {
		float longueur = (float) atof(buffer + 255 + 255);
			
		this->setPays(buffer);
		this->setNom(buffer + 255);
		this->setLongueur(longueur);
		
		return true;
	}
}

Circuit Circuit::operator+(const float& val) const
{
	Circuit c(this->getPays(), this->getNom(), this->longueur + val);
	return c;
}

Circuit Circuit::operator-(const float& val) const
{
	return *this + (-val);
}

Circuit Circuit::operator+(const Circuit& c2) const
{
	return *this + c2.getLongueur();
}

float Circuit::operator-(const Circuit& c2) const
{
	return this->longueur - c2.getLongueur();
}

bool Circuit::operator<(const Circuit& c2) const
{
	return this->getLongueur() < c2.getLongueur();
}

bool Circuit::operator>(const Circuit& c2) const
{
	return this->getLongueur() > c2.getLongueur();
}

Circuit Circuit::operator++()
{
	this->longueur += 0.010;
	return *this;
}

Circuit Circuit::operator++(int)
{
	Circuit pre(*this);
	this->longueur += 0.010;
	return pre;
}

ostream& operator<<(ostream& output, const Circuit& c)
{
	if (c.getPays() == NULL || c.getNom() == NULL)
		cout << "Circuit non défini" << endl;
	else {
		cout << c.getNom()
		     << " (" << c.getPays() << ") - "
		     << "Longueur : " << c.getLongueur() << "km" << endl;
	}
}

Circuit& Circuit::operator=(const Circuit& c2)
{
	this->setNom(c2.getNom());
	this->setPays(c2.getPays());
	this->setLongueur(c2.getLongueur());
	
	return *this;
}