#ifndef MYVECTOR_CPP
#define MYVECTOR_CPP

#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "MyVector.h"

using namespace std;

template <typename T>
MyVector<T>::MyVector() // private
{
	this->vector = NULL;
}
template <typename T>
MyVector<T>::MyVector(const MyVector& vector)
{
	this->vector = NULL;
	*this = vector;
}
template <typename T>
MyVector<T>::MyVector(const int size)
{
	this->vector = NULL;
	this->initVector(size);
}

template <typename T>
MyVector<T>::~MyVector()
{
	if (this->vector != NULL)
		delete [] this->vector;
}

template <typename T>
void MyVector<T>::initVector(int size)
{
	if (size <= 0)
		throw ExceptionBase("Taille invalide");
	
	if (this->vector != NULL)
		delete [] this->vector;
	
	this->vector = new Element<T>[size];
	this->size = size;
}

template <typename T>
void MyVector<T>::setElement(const int index, T value)
{
	if (!this->indiceValide(index))
		throw InvalidIndexException();
	
	this->vector[index].setItem(value);
}
template <typename T>
T MyVector<T>::retireElement(const int index)
{
	if (!this->indiceValide(index))
		throw InvalidIndexException();
	
	this->vector[index].remove();
	return this->vector[index].getItem();
}

template <typename T>
int MyVector<T>::getSize() const
{
	return this->size;
}
template <typename T>
T MyVector<T>::getElement(const int index) const
{
	if (!this->indiceValide(index))
		throw InvalidIndexException();
	
	if (!this->estOccupe(index))
		throw NoValueException();
	
	return this->vector[index];
}

template <typename T>
bool MyVector<T>::indiceValide(const int index) const
{
	return index >= 0 && index < this->getSize();
}

template <typename T>
bool MyVector<T>::estOccupe(const int index) const
{
	if (!this->indiceValide(index))
		throw InvalidIndexException();
	
	return !this->vector[index].getFree();
}

template <typename T>
void MyVector<T>::Affiche() const
{
	cout << *this;
}
template <typename T>
void MyVector<T>::affiche() const
{
	this->Affiche();
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& v2)
{
	this.initVector(v2.getSize());
	this.size = v2.getSize();
	
	for (int i = 0; i < this->getSize(); i++) {
		try {
			this->vector[i] = v2.getElement(i);
		} catch (NoValueException e) {
			this->vector[i].free = true; // useless
		}
	}
}

template <typename T>
MyVector<T>& MyVector<T>::operator+(T value)
{
	for (int i = 0; i < this->getSize(); i++) {
		if (!this->estOccupe(i)) {
			this->setElement(i, value);
			return *this;
		}
	}
	
	throw ExceptionBase("Plus de place");
}

template <typename T>
ostream& operator<<(ostream& output, const MyVector<T>& v)
{
	for (int i = 0; i < v.getSize(); i++) {
		if (v.vector[i].getFree())
			output << "-- ";
		else
			output << v.vector[i].getItem() << ' ';
	}
	output << endl;
	
	return output;
}

#endif