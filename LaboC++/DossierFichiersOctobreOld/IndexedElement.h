#ifndef INDEXEDELEMENT_H
#define INDEXEDELEMENT_H

#include <ostream>
#include <iostream>

#include "Element.h"

using namespace std;

template <typename T>
struct Element;

struct IndexedElement {
	FILE_OFFSET inFileOffset;
	OFFSET offset; // Next element offset
	SIZE size; // Size of HEADERS + datas + PADDING in bytes
	
	IndexedElement* previous; // Previous element
	IndexedElement* next; // Next element
	
	IndexedElement();
	IndexedElement(const IndexedElement& elem);
	IndexedElement(const FILE_OFFSET inFileOffset, const OFFSET offset,
		       const SIZE size, IndexedElement* previous,
		       IndexedElement* next);
	
	~IndexedElement();
	
	// free space between this element and the next element
	inline SIZE freeSpace()
	{
		this->offset - this->size;
	}
};

#endif
