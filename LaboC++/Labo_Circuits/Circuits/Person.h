#ifndef PERSON_H
#define PERSON_H

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "StringProperty.h"
#include "Date.h"

#define STRINGS_SIZE 255

using namespace std;

class Person {
	private:
		StringProperty nom;
		StringProperty prenom;
		StringProperty nationalite;
		Date dateNaissance;
		
	public:
		Person();
		Person(const Person& person);
		Person(const char* nom, const char* prenom, const Date dateNaissance,
		       const char* nationalite);
		
		~Person();
		
		void setNom(const char* nom);
		void setPrenom(const char* prenom);
		void setNationalite(const char* nationalite);
		void setDateNaissance(const Date dateNaissance);
		
		const char* getNom() const;
		const char* getPrenom() const;
		const char* getNationalite() const;
		Date getDateNaissance() const;
		
		virtual const char* getIdentification() const;
		
		void save(ostream& stream) const;
		bool load(istream& stream);
		
		virtual ostream& insert(ostream& output) const;
		virtual Person& pull(istream& input);
		
		friend ostream& operator<<(ostream& output, const Person& p);
		friend Person& operator>>(istream& input, Person& p);
		
		bool operator<=(const Person& p2) const;
		bool operator>=(const Person& p2) const;

		void Affiche() const;
		void affiche() const;
		
		Person& operator=(const Person& p2);
};

#endif