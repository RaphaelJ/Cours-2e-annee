#ifndef RACES_H
#define RACES_H

#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "Race.h"
#include "Exception.h"

class Races
{
	private:
		list<Race> listeRaces;
		
	public:
		Races(const char* chemin);
		
		void charger(const char* chemin);
		
		const list<Race>& getListe() const;
		
		friend ostream& operator<<(ostream& out, const Races& r);
};

#endif
