#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <string>

#include "Exception.h"

using namespace std;

class DataSource /* abstract */ {
	protected:
		string nom;
		int effectifTotal;
	
	public:
		// Nom de la source
		inline const char* getNom() const
		{
			return this->nom.c_str();
		}
		
		inline int getEffectifTotal() const
		{
			return this->effectifTotal;
		}
};

#endif
