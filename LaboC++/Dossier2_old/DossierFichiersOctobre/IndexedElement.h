#ifndef INDEXEDELEMENT_H
#define INDEXEDELEMENT_H

#include <ostream>
#include <iostream>

#include "Types.h"

using namespace std;

struct IndexedElement {
	FILE_OFFSET inFileOffset; // Absolut offset
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
		return this->offset - this->size;
	}
};

//#include "IndexedElement.cpp" // Template

#endif
