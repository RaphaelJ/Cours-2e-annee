#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Date.h"

using namespace std;

Date Date::defaultDate = Date(01, 01, 2000);

Date::Date()
{
	this->setJour(Date::defaultDate.getJour());
	this->setMois(Date::defaultDate.getMois());
	this->setAnnee(Date::defaultDate.getAnnee());
}
Date::Date(const Date& date)
{
	*this = date;
}
Date::Date(const byte jour, const byte mois, const short annee)
{
	this->setJour(jour);
	this->setMois(mois);
	this->setAnnee(annee);
}
Date::Date(const char* date)
{
	this->setDate(date);
}

Date::~Date()
{
}

void Date::setJour(const byte jour)
{
	if (jour > 31 || jour < 1)
		throw InvalidDateException();
	this->jour = jour;
}
void Date::setMois(const byte mois)
{
	if (mois > 12 || mois < 1)
		throw InvalidDateException();
	this->mois = mois;
}
void Date::setAnnee(const short annee)
{
	this->annee = annee;
}
// Format JJ/MM/AAAA
void Date::setDate(const char* date)
{
	if (strlen(date) != 10)
		throw InvalidDateException();
	
	char workingDate[11];
	strcpy(workingDate, date);
	workingDate[2] = workingDate[5] = '\0';
	this->setJour(atoi(workingDate));
	this->setMois(atoi(workingDate + 3));
	this->setAnnee(atoi(workingDate + 6));
}

byte Date::getJour() const
{
	return this->jour;
}
byte Date::getMois() const
{
	return this->mois;
}
short Date::getAnnee() const
{
	return this->annee;
}

void Date::Affiche() const
{
	cout << *this;
}

void Date::affiche() const
{
	this->Affiche();
}

Date& Date::operator=(const Date& date2)
{
	this->setJour(date2.getJour());
	this->setMois(date2.getMois());
	this->setAnnee(date2.getAnnee());
}

ostream& operator<<(ostream& stream, const Date& date)
{
	stream << (short) date.getJour() << '/'
	       << (short) date.getMois() << '/'
	       << date.getAnnee() << endl;
	
	return stream;
}