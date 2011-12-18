#ifndef LIST_H
#define LIST_H

#include "ExceptionBase.h"
#include "Node.h"

template <typename T>
class List;

template <typename T>
class ListIterator;

template <typename T>
ostream& operator<<(ostream& stream, const List<T>& list);

template <typename T>
class /* abstract */ List {
	protected:
		Node<T>* first;
		
// 		virtual void foo() = 0; // Empêche l'instanciation
	public:
		List();
		List(const List<T>& list);
		
		~List();
		
		T retirePremier();
		T retireDernier();
		
		bool vide() const;
		int size() const;
		
		Node<T>* getFirstNode() const;
		ListIterator<T> getIterator();

		void Affiche() const;
		void affiche() const;
		
		List<T>& operator=(const List<T>& list);
		
		friend ostream& operator<< <>(ostream& output, const List<T>& list);
};

template <typename T>
class ListIterator {
	private:
		Node<T>* curr;
	
		ListIterator();
	public:
		ListIterator(const ListIterator<T>& ite);
		ListIterator(List<T> list);
		
		~ListIterator();
		
		Node<T>* getCurrentNode() const;
		
		bool end();
		
		void operator++();
		T operator*();
		
		ListIterator<T>& operator=(const ListIterator<T>& ite);
};

#include "List.cpp" // template's code

#endif