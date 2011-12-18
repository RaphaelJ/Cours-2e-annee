#ifndef CIRCUIT_H
#define CIRCUIT_H

#include<iostream>

#include "StringProperty.h"

using namespace std;

class Circuit {
	private:
		StringProperty pays;
		StringProperty nom;
		float longueur;
		
	public:
		Circuit();
		Circuit(const Circuit& circuit);
		Circuit(const char* pays, const char* nom, const float longueur);
		
		~Circuit();
		
		static Circuit SPA_FRANCORCHAMPS;
		static Circuit SILVERSTONE;
		
		void setPays(const char* pays);
		void setNom(const char* nom);
		void setLongueur(const float longueur);
		
		const char* getPays() const;
		const char* getNom() const;
		float getLongueur() const;

		void Affiche() const;
		void affiche() const;
		
		void save(ostream& stream) const;
		bool load(istream& stream);
		
		Circuit operator+(const float& val) const;
		Circuit operator-(const float& val) const;
		
		Circuit operator+(const Circuit& c2) const;
		float operator-(const Circuit& c2) const;
		
		bool operator<(const Circuit& c2) const;
		bool operator>(const Circuit& c2) const;
		
		Circuit operator++();
		Circuit operator++(int); // Post
		
		friend ostream& operator<<(ostream& output, const Circuit& c);
		
		Circuit& operator=(const Circuit& c2);
};

#endif