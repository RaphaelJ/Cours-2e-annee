#ifndef FICHIERBINAIRE_H
#define FICHIERBINAIRE_H

#include <iostream>
#include <fstream>
#include <string.h>

#include "StringProperty.h"

using namespace std;

template <typename T>
class FichierBinaireIterator;

template <typename T>
class FichierBinaire {
	private:
		StringProperty chemin;
		
		FichierBinaire();
		FichierBinaire(const FichierBinaire<T>& copy);
	public:
		FichierBinaire(char* chemin);
		
		~FichierBinaire();
		
		FichierBinaireIterator<T> getIterator();
		
		void save(const T& element);
		int load(T& element, const char* nom);
		void list(ostream& out);
};

template <typename T>
class FichierBinaireIterator {
	private:
		ifstream* stream;
		StringProperty chemin;
		T curr;
		bool fin;
	
		FichierBinaireIterator();
	public:
		FichierBinaireIterator(const FichierBinaireIterator<T>& ite);
		FichierBinaireIterator(const char* chemin);
		
		~FichierBinaireIterator();
		
		bool end();
		
		const char* getChemin() const;
		
		void operator++();
		T operator*();
};

#include "FichierBinaire.cpp" // template's code

#endif