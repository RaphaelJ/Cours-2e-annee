#ifndef PARAMSTAT2D_H
#define PARAMSTAT2D_H

#include <iostream>
#include <list>
#include <string>
#include <math.h>

#include "Exception.h"
#include "DataSource.h"
#include "DataSourceXY.h"
#include "DataXY.h"

using namespace std;

class ParamStat2d {
	private:
		string nomSerie;
		
		float moyenneX;
		float moyenneY;
		float ecartTypeX;
		float ecartTypeY;
		int etendueX;
		int etendueY;
		float correlationLineaire;
		float regressionA;
		float regressionB;
		
		ParamStat2d();
	public:
		ParamStat2d(const ParamStat2d& p2);
		ParamStat2d(const DataSourceXY& data);
		
		~ParamStat2d();
		
		const char* getNomSerie() const;
		
		float getMoyenneX() const;
		float getMoyenneY() const;
		float getEcartTypeX() const;
		float getEcartTypeY() const;
		int getEtendueX() const;
		int getEtendueY() const;
		float getCorrelationLineaire() const;
		float getRegressionA() const;
		float getRegressionB() const;
		
		static float calculerMoyenneX(const DataSourceXY& data);
		static float calculerMoyenneY(const DataSourceXY& data);
		static float calculerEcartTypeX(const DataSourceXY& data, const float moyenneX);
		static float calculerEcartTypeY(const DataSourceXY& data, const float moyenneY);
		static int calculerEtendueX(const DataSourceXY& data);
		static int calculerEtendueY(const DataSourceXY& data);
		static float calculerCorrelationLineaire(const DataSourceXY& data, const float moyenneX,
				                         const float moyenneY);
		static float calculerRegressionA(const DataSourceXY& data, const float moyenneX,
		                                 const float moyenneY);
		static float calculerRegressionB(const DataSourceXY& data, const float moyenneX,
		                                 const float moyenneY, const float regressionA);
		
		ParamStat2d& operator=(const ParamStat2d& p2);
		
		friend ostream& operator<<(ostream& out, const ParamStat2d& p);
};

#endif