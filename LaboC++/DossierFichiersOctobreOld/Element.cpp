#ifndef ELEMENT_CPP
#define ELEMENT_CPP

#include <ostream>
#include <iostream>
#include <string.h>

#include "Element.h"

#include "IndexedElement.h"

using namespace std;

template <typename T>
Element<T>::Element()
{
	this->key = NULL;
	this->value = NULL;
	this->size = 0;
	this->offset = this->totalSize();
}
template <typename T>
Element<T>::Element(const char* key, const T* value, short nValues)
{
	SIZE keyLen = strlen(key);
	this->key = new char[keyLen + 1];
	strcpy(this->key, key);
	
	this->value = new T[nValues];
	memcpy(this->value, value, nValues * sizeof(T));
	
	this->size = keyLen + 1 + nValues * sizeof(T); // size in bytes
	this->offset = this->totalSize();
}
template <typename T>
Element<T>::~Element()
{
	if (this->key != NULL)
		delete [] this->key;
	
	if (this->value != NULL)
		delete [] this->value;
}

template <typename T>
IndexedElement* Element<T>::getIndexedElement() const
{
	IndexedElement* elem = new IndexedElement();
	
	elem->inFileOffset = 0;
	elem->offset = this->offset;
	elem->size = this->totalSize();
	
	elem->previous = NULL;
	elem->next = NULL;
	
	return elem;
}

template <typename T>
DATA_SIZE Element<T>::decomposeSize() const
{
	DATA_SIZE size;
	
	if (this->key == NULL) {
		size.key = 0;
		size.value = 0;
	} else {
		size.key = strlen(this->key) + 1;
		
		if (this->value == NULL)
			size.value = 0;
		else
			size.value = this->size - size.key;
	}
	
	SIZE sizeWOPadding = Element::headersSize + this->size;
	size.padding = Element<T>::padding(sizeWOPadding);
	
	return size;
}

template <typename T>
SIZE Element<T>::totalSize() const
{
	DATA_SIZE size = this->decomposeSize();
	
	return Element::headersSize
	     + size.key
	     + size.value;
	     + size.padding;
}

template <typename T>
ostream& operator<<(ostream& stream, const Element<T>& elem)
{
	DATA_SIZE size = elem.decomposeSize();
	
	stream << elem.key << '=';
	
	// Print every byte of the value
	for (short i = 0; i < size.value; i++)
		stream << elem.value[i];
	
	stream << endl;
	
	return stream;
}

#endif
