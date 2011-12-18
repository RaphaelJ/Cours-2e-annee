#ifndef MYLIST_H
#define MYLIST_H

#include "ExceptionBase.h"
#include "Node.h"
#include "List.h"

template <typename T>
class MyList : public List<T> {
	protected:
		void foo() {}; // Permet l'instanciation
		
	public:
		MyList();
		MyList(const MyList<T>& list);
		
		~MyList();
		
		void ajoutePremier(T item);
		void ajouteDernier(T item);
};

#include "MyList.cpp" // template's code

#endif