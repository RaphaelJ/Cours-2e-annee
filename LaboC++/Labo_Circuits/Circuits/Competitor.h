#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "StringProperty.h"
#include "Person.h"

#define STRINGS_SIZE 255

using namespace std;

class Competitor
	: public Person
{
	private:
		int dossard;
		int score;
		
	public:
		Competitor();
		Competitor(const Competitor& competitor);
		Competitor(const char* nom, const char* prenom, const Date dateNaissance,
		           const char* nationalite, const int dossard, const int score);
		
		~Competitor();
		
		void setDossard(const int dossard);
		void setScore(const int score);
		
		const int getDossard() const;
		const int getScore() const;
		
		const char* getIdentification() const;
		
		void save(ostream& stream) const;
		bool load(istream& stream);
		
		ostream& insert(ostream& output) const;
		Person& pull(istream& input);
		
		Competitor& operator=(const Competitor& c2);
};

#endif