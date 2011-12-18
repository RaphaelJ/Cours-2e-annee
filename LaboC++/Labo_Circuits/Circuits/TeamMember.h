#ifndef TEAMMEMBER_H
#define TEAMMEMBER_H

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "StringProperty.h"
#include "Person.h"
#include "AuthorizedPerson.h"

#define STRINGS_SIZE 255

using namespace std;

class TeamMember
	: public AuthorizedPerson
{
	private:
		StringProperty team;
		StringProperty function;
		
	public:
		TeamMember();
		TeamMember(const TeamMember& tm);
		TeamMember(const char* nom, const char* prenom, const Date dateNaissance,
		           const char* nationalite, const char* team, const char* function);
		
		~TeamMember();
		
		void setTeam(const char* team);
		void setFunction(const char* function);
		
		const char* getTeam() const;
		const char* getFunction() const;
		
		const char* getIdentification() const;
		
		bool Granted() const { return true; };
		
		void save(ostream& stream) const;
		bool load(istream& stream);
		
		ostream& insert(ostream& output) const;
		Person& pull(istream& input);
		
		TeamMember& operator=(const TeamMember& tm2);
};

#endif