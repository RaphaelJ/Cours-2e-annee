#ifndef PARAMSTAT1D_H
#define PARAMSTAT1D_H

#include <iostream>
#include <list>
#include <string>
#include <math.h>

#include "Exception.h"
#include "DataSource.h"
#include "DataSourceX.h"
#include "DataX.h"

using namespace std;

class ParamStat1d {
	private:
		string nomSerie;
		
		// Remarque:
		//	Je n'ai pas utilisé de de map, car map n'est
		//	pas un type polymorphique, je ne peux donc pas
		//	placer dans le même conteneur des flottants,
		//	des entiers et une liste.
		//	Cependant, j'utilise une map dans les sources
		//	des échantillons.
		
		float moyenne;
		int mediane;
		list<int> modes;
		float ecartType;
		int etendue;
		float CV;
		
		ParamStat1d();
	public:
		ParamStat1d(const ParamStat1d& p2);
		ParamStat1d(const DataSourceX& data);
		
		~ParamStat1d();
		
		const char* getNomSerie() const;
		
		float getMoyenne() const;
		int getMediane() const;
		const list<int>& getModes() const;
		float getEcartType() const;
		int getEtendue() const;
		float getCV() const;
		
		static float calculerMoyenne(const DataSourceX& data);
		static int calculerMediane(const DataSourceX& data);
		static list<int> calculerModes(const DataSourceX& data);
		static float calculerEcartType(const DataSourceX& data, const float moyenne);
		static int calculerEtendue(const DataSourceX& data);
		static int calculerCV(const float ecartType, const float moyenne);
		
		ParamStat1d& operator=(const ParamStat1d& p2);
		
		friend ostream& operator<<(ostream& out, const ParamStat1d& p);
};

#endif