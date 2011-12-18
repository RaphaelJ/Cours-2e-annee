#ifndef LINKEDFILE_CPP
#define LINKEDFILE_CPP

#include <ostream>
#include <stdio.h>
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
	cerr << "Set file" << endl;
	
	this->file = fopen(filename, "r+");
	
	if (this->file == NULL) { // File exists
		this->file = fopen(filename, "w+");
		if (this->file == NULL)
			throw FileOpenException();
		else
			this->createFile();
	}
	
	Element<T>* firstElem = this->readElement(0);
	this->firstElem = firstElem->getIndexedElement();
	delete firstElem;
	
	this->indexLoad();
}
template <typename T>
void LinkedFile<T>::setFile(const FILE_DESC file)
{
	this->file = fopen(file, "r+");
	if (this->file == NULL) {
		throw FileOpenWithDescriptorException();
	}
	
	cerr << "Set filedesc" << endl;
	Element<T>* firstElem = this->readElement(0);
	this->firstElem = firstElem->getIndexedElement();
	delete firstElem;
	
	this->indexLoad();
}

template <typename T>
void LinkedFile<T>::seek(const long pos)
{
	cerr << "Seek : "  << pos << endl;
	if (fseek(this->file, pos, SEEK_SET) != 0)
		throw SeekException();
}

template <typename T>
void LinkedFile<T>::read(void *ptr, size_t size, size_t nmemb)
{
	cerr << "Read size : " << size << " nmemb: " << nmemb << endl;
	if (fread(ptr, size, nmemb, this->file) != nmemb)
		throw ReadingException();
}

template <typename T>
void LinkedFile<T>::write(const void *ptr, size_t size, size_t nmemb)
{
	cerr << "Write size : " << size << " nmemb: " << nmemb << endl;
	if (fwrite(ptr, size, nmemb, this->file) != nmemb)
		throw WritingException();
}

// Initialise the file for writing
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
void LinkedFile<T>::readHeaders(const FILE_OFFSET offset, Element<T>* elem)
{
	this->seek(offset);
	
	cerr << "Read headers" << endl;
	this->read(elem, Element<T>::headersSize, 1);
}

template <typename T>
void LinkedFile<T>::writeHeaders(const FILE_OFFSET offset, const Element<T>* elem)
{
	cerr << "Write headers" << endl;
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
	
	cerr << "Call move next" << endl;
	ite->moveNext();
	cerr << "Called move next" << endl;
	
	while (ite->moveNext()) {
		Element<T>* current = ite->getCurrent();
		
		IndexedElement* elem
			= new IndexedElement(inFileOffset, current->offset,
					     current->size, lastElem, NULL);
	
		// List
		lastElem->next = elem;
		lastElem = elem;
		
		this->indexAdd(current->key, elem);
		
		inFileOffset = ite->getNextOffset();
	}
	
	
		cerr << "ok" << endl;
	
	delete ite;
}

template <typename T>
void LinkedFile<T>::indexAdd(const char* key, IndexedElement* elem)
{
	char* keyCpy = new char[strlen(key) + 1];
	strcpy(keyCpy, key);
	
	cerr << "index Add " << key << endl;
	cerr << *this << endl;
	
	this->keysTree.add(keyCpy, elem);
}

template <typename T>
void LinkedFile<T>::indexRemove(const char* key)
{
	Tuple<char*, IndexedElement*> t = this->keysTree.remove(key);
	
	t.e2->previous->next = t.e2->next;
	
	delete t.e1;
	delete t.e2;
}

template <typename T>
void LinkedFile<T>::indexEdit(const char* key, const FILE_OFFSET offset,
                              const SIZE size)
{
	Tuple<char*, IndexedElement*> t = this->indexSearch(key);
	
	t.e2->offset = offset;
	t.e2->size = size;
}

template <typename T>
IndexedElement* LinkedFile<T>::indexSearch(const char* key)
{
	return this->keysTree.search(key).e2;
}

template <typename T>
FILE* LinkedFile<T>::getFile() const
{
	return this->file;
}

bool getFreeSpace(Tuple<IndexedElement*, SIZE>& acc, /* best elem */
                  const Tuple<char*&, IndexedElement*&> node)
{
	IndexedElement *&best = acc.e1,
		       *current = node.e2;
	SIZE spaceNeeded = acc.e2;
	
	if (current->freeSpace() == spaceNeeded) { // if just fit, stop folding
		best = current;
		
		return false; // Stop folding
	} else if (current->freeSpace() >= spaceNeeded) {
		if (best == NULL || current->freeSpace() < best->freeSpace())
			best = current;
	} else if (current->next == NULL) { // Last
		best = current;
	}
	
	return true; // continue folding
}

template <typename T>
void LinkedFile<T>::add(const char* key, const T* value, const short nValues)
{
	cerr << "Add " << key << endl;
	
	Element<T> elem(key, value, nValues);
	
	IndexedElement *indexElem = elem.getIndexedElement();
	
	IndexedElement *bestFree = this->firstElem;
	
	// Fetch the tree for the best place to insert for SIZE
	typedef Tuple<IndexedElement*, SIZE> ACC_TUPLE;
	ACC_TUPLE tuple(bestFree, indexElem->size);
	
	this->keysTree.fold(getFreeSpace, tuple);
	bestFree = tuple.e1;
	
	// Create entry in index (and check for duplicate key)
	this->indexAdd(key, indexElem); // no copy of indexElem, same struct

	indexElem->inFileOffset = bestFree->inFileOffset + bestFree->size;
	if (bestFree->next != NULL) { // Re-use free space
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
void LinkedFile<T>::edit(const char* key, const T* value, const short nValues)
{
	this->remove(key);
	this->add(key, value, nValues);
}

template <typename T>
void LinkedFile<T>::remove(const char* key)
{
	IndexedElement* indexElem = this->indexSearch(key);
	cerr << "Remove" << endl;
	Element<T>* elem = this->readElement(indexElem->inFileOffset);
	
	indexElem->previous->offset += indexElem->offset;
	this->writeOffset(indexElem->previous->inFileOffset,
	                  indexElem->previous->offset);
	
	// Remove index
	this->indexRemove(key); 
}

template <typename T>
Tuple<T*, short> LinkedFile<T>::search(const char* key)
{
	cerr << "Search" << endl;
	IndexedElement* indexElem = this->indexSearch(key);
	Element<T>* elem = this->readElement(indexElem->inFileOffset);
	
	T* data = elem->data;
	short nValues = elem->decomposeSize().value / sizeof (T);
	
	elem->data = NULL; // don't delete data
	delete elem;
	
	Tuple<T*, short> tuple(data, nValues);
	return tuple;
}

template <typename T>
FileIterator<T>* LinkedFile<T>::getIterator()
{
	return new FileIterator<T>(this);
}

template <typename T>
long LinkedFile<T>::getFirstElementOffset()
{
	cerr << "Read first element offset " << endl;
	
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
	cerr << "Read element" << endl;
	
	Element<T>* elem = new Element<T>;
	
	// Read headers
	try {
		this->readHeaders(offset, elem);
	} catch (ReadingException) {
		delete elem;
		
		return NULL; // EOF
	}
	
	cerr << "headers: offset : " << elem->offset << " size : " << elem->size << endl; 
	
	if (elem->size > 0) {
		// Read data
		char* dataBuffer = new char[elem->size];
		cerr << "Read element" << endl;
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
	cerr << "Write element" << endl;

	// Write headers
	this->writeHeaders(offset, elem);
	
	if (elem->size > 0) {
		cerr << "Write key" << endl;
		// Write key
		short keyLen = strlen(elem->key);
		this->write(elem->key, 1, keyLen + 1 /* key + \0 */);
		
		// Write value
		cerr << "Write val" << endl;
		short valueLen = elem->size - (keyLen + 1);
		this->write(elem->value, sizeof (T), valueLen / sizeof(T));
	}
}

template <typename T>
bool treeNodeToStream(Tuple3<LinkedFile<T>&, ostream&, int>& acc,
                      const Tuple<char*&, IndexedElement*&> node)
{
	// Read elem in file
	cerr << "Tree node " << endl;
	Element<T> *elem = acc.e1.readElement(node.e2->inFileOffset);
	
	// Write into stream
	acc.e2 << *elem << endl;
	
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

int stringcompare(char*& a, char*& b)
{
	return strcmp(a,b);
}

#endif