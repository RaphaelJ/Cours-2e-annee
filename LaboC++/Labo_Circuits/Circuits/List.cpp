#ifndef LIST_CPP
#define LIST_CPP

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "List.h"
#include "Node.h"

using namespace std;

template <typename T>
List<T>::List()
{
	this->first = NULL;
}
template <typename T>
List<T>::List(const List<T>& list)
{
	this->first = NULL;
	*this = list;
}

template <typename T>
List<T>::~List()
{
	if (this->first != NULL)
		delete this->first;
}

template <typename T>
T List<T>::retirePremier()
{
	if (!this->vide()) {
		Node<T>* oldNode = this->first;
		this->first = oldNode->next;
		
		T item = oldNode->item;
		oldNode->next = NULL; // Disable recursive delete
		delete oldNode;
		return item;
	} else {
		throw ExceptionBase("Pas de noeud à supprimer.");
	}
}

template <typename T>
T List<T>::retireDernier()
{
	if (!this->vide()) {
		Node<T>** old = &this->first;
		Node<T>* curr = this->first;
		while (curr->next != NULL) {
			old = &curr->next;
			curr = curr->next;
		}
		
		*old = NULL;
		
		T item = curr->item;
		curr->next = NULL; // Disable recursive delete
		delete curr;
		return item;
	} else {
		throw ExceptionBase("Pas de noeud à supprimer.");
	}
}

template <typename T>
bool List<T>::vide() const
{
	return this->first == NULL;
}

template <typename T>
int List<T>::size() const
{
	if (!this->vide()) {
		return this->first->size();
	} else {
		return 0;
	}
}

template <typename T>
Node<T>* List<T>::getFirstNode() const
{
	return this->first;
}

template <typename T>
ListIterator<T> List<T>::getIterator()
{
	return ListIterator<T>(*this);
}

template <typename T>
void List<T>::Affiche() const
{
	cout << *this;
}

template <typename T>
void List<T>::affiche() const
{
	this->Affiche();
}

template <typename T>
ostream& operator<<(ostream& output, const List<T>& list)
{
	if (!list.vide()) {
		return output << *list.getFirstNode(); // Recursive <<
	} else {
		return output << "Liste vide" << endl;
	}
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (list.vide() && this->first != NULL) {
		delete this->first; // recursive delete
		this->first = NULL;
	} else {
		if (this->first == NULL)
			this->first = new Node<T>();
		
		*(this->first) = *(list.getFirstNode()); // recursive copy
	}
	
	return *this;
}

template <typename T>
ListIterator<T>::ListIterator() // private
{
}

template <typename T>
ListIterator<T>::ListIterator(const ListIterator<T>& ite)
{
	*this = ite;
}

template <typename T>
ListIterator<T>::ListIterator(List<T> list)
{
	this->curr = list.getFirstNode();
}

template <typename T>
ListIterator<T>::~ListIterator()
{
}

template <typename T>
Node<T>* ListIterator<T>::getCurrentNode() const
{
	return this->curr;
}

template <typename T>
bool ListIterator<T>::end()
{
	this->curr == NULL;
}

template <typename T>
void ListIterator<T>::operator++()
{
	this->curr = this->curr->next;
}

template <typename T>
T ListIterator<T>::operator*()
{
	return this->curr->item;
}

template <typename T>
ListIterator<T>& ListIterator<T>::operator=(const ListIterator<T>& ite)
{
	this->curr = ite.getCurrentNode();
	return *this;
}

#endif