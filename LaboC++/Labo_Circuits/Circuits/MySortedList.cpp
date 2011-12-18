#ifndef MYSORTEDLIST_CPP
#define MYSORTEDLIST_CPP

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "MySortedList.h"

using namespace std;

template <typename T>
MySortedList<T>::MySortedList()
	: List<T>::List()
{
	this->mode = CROISSANT;
}
template <typename T>
MySortedList<T>::MySortedList(const MySortedList<T>& list)
	: List<T>::List(list)
{
}

template <typename T>
MySortedList<T>::~MySortedList()
{
}

template <typename T>
void MySortedList<T>::setMode(int algo)
{
	if (this->mode != algo) {
		this->mode = algo;
		
		if (!this->vide())
			this->first = this->first->retourner();
	}
}

template <typename T>
int MySortedList<T>::getMode() const
{
	return this->mode;
}

template <typename T>
void MySortedList<T>::insere(T item)
{
	if (this->vide()) {
		Node<T>* newNode = new Node<T>();
		newNode->item = item;
		newNode->next = this->first;
	
		this->first = newNode;
	} else {
		if (this->mode == CROISSANT)
			this->first = this->first->ajouterCroissant(item);
		else
			this->first = this->first->ajouterDecroissant(item);
	}
}

#endif