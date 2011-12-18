#ifndef ECHPOSITIONDEPART_H
#define ECHPOSITIONDEPART_H

#include <algorithm>
#include <list>
#include <map>
#include <string>

#include "Races.h"
#include "DataSourceX.h"
#include "DataX.h"

using namespace std;

class EchPositionDepart : public DataSourceX {
	private:		
		EchPositionDepart();
		
	public:
		EchPositionDepart(const EchPositionDepart& e);
		EchPositionDepart(const Races& races);
		
		EchPositionDepart& operator=(const EchPositionDepart& e);
};

#endif