#ifndef ECHPOSITIONDEPARTARRIVEE_H
#define ECHPOSITIONDEPARTARRIVEE_H

#include <list>
#include <map>
#include <string>

#include "Races.h"
#include "DataSourceXY.h"
#include "DataXY.h"

using namespace std;

class EchPositionDepartArrivee : public DataSourceXY {
	private:		
		EchPositionDepartArrivee();
	
	public:
		EchPositionDepartArrivee(const EchPositionDepartArrivee& e);
		EchPositionDepartArrivee(const Races& races);
		
		EchPositionDepartArrivee& operator=(const EchPositionDepartArrivee& e);
};

#endif