#ifndef LINKEDFILE_H
#define LINKEDFILE_H

#include <ostream>
#include <stdio.h>
#include <string.h>

#include "Tuple.h"
#include "Element.h"
#include "IndexedElement.h"
#include "Tree.h"
#include "FileIterator.h"

typedef int FILE_DESC;

template <typename T>
class FileIterator;

template <typename T>
class LinkedFile;

template <typename T>
ostream& operator<<(ostream& stream, LinkedFile<T>& file);
// http://stackoverflow.com/questions/1297609/overloading-friend-operator-for-template-class

int stringcompare(char* a, char* b);

// Fecth all the tree's node of the tree into an ostream
template <typename T>
bool treeNodeToStream(Tuple3<LinkedFile<T>&, ostream&, int>& acc,
                      const Tuple<char*&, IndexedElement*&> node);

// Fetch all the tree's node for the best place to insert
bool getFreeSpace(Tuple<IndexedElement*, SIZE>& acc, /* best and last elem */
                  const Tuple<char*&, IndexedElement*&> node);

template <typename T>
class LinkedFile {
	private:
		FILE* file; // Read-only
		
		// The tree is sorted by key.
		// The tree is used for key searching and listing and
		// for free space searching.
		Tree<char*, IndexedElement*> keysTree;
		IndexedElement* firstElem;
		
		LinkedFile();
		
		void openFile(); // Read the first elem and load the index
		void createFile(); // Write the first ghost element into a new file
		
		void setFile(const char* filename);
		void setFile(const FILE_DESC file);
		
		void seek(const long pos);
		void read(void *ptr, size_t size, size_t nmemb);
		void write(const void *ptr, size_t size, size_t nmemb);
		
		void readHeaders(const FILE_OFFSET offset, Element<T>* elem);
		void writeHeaders(const FILE_OFFSET offset, const Element<T>* elem);
		void writeOffset(const FILE_OFFSET elem_offset, OFFSET offset);
		
		void indexLoad(); // Load all entries of the file in the tree
		void indexAdd(const char* key, IndexedElement* elem);
		void indexRemove(char* const key);
		void indexEdit(char* const key, const FILE_OFFSET offset,
		               const SIZE size);
		IndexedElement* indexSearch(char* const key);
		
		void compactRec(IndexedElement* currentElem, SIZE freeSpaceBefore);
		
	public:
		LinkedFile(const LinkedFile& linkedfile);
		LinkedFile(const char* filename);
		LinkedFile(const FILE_DESC file);
		~LinkedFile();
		
		FILE* getFile() const;
		
		void add(const char* key, const T* value, const short nValues);
		void edit(char* const key, const T* value, const short nValues);
		void remove(char* const key);
		// Return a tuple of the value and its size
		Tuple<T*, short> search(char* const key);
		void compact();
		
		void flush();
		
		FileIterator<T>* getIterator();
		
		FILE_OFFSET getFirstElementOffset(); // Get the offset
		Element<T>* readElement(const FILE_OFFSET offset);
		void writeElement(const FILE_OFFSET offset, const Element<T>* elem);

		friend ostream& operator<< <>(ostream& stream, LinkedFile<T>& file);
		
		// Exceptions
		class FileOpenException {
		};
		class FileOpenWithDescriptorException {
		};
		class ReadFirstElementOffsetException {
		};
		class SeekException {
		};
		class ReadingException {
		};
		class WritingException {
		};
};

// Templates
#include "LinkedFile.cpp"

#endif