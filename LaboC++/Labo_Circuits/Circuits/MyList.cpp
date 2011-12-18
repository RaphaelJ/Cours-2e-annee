#ifndef MYLIST_CPP
#define MYLIST_CPP

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "MyList.h"
#include "Node.h"

using namespace std;

template <typename T>
MyList<T>::MyList()
	: List<T>::List()
{
}
template <typename T>
MyList<T>::MyList(const MyList<T>& list)
	: List<T>::List(list)
{
}

template <typename T>
MyList<T>::~MyList()
{
}

template <typename T>
void MyList<T>::ajoutePremier(T item)
{
	Node<T>* newNode = new Node<T>();
	newNode->item = item;
	newNode->next = this->first;
	
	this->first = newNode;
}

template <typename T>
void MyList<T>::ajouteDernier(T item)
{
	if (this->vide())
		this->ajoutePremier(item);
	else {
		Node<T>* curr = this->first;
		while (curr->next != NULL)
			curr = curr->next;
		
		curr->ajouterApres(item);
	}
}

#endif