#ifndef FILEITERATOR_CPP
#define FILEITERATOR_CPP

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "FileIterator.h"

#include "Element.h"
#include "LinkedFile.h"

using namespace std;

template <typename T>
FileIterator<T>::FileIterator()
{
	this->file = NULL;
	this->current = NULL;
	this->nextOffset = 0;
}
template <typename T>
FileIterator<T>::FileIterator(const FileIterator& ite)
{
	this->file = ite.getFile();
	this->current = ite.getCurrent();
	this->nextOffset = ite.getNextOffset();
}
template <typename T>
FileIterator<T>::FileIterator(LinkedFile<T>* file)
{
	this->file = file;
	this->current = NULL;
	
	this->nextOffset = this->file->getFirstElementOffset();
}

template <typename T>
FileIterator<T>::~FileIterator()
{
	if (this->current != NULL)
		delete this->current;
}

template <typename T>
FILE_OFFSET FileIterator<T>::getNextOffset() const
{
	return this->nextOffset;
}

template <typename T>
Element<T>* FileIterator<T>::getCurrent() const
{
	return this->current;
}

template <typename T>
bool FileIterator<T>::moveNext() // return false if EOF
{
	if (this->current != NULL)
		delete this->current;
	
	this->current = this->file->readElement(this->nextOffset);
	
	if (this->current != NULL) {
		this->nextOffset += this->current->offset;
		return true;
	} else {
		return false;
	}
}

#endif