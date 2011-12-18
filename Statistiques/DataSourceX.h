#ifndef DATASOURCEX_H
#define DATASOURCEX_H

#include <vector>
#include <map>
#include <algorithm>

#include "Exception.h"
#include "DataSource.h"
#include "DataX.h"

using namespace std;

class DataSourceX;
ostream& operator<<(ostream& out, const DataSourceX& s);

class DataSourceX /* abstract */ : public DataSource {
	protected:
		int effectifsDistincts;
		vector<DataX> data;
	
	public:
		inline int getEffectifsDistincs() const
		{
			return this->effectifsDistincts;
		}
		
		// Donne la nème valeur
		inline DataX getData(const int i) const
		{
			if (i < 0 || i >= this->data.size())
				throw Exception("Indice invalide");
			else
				return this->data[i];
		}
		
		// Donne toutes les valeurs
		inline const vector<DataX>& getData() const
		{
			return this->data;
		}
		
		friend ostream& operator<<(ostream& out, const DataSourceX& s);
};

inline ostream& operator<<(ostream& out, const DataSourceX& s)
{
	out << "Effectif total: " << s.getEffectifTotal() << endl;
	out << "Effectifs distincts: " << s.getEffectifsDistincs() << endl;
	
	return out;
}


// Convertir une map de xi => ni en un vecteur *trié*
// de DataX
inline vector<DataX> mapToDataXVector(const map<int, int>& m)
{
	// v.clear(); // Le données seront écrasées
	vector<DataX> v(m.size());
	map<int, int>::const_iterator it;
	int index;
	for (it=m.begin(), index = 0; it!=m.end(); it++, index++) {
		// Insertion en O(1)
		v[index] = DataX(it->first, it->second);
	}
	
	// Tri en O(n * log² n)
	sort(v.begin(), v.end());
	
	return v;
}

#endif