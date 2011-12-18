#ifndef DATAX_H
#define DATAX_H

struct DataX {
	int x; // Valeur des effectifs
	int n; // Effectif
	
	DataX()
	{
		this->x = 0;
		this->n = 0;
	}
	
	DataX(const int x, const int n)
	{
		this->x = x;
		this->n = n;
	}
	
	inline int operator<(const DataX& d) const
	{
		return this->x < d.x;
	}
	inline int operator>(const DataX& d) const
	{
		return this->x > d.x;
	}
	inline int operator==(const DataX& d) const
	{
		return this->x == d.x;
	}
};

#endif