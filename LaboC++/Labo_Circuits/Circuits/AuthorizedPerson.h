#ifndef AUTHORIZEDPERSON_H
#define AUTHORIZEDPERSON_H

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "StringProperty.h"
#include "Person.h"

using namespace std;

/* abstract */ class AuthorizedPerson
	: public Person
{
	protected:
		StringProperty login;
		
	public:
		AuthorizedPerson() { }
		AuthorizedPerson(const AuthorizedPerson& p) : Person() { }
		AuthorizedPerson(const char* nom, const char* prenom, const Date dateNaissance,
		       const char* nationalite)
		      : Person(nom, prenom, dateNaissance, nationalite) { }
		
		~AuthorizedPerson() { }
		
		void setLogin(const char* login) { this->login = login; }
		
		const char* getLogin() const { return this->login; }
		
		virtual bool Granted() const = 0;
		
		void save(ostream& stream) const
		{
			Person::save(stream);
			
			char loginBuff[255];
			strcpy(loginBuff, this->getLogin());
	
			stream.write(loginBuff, sizeof loginBuff);
		}
		
		bool load(istream& stream)
		{
			if (Person::load(stream)) {
				char buffer[255];
	
				stream.read(buffer, sizeof buffer);
	
				this->setLogin(buffer);
			} else
				return false;
		}
};

#endif