#include <iostream>
#include <stdio.h>
#include <string.h>

#include "LinkedFile.h"
#include "Tuple.h"

#define STR_SIZE 255

using namespace std;

void lireChaine(char* chaine, int longeur)
{
	if (fgets(chaine, longeur, stdin) == NULL)
		throw "Error while reading string";
	
	int len = strlen(chaine);
	
	if (chaine[len - 1] == '\n')
		chaine[len - 1] = '\0';
}

short menu()
{
	short choix;
	do {
		cout << "1. Ajouter un enregistrement" << endl;
		cout << "2. Chercher un enregistrement" << endl;
		cout << "3. Editer un enregistrement" << endl;
		cout << "4. Supprimer un enregistrement" << endl;
		cout << "5. Compacter le fichier" << endl;
		cout << "6. Vider les buffers du fichier" << endl;
		cout << "7. Lister les enregistrements" << endl;
		cout << "8. Quitter" << endl;
		
		cout << "Votre choix : ";
		cin >> choix;
		getchar();
	} while (choix < 1 && choix > 8);
	
	return choix;	
}

void ajouer(LinkedFile<char>& fichier)
{
	char *key = new char[STR_SIZE + 1],
	     *value = new char[STR_SIZE + 1];
	
	cout << "Clé : ";
	lireChaine(key, STR_SIZE);
	
	cout << "Valeur : ";
	lireChaine(value, STR_SIZE);
	
	fichier.add(key, value, strlen(value) /* remove the \0 */);
}

void chercher(LinkedFile<char>& fichier)
{
	char* key = new char[STR_SIZE + 1];
	
	cout << "Clé : ";
	lireChaine(key, STR_SIZE);
	
	Tuple<char*, short> res = fichier.search(key);
	
	for (short i = 0; i < res.e2; i++)
		cout << res.e1[i];
	
	delete res.e1;
	
	cout << endl;
}

void editer(LinkedFile<char>& fichier)
{
	char *key = new char[STR_SIZE + 1],
	     *value = new char[STR_SIZE + 1];
	
	cout << "Clé : ";
	lireChaine(key, STR_SIZE);
	
	cout << "Valeur : ";
	lireChaine(value, STR_SIZE);
	
	fichier.edit(key, value, strlen(value) /* remove the \0 */);
}

void supprimer(LinkedFile<char>& fichier)
{
	char* key = new char[STR_SIZE + 1];
	
	cout << "Clé : ";
	lireChaine(key, STR_SIZE);
	
	fichier.remove(key);
}

int main(int argc, char **argv)
{
	LinkedFile<char> fichier("test.txt");
	
	fichier.remove("Hello");
	fichier.remove("Hey");
	fichier.flush();
	
	short choix;
	do {
		choix = menu();
		
		switch (choix) {
		case 1:
			ajouer(fichier);
			break;
		case 2:
			chercher(fichier);
			break;
		case 3:
			editer(fichier);
			break;
		case 4:
			supprimer(fichier);
			break;
		case 5:
			fichier.compact();
			break;
		case 6:
			fichier.flush();
			break;
		case 7:
			cout << fichier;
		
		}
	} while (choix != 8);
	
// 	char *a = new char[20], 
// 	     *b = new char[20],
// 	     *c = new char[20],
// 	     *d = new char[20], 
// 	     *e = new char[20],
// 	     *f = new char[20],
// 	     *g = new char[20], 
// 	     *h = new char[20],
// 	     *i = new char[20],
// 	     *aVal = new char[20],
// 	     *bVal = new char[20],
// 	     *cVal = new char[255];
// 	     
//  
// 	strcpy(a, "A");
// 	strcpy(b, "B");
// 	strcpy(c, "C");
// 	strcpy(d, "D");
// 	strcpy(e, "E");
// 	strcpy(f, "F");
// 	strcpy(g, "G");
// 	strcpy(h, "H");
// 	strcpy(i, "I");
// 
// 	strcpy(aVal, "Hello A");
// 	strcpy(bVal, "HeyB");
// 	strcpy(cVal, "Salut C comment vas-tu ? Moi je vais bien mais est-ce que c'est importan?");
// 	
// 	fichier.add(a, aVal, strlen(aVal));
// //	fichier.add(b, bVal, strlen(bVal));
// 	fichier.add(c, cVal, strlen(cVal));
// //	fichier.add(d, aVal, strlen(aVal));
// 	fichier.add(e, bVal, strlen(bVal));
// 	fichier.edit(c, aVal, strlen(aVal));
// 	fichier.edit(a, cVal, strlen(cVal));
// 	
// 	Tuple<char*, short> searchval = fichier.search(a);
// 	
// 	fichier.add(f, cVal, strlen(aVal));
// 	fichier.add(g, aVal, strlen(aVal));
// 	fichier.add(h, bVal, strlen(bVal));
// 	fichier.add(i, cVal, strlen(cVal));
// 	//fichier.add(b, cVal, strlen(cVal) + 1);
// 	
// 	cout << fichier;
	
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
