#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

#include "FichierBinaire.h"
#include "StringProperty.h"
#include "ExceptionBase.h"

using namespace std;

template <typename T>
FichierBinaire<T>::FichierBinaire() // private
{
}
template <typename T>
FichierBinaire<T>::FichierBinaire(const FichierBinaire<T>& copy) // private
{
}

template <typename T>
FichierBinaire<T>::FichierBinaire(char* chemin)
{
	this->chemin = chemin;
}

template <typename T>
FichierBinaire<T>::~FichierBinaire()
{
}

template <typename T>
FichierBinaireIterator<T> FichierBinaire<T>::getIterator()
{
	return FichierBinaireIterator<T>(this->chemin);
}

template <typename T>
void FichierBinaire<T>::save(const T& elem)
{
	ofstream stream(this->chemin, ios_base::binary | ios_base::out | ios_base::app);
	
	elem.save(stream);
	
	stream.close();
}

template <typename T>
int FichierBinaire<T>::load(T& elem, const char* nom)
{
	FichierBinaireIterator<T> ite = this->getIterator();
	
	while (!ite.end()) {
		if (strcmp((*ite).getNom(), nom) == 0) { // Nom trouvé
			elem = (*ite);
			return 0;
		}
		
		++ite;
	}
	
	return -1; // Non trouvé
}

template <typename T>
void FichierBinaire<T>::list(ostream& out)
{
	FichierBinaireIterator<T> ite = this->getIterator();
	
	while (!ite.end()) {
		out << (*ite) << endl;
	}
}

template <typename T>
FichierBinaireIterator<T>::FichierBinaireIterator() // private
{
}

template <typename T>
FichierBinaireIterator<T>::FichierBinaireIterator(const FichierBinaireIterator<T>& ite)
{
	this->stream = new ifstream(ite.getChemin(), ios_base::binary | ios_base::in);
	++(*this); // lit le premier
}

template <typename T>
FichierBinaireIterator<T>::FichierBinaireIterator(const char* chemin)
{
	this->stream = new ifstream(chemin, ios_base::binary | ios_base::in);
	++(*this); // lit le premier
}

template <typename T>
FichierBinaireIterator<T>::~FichierBinaireIterator()
{
	this->stream->close();
	delete this->stream;
}

template <typename T>
const char* FichierBinaireIterator<T>::getChemin() const
{
	return this->chemin;
}

template <typename T>
bool FichierBinaireIterator<T>::end()
{
	return this->fin;
}

template <typename T>
void FichierBinaireIterator<T>::operator++()
{
	this->fin = !(this->curr.load(*stream));
}

template <typename T>
T FichierBinaireIterator<T>::operator*()
{
	return this->curr;
}
