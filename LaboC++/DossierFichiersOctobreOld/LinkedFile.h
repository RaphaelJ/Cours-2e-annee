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

int stringcompare(char*& a, char*& b);

template <typename T>
bool treeNodeToStream(Tuple3<LinkedFile<T>&, ostream&, int>& acc,
                      const Tuple<char*&, IndexedElement*&> node);

bool getFreeSpace(Tuple<IndexedElement*, SIZE>& acc, /* best and last elem */
                  const Tuple<char*&, IndexedElement*&> node);

template <typename T>
class LinkedFile {
	private:
		FILE* file; // Read-only
		
		// The tree is sorted by key.
		// The tree is used for key searching and listing and
		// for free space searching.
		Tree<char*&, IndexedElement*> keysTree;
		IndexedElement* firstElem;
		
		LinkedFile();
		
		void setFile(const char* filename);
		void setFile(const FILE* file);
		void setFile(const FILE_DESC file);
		
		void seek(const long pos);
		void read(void *ptr, size_t size, size_t nmemb);
		void write(const void *ptr, size_t size, size_t nmemb);
		
		void createFile();
		
		void readHeaders(const FILE_OFFSET offset, Element<T>* elem);
		void writeHeaders(const FILE_OFFSET offset, const Element<T>* elem);
		void writeOffset(const FILE_OFFSET elem_offset, OFFSET offset);
		
		void indexLoad();
		void indexAdd(const char* key, IndexedElement* elem);
		void indexRemove(const char* key);
		void indexEdit(const char* key, const FILE_OFFSET offset,
		               const SIZE size);
		IndexedElement* indexSearch(const char* key);
		
	public:
		LinkedFile(const LinkedFile& linkedfile);
		LinkedFile(const char* filename);
		LinkedFile(const FILE_DESC file);
		~LinkedFile();
		
		FILE* getFile() const;
		
		void add(const char* key, const T* value, const short nValues);
		void edit(const char* key, const T* value, const short nValues);
		void remove(const char* key);
		Tuple<T*, short> search(const char* key);
		
		FileIterator<T>* getIterator();
		
		long getFirstElementOffset();
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
		
		class KeyExists {
		};
};

// Templates
#include "Element.cpp"
#include "FileIterator.cpp"

#endif