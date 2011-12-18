#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdio.h>

#include "Element.h"
#include "LinkedFile.h"

template <typename T>
class LinkedFile;

template <typename T>
class FileIterator {
	private:
		FILE_OFFSET nextOffset; // Offset of the next element from the start of the file
		Element<T>* current;
		LinkedFile<T>* file;
		
		FileIterator();
		
		void seekNext();
	public:
		FileIterator(const FileIterator<T>& ite);
		FileIterator(LinkedFile<T>* file);
		
		~FileIterator();
		
		FILE_OFFSET getNextOffset() const;
		Element<T>* getCurrent() const;
		LinkedFile<T>* getFile() const;
		
		bool moveNext(); // return false if EOF
};

// Templates
#include "FileIterator.cpp"

#endif
