#ifndef LINKEDFILE_CPP
#define LINKEDFILE_CPP

#include <ostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedFile.h"

#include "Tuple.h"
#include "Element.h"
#include "IndexedElement.h"
#include "Tree.h"
#include "FileIterator.h"

using namespace std;

template <typename T>
LinkedFile<T>::LinkedFile() // private
	: keysTree(stringcompare)
{
	this->firstElem = NULL;
}
template <typename T>
LinkedFile<T>::LinkedFile(const LinkedFile<T>& linkedfile)
	: keysTree(stringcompare)
{
	this->firstElem = NULL;
	
	this->setFile(linkedfile.getFile());
}
template <typename T>
LinkedFile<T>::LinkedFile(const char* filename)
	: keysTree(stringcompare)
{
	this->firstElem = NULL;
	
	this->setFile(filename);
}
template <typename T>
LinkedFile<T>::LinkedFile(const FILE_DESC file)
	: keysTree(stringcompare)
{
	this->firstElem = NULL;
	
	this->setFile(file);
}

template <typename T>
LinkedFile<T>::~LinkedFile()
{
	if (this->firstElem != NULL)
		delete this->firstElem;
	
	fclose(this->file);
}

template <typename T>
void LinkedFile<T>::setFile(const char* filename)
{
	this->file = fopen(filename, "r+");
	
	if (this->file == NULL) { // File exists
		this->file = fopen(filename, "w+");
		if (this->file == NULL)
			throw FileOpenException();
		else
			this->createFile();
	}
	
	this->openFile();
}
template <typename T>
void LinkedFile<T>::setFile(const FILE_DESC file)
{
	this->file = fopen(file, "r+");
	if (this->file == NULL) {
		throw FileOpenWithDescriptorException();
	}
	
	this->openFile();
}

template <typename T>
void LinkedFile<T>::openFile()
{
	Element<T>* firstElem = this->readElement(0);
	this->firstElem = firstElem->getIndexedElement();
	delete firstElem;
	
	this->indexLoad();
}

template <typename T>
void LinkedFile<T>::createFile()
{
	Element<T> firstElem;
	firstElem.size = 0;
	firstElem.key = NULL;
	firstElem.value = NULL;
	firstElem.offset = firstElem.totalSize();

	this->writeElement(0, &firstElem);
}

template <typename T>
void LinkedFile<T>::seek(const long pos)
{
	if (fseek(this->file, pos, SEEK_SET) != 0)
		throw SeekException();
}

template <typename T>
void LinkedFile<T>::read(void *ptr, size_t size, size_t nmemb)
{
	if (fread(ptr, size, nmemb, this->file) != nmemb)
		throw ReadingException();
}

template <typename T>
void LinkedFile<T>::write(const void *ptr, size_t size, size_t nmemb)
{
	if (fwrite(ptr, size, nmemb, this->file) != nmemb)
		throw WritingException();
}

template <typename T>
void LinkedFile<T>::flush()
{
	fflush(this->file);
}

template <typename T>
void LinkedFile<T>::readHeaders(const FILE_OFFSET offset, Element<T>* elem)
{
	this->seek(offset);
	
	this->read(elem, Element<T>::headersSize, 1);
}

template <typename T>
void LinkedFile<T>::writeHeaders(const FILE_OFFSET offset, const Element<T>* elem)
{
	this->seek(offset);
	
	this->write(elem, Element<T>::headersSize, 1);
}

template <typename T>
void LinkedFile<T>::writeOffset(const FILE_OFFSET elem_offset, OFFSET offset)
{
	this->seek(elem_offset);
	
	this->write(&offset, sizeof (OFFSET), 1);
}

template <typename T>
void LinkedFile<T>::indexLoad()
{
	FileIterator<T>* ite = this->getIterator();
	
	FILE_OFFSET inFileOffset = ite->getNextOffset();
	
	IndexedElement* lastElem = this->firstElem;
	
	while (ite->moveNext()) {
		Element<T>* current = ite->getCurrent();
		
		IndexedElement* elem = current->getIndexedElement();
		elem->inFileOffset = inFileOffset;
		elem->previous = lastElem;
		elem->next = NULL;
		
		// List
		lastElem->next = elem;
		lastElem = elem;
		
		this->indexAdd(current->key, elem);
		
		inFileOffset = ite->getNextOffset();
	}
	
	delete ite;
}

template <typename T>
void LinkedFile<T>::indexAdd(const char* key, IndexedElement* elem)
{
	char* keyCpy = new char[strlen(key) + 1];
	strcpy(keyCpy, key);
	
	this->keysTree.add(keyCpy, elem);
}

template <typename T>
void LinkedFile<T>::indexRemove(char* const key)
{
	Tuple<char*, IndexedElement*> t = this->keysTree.remove(key);
	
	t.e2->previous->next = t.e2->next;
	t.e2->next->previous = t.e2->previous;
	
	delete t.e1;
	delete t.e2;
}

template <typename T>
void LinkedFile<T>::indexEdit(char* const key, const FILE_OFFSET offset,
                              const SIZE size)
{
	Tuple<char*, IndexedElement*> t = this->indexSearch(key);
	
	t.e2->offset = offset;
	t.e2->size = size;
}

template <typename T>
IndexedElement* LinkedFile<T>::indexSearch(char* const key)
{
	return this->keysTree.search(key).e2;
}

template <typename T>
FILE* LinkedFile<T>::getFile() const
{
	return this->file;
}

bool getFreeSpace(Tuple<IndexedElement*, SIZE>& acc, /* best elem and requested SIZE */
                  const Tuple<char*&, IndexedElement*&> node)
{
	IndexedElement *&best = acc.e1,
	               *current = node.e2;
	SIZE spaceNeeded = acc.e2,
	     currentFreeSpace = current->freeSpace();
	
	if (currentFreeSpace == spaceNeeded) { // if just fit, stop folding
		best = current;
		
		return false; // Stop folding
	} else {
		if (currentFreeSpace > spaceNeeded) {
			if (best == NULL /* first */
			    || best->freeSpace() == 0 /* last */
			    || currentFreeSpace < best->freeSpace() /* best place */)
				best = current;
		} else if (best == NULL && current->next == NULL) // Last (only if no fit space found)
			best = current;
		
		return true; // continue folding
	}
}

template <typename T>
void LinkedFile<T>::add(const char* key, const T* value, const short nValues)
{
	Element<T> elem(key, value, nValues); // Copy key & value
	
	IndexedElement *indexElem = elem.getIndexedElement();
	
	IndexedElement *bestFree = NULL;
	
	// Fetch the tree for the best place to insert for SIZE
	typedef Tuple<IndexedElement*, SIZE> ACC_TUPLE;
	ACC_TUPLE tuple(bestFree, indexElem->size);
	
	this->keysTree.fold(getFreeSpace, tuple);
	bestFree = tuple.e1;
	
	if (bestFree == NULL) // First elem
		bestFree = this->firstElem;
	
	// Create an index entry (and check for duplicate key)
	this->indexAdd(key, indexElem); // copy the key, doesn't copy indexElem

	indexElem->inFileOffset = bestFree->inFileOffset + bestFree->size;
	if (bestFree->size < bestFree->offset) { // Re-use free space
		indexElem->offset = elem.offset = bestFree->offset - bestFree->size;
		
		// Update offset of previous element
		bestFree->offset = bestFree->size; // in index
		this->writeOffset(bestFree->inFileOffset, bestFree->offset); // in file
	} else // Write at the end of the file
		indexElem->offset = elem.offset = indexElem->size;
	
	// Update list
	indexElem->next = bestFree->next;
	indexElem->previous = bestFree;
	bestFree->next = indexElem;
	
	// Write new element in file
	this->writeElement(indexElem->inFileOffset, &elem);
}

template <typename T>
void LinkedFile<T>::edit(char* key, const T* value, const short nValues)
{
	IndexedElement* indexElem = this->indexSearch(key);
	Element<T> elem(key, value, nValues);
	SIZE freeSpace = indexElem->offset;
	
	if (freeSpace >= elem.totalSize()) { // Edit and use the free space
		indexElem->size = elem.totalSize();
		elem.offset = indexElem->offset;
		this->writeElement(indexElem->inFileOffset, &elem);
	} else { // Remove at the current place and add somewhere else
		this->remove(key);
		this->add(key, value, nValues);
	}
}

template <typename T>
void LinkedFile<T>::remove(char* const key)
{
	IndexedElement* indexElem = this->indexSearch(key);
	Element<T>* elem = this->readElement(indexElem->inFileOffset);
	
	indexElem->previous->offset += indexElem->offset;
	this->writeOffset(indexElem->previous->inFileOffset,
	                  indexElem->previous->offset);
	
	// Remove index
	this->indexRemove(key); 
}

template <typename T>
Tuple<T*, short> LinkedFile<T>::search(char* const key)
{
	IndexedElement* indexElem = this->indexSearch(key);
	Element<T>* elem = this->readElement(indexElem->inFileOffset);
	
	T* value = elem->value;
	short nValues = elem->decomposeSize().value / sizeof (T);
	
	elem->value = NULL; // don't delete data
	delete elem;
	
	Tuple<T*, short> tuple(value, nValues);
	return tuple;
}

template <typename T>
void LinkedFile<T>::compactRec(IndexedElement* currentElem, SIZE freeSpaceBefore)
{
	if (currentElem != NULL) {
		SIZE freeSpace = currentElem->freeSpace();
		if (freeSpaceBefore > 0) { // left shift
			Element<T>* elem = this->readElement(currentElem->inFileOffset);
			
			currentElem->inFileOffset
				= currentElem->inFileOffset - freeSpaceBefore;
			
			if (currentElem->next != NULL)
				currentElem->offset = elem->offset = currentElem->size;
			else { // point to the end of file for the last
				currentElem->offset = elem->offset
					= currentElem->offset + freeSpaceBefore;
			}
			
			cerr << "offset: " << elem->offset<< endl;
			
			this->writeElement(currentElem->inFileOffset, elem);
			
			delete elem;
		} else if (freeSpace > 0 // change offset of first space
		           && currentElem->next != NULL) {
			currentElem->offset = currentElem->size;
			cerr << currentElem->offset << " " << 
			  currentElem->inFileOffset << endl;
			this->writeOffset(currentElem->inFileOffset, currentElem->offset);
		}
		
		this->compactRec(currentElem->next, freeSpaceBefore + freeSpace);
	}
}

template <typename T>
void LinkedFile<T>::compact()
{
	this->compactRec(this->firstElem, 0);
}

template <typename T>
FileIterator<T>* LinkedFile<T>::getIterator()
{
	return new FileIterator<T>(this);
}

template <typename T>
long LinkedFile<T>::getFirstElementOffset()
{	
	Element<T> elem;
	
	try {
		this->readHeaders(0, &elem);
	} catch (ReadingException) {
		throw ReadFirstElementOffsetException();
	}
	
	return elem.offset;
}

template <typename T>
Element<T>* LinkedFile<T>::readElement(const FILE_OFFSET offset)
{	
	Element<T>* elem = new Element<T>;
	
	// Read headers
	try {
		this->readHeaders(offset, elem);
	} catch (ReadingException) {
		delete elem;
		
		return NULL; // EOF
	}
	
	if (elem->size > 0) {
		// Read data
		char* dataBuffer = new char[elem->size];
		this->read(dataBuffer, 1, elem->size);

		// Copy data into the Element structure
		short keyLen = strlen(dataBuffer);
		//short keyLen = 0;
		//while (dataBuffer[keyLen] != '=')
		//	keyLen += 1;
		short valueLen = elem->size - (keyLen + 1);
		
		// Copy the key
		dataBuffer[keyLen] = '\0';
		
		elem->key = new char[keyLen + 1];
		strcpy(elem->key, dataBuffer);
		
		// Copy the value
		T* pValue = (T*) (dataBuffer + keyLen + 1);
		elem->value = new T[valueLen / sizeof (T)];
		for (short i = 0; i < valueLen; i++)
			elem->value[i] = pValue[i];
		
		delete [] dataBuffer;
	} else { // First elem
		elem->key = NULL;
		elem->value = NULL;
	}
	
	return elem;
}

template <typename T>
void LinkedFile<T>::writeElement(const FILE_OFFSET offset, const Element<T>* elem)
{
	// Write headers
	this->writeHeaders(offset, elem);
	
	if (elem->size > 0) {
		// Write key
		short keyLen = strlen(elem->key);
		this->write(elem->key, 1, keyLen + 1 /* key + \0 */);
		
		// Write value
		short valueLen = elem->size - (keyLen + 1);
		this->write(elem->value, sizeof (T), valueLen / sizeof(T));
	}
}

template <typename T>
bool treeNodeToStream(Tuple3<LinkedFile<T>&, ostream&, int>& acc,
                      const Tuple<char*&, IndexedElement*&> node)
{
	acc.e2 << "In file offset : " << node.e2->inFileOffset << '\t'
	       << "Total size : " << node.e2->size << '\t'
	       << "Offset : " << node.e2->offset << endl;
	
	// Read elem data in file
	Element<T> *elem = acc.e1.readElement(node.e2->inFileOffset);
	
	// Write data into stream
	acc.e2 << *elem;
	
	delete elem;
	
	acc.e3 += 1; // nElems
	
	return true; // fetch all tree's nodes
}

template <typename T>
ostream& operator<<(ostream& stream, LinkedFile<T>& file)
{
	// Create a tuple as an accumulator for the tree
	// folding.
	// The folding fct will read the node data in the file,
	// put theses on the stream and increment int by one
	typedef Tuple3<LinkedFile<T>&, ostream&, int> ACC_TUPLE;
	ACC_TUPLE tuple(file, stream, 0);
	
	file.keysTree.fold(treeNodeToStream<T>, tuple);
	
	stream << "Records count : "
	       << tuple.e3
	       << endl;
	
	return stream;
}

// Functions

int stringcompare(char* const a, char* const b)
{
	return strcmp(a, b);
}

#endif