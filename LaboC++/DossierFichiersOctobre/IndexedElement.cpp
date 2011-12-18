#include <ostream>
#include <iostream>

#include "IndexedElement.h"

using namespace std;

IndexedElement::IndexedElement()
{
	this->inFileOffset = 0;
	this->offset = 0;
	this->size = 0;
	
	this->previous = NULL;
}
IndexedElement::IndexedElement(const IndexedElement& elem)
{
	this->inFileOffset = elem.inFileOffset;
	this->offset = elem.offset;
	this->size = elem.size;
	
	this->previous = elem.previous;
	this->next = elem.next;
}
IndexedElement::IndexedElement(const FILE_OFFSET inFileOffset, const OFFSET offset,
                               const SIZE size, IndexedElement* previous,
                               IndexedElement* next)
{
	this->inFileOffset = inFileOffset;
	this->offset = offset;
	this->size = size;
	
	this->previous = previous;
	this->next = next;
}

IndexedElement::~IndexedElement()
{
}
