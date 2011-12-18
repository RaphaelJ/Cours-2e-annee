#ifndef MYSORTEDLIST_H
#define MYSORTEDLIST_H

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ExceptionBase.h"
#include "Node.h"
#include "List.h"

using namespace std;

template <typename T>
class MySortedList : public List<T> {
	private:
		int mode;
	
	protected:
		void foo() {}; // Permet l'instanciation
	
	public:
		MySortedList();
		MySortedList(const MySortedList<T>& list);
		
		~MySortedList();
		
		static const int CROISSANT = 1;
		static const int DECROISSANT = -1;
		
		void setMode(int algo);
		int getMode() const;
		
		void insere(T item);
};

#include "MySortedList.cpp" // template's code

#endif