#ifndef RACE_H
#define RACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

using namespace std;

#define AB -1
#define DSQ -2

class Race
{
	private:
		int numero;
		int annee;
		string grandPrix;
		string ecurie;
		string constructeur;
		string moteur;
		string pneu;
		int depart;
		int arrivee;
		string remarques;
		int spectateurs;
		
	public:
		~Race();
		Race();
		Race(const Race& r);
		
		void setNumero(const int numero);
		void setAnnee(const int annee);
		void setGrandPrix(const char* grandPrix);
		void setEcurie(const char* ecurie);
		void setConstructeur(const char* constructeur);
		void setMoteur(const char* moteur);
		void setPneu(const char* pneu);
		void setDepart(const int grille);
		void setArrivee(const int arrivee);
		void setArrivee(const char* arrivee);
		void setRemarques(const char* remarques);
		void setSpectateurs(const int spectateurs);

		int getNumero() const;
		int getAnnee() const;
		const char* getGrandPrix() const;
		const char* getEcurie() const;
		const char* getConstructeur() const;
		const char* getMoteur() const;
		const char* getPneu() const;
		int getDepart() const;
		int getArrivee() const;
		const char* getRemarques() const;
		int getSpectateurs() const;

		Race& operator=(const Race& r);
		
		bool operator<(const Race& r);
		bool operator>(const Race& r);
		bool operator==(const Race& r);
		bool operator!=(const Race& r);
		
		static int cmp(const Race& r1, const Race& r2);
		
		friend ostream& operator<<(ostream& out, const Race& r);
};

#endif