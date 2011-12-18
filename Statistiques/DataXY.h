#ifndef DATAXY_H
#define DATAXY_H

struct DataXY {
	int x; // Valeur du premier paramètre
	int y; // Valeur du second paramètre
	
	DataXY()
	{
		this->x = 0;
		this->y = 0;
	}
	
	DataXY(const int x, const int y)
	{
		this->x = x;
		this->y = y;
	}
};

#endif