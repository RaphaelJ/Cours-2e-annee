#include <iostream>
#include <string.h>

#include "LinkedFile.h"
#include "LinkedFile.cpp"

#include "Tree.h"

int intcmp(int a, int b)
{
	return a - b;
}

int scmp(char* a, char* b)
{
	return strcmp(a,b);
}

int main(int argc, char **argv)
{
	LinkedFile<char> fichier("test.txt");
	
	char *a = new char[20], 
	     *b = new char[20],
	     *c = new char[20],
	     *aVal = new char[20],
	     *bVal = new char[20],
	     *cVal = new char[20];
	     
 
	strcpy(a, "A");
	strcpy(b, "B");
	strcpy(c, "C");

	strcpy(aVal, "Hello A");
	strcpy(bVal, "Hello B");
	strcpy(cVal, "Hello C");
	
	fichier.add(a, aVal, strlen(aVal) + 1);
	fichier.add(b, bVal, strlen(bVal) + 1);
	fichier.add(c, cVal, strlen(cVal) + 1);
	
	cout << fichier;
	
// 	Tree<char*, char*> t(scmp);
// 	
// 	char *a = new char[20], 
// 	      *b = new char[20],
// 	      *c = new char[20];
// 
// 	strcpy(a, "Hello A");
// 	strcpy(b, "Hello B");
// 	strcpy(c, "Hello C");
// 	
// 	cerr << "Insert A" << endl;
// 	t.add(a, a);
// 	
// 	cerr << endl;
// 	cerr << "Insert B" << endl;
// 	t.add(b, b);
// 	
// 	cerr << endl;
// 	cerr << "Insert C" << endl;
// 	t.add(c, c);
// 	
// 	cerr << endl;
// 	cerr << "Remove A" << endl;
// 	t.remove(a);
// 	cerr << "Remove C" << endl;
// 	cerr << "Val: " << t.remove(c).e1 << endl;
// 	
// 	cerr << endl;
// 	cerr << "Insert C" << endl;
// 	t.add(c, c);
// 	
// 	t.add(a, c);
// 	
// 	cerr << "Val: " << t.remove(c).e1 << endl;
// 	
// 	cerr << "Val: " << t.remove(b).e1 << endl;
// 	t.add(b, c);
// 	t.add(c, c);
// 	
// 	cout << t.search(a).e2 << endl;
// 	cout << t.search(b).e2 << endl;
// 	cout << t.search(c).e2 << endl;
// 	
	return 0;
}
