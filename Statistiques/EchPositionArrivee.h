#ifndef ECHPOSITIONARRIVEE_H
#define ECHPOSITIONARRIVEE_H

#include <algorithm>
#include <list>
#include <map>
#include <string>

#include "Races.h"
#include "DataSourceX.h"
#include "DataX.h"

using namespace std;

class EchPositionArrivee : public DataSourceX {
	private:		
		EchPositionArrivee();
		
	public:
		EchPositionArrivee(const EchPositionArrivee& e);
		EchPositionArrivee(const Races& races);
		
		EchPositionArrivee& operator=(const EchPositionArrivee& e);
};

#endif