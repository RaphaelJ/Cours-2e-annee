#ifndef ELEMENT_H
#define ELEMENT_H

#include <ostream>
#include <iostream>
#include <string.h>

#include "Types.h"
#include "IndexedElement.h"

using namespace std;

// Result of Element::decomposeSize()
struct DATA_SIZE {
	SIZE key; // String + \0 in bytes
	SIZE value; // in bytes
	SIZE padding; // in bytes
};

struct IndexedElement;

template <typename T>
struct Element;

template <typename T>
ostream& operator<<(ostream& stream, const Element<T>& elem);

template <typename T>
struct Element {
	static const SIZE headersSize = sizeof (OFFSET) + sizeof (SIZE); // in bytes
	
	// |     Headers    | key\0value |                 Padding
	// |    int   |short|    size    | (int - ((int + short + size) % int)) % int
	OFFSET offset; // Offset to the next Element
	SIZE size; // Size of datas in bytes = (len(key) + 1) * char + len(value) * T (w/o padding)
	
	char* key;
	T* value;
	
	Element();
	Element(const char* key, const T* value, short nValues);
	~Element();
	
	IndexedElement* getIndexedElement() const;
	
	// Return the sizes of the key, the data dans the padding in bytes
	DATA_SIZE decomposeSize() const; 
	
	// Total size in bytes (headers + data + padding)
	SIZE totalSize() const;
	
	inline static SIZE padding(SIZE elementSize)
	{
		return (sizeof (int) - (elementSize % sizeof (int))) % sizeof (int);
	}

	friend ostream& operator<< <>(ostream& stream, const Element<T>& elem);
};

#include "Element.cpp"

#endif
