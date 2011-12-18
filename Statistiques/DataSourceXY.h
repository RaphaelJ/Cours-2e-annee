#ifndef DATASOURCEXY_H
#define DATASOURCEXY_H

#include <vector>

#include "Exception.h"
#include "DataSource.h"
#include "DataXY.h"

using namespace std;

class DataSourceXY;
ostream& operator<<(ostream& out, const DataSourceXY& s);

class DataSourceXY /* abstract */ : public DataSource {
	protected:
		vector<DataXY> data;
	
	public:
		// Donne la nème valeur
		inline DataXY getDataXY(const int i) const
		{
			if (i < 0 || i >= this->data.size())
				throw Exception("Indice invalide");
			else
				return this->data[i];
		}
		
		// Donne la nème valeur du premier paramètre
		inline int getDataX(const int i) const
		{
			return this->getDataXY(i).x;
		}
		
		// Donne la nème valeur du second paramètre
		inline int getDataY(const int i) const
		{
			return this->getDataXY(i).y;
		}
		
		// Donne toutes les valeurs
		inline const vector<DataXY>& getData() const
		{
			return this->data;
		}
		
		friend ostream& operator<<(ostream& out, const DataSourceXY& s);
};

inline ostream& operator<<(ostream& out, const DataSourceXY& s)
{
	out << "Effectif total: " << s.getEffectifTotal() << endl;
	
	return out;
}

#endif