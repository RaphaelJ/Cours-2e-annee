#ifndef FEDERATIONADMIN_H
#define FEDERATIONADMIN_H

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "StringProperty.h"
#include "Person.h"
#include "AuthorizedPerson.h"

#define STRINGS_SIZE 255

using namespace std;

class FederationAdmin
	: public AuthorizedPerson
{
	private:
		StringProperty competition;
		
	public:
		FederationAdmin();
		FederationAdmin(const FederationAdmin& fedadm);
		FederationAdmin(const char* nom, const char* prenom, const Date dateNaissance,
		           const char* nationalite, const char* competition);
		
		~FederationAdmin();
		
		void setCompetition(const char* competition);
		
		const char* getCompetition() const;
		
		const char* getIdentification() const;
		
		bool Granted() const { return true; };
		
		void save(ostream& stream) const;
		bool load(istream& stream);
		
		ostream& insert(ostream& output) const;
		Person& pull(istream& input);
		
		FederationAdmin& operator=(const FederationAdmin& fa2);
};

#endif