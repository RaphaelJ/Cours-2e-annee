#ifndef ECRAN_H
#define ECRAN_H

class Race {
	private:
		char* Nom;
		char Date[11];
		int NbTours;
	
	public:
		Race();
		Race(const Race& race);
		Race(char* nom, char* date, int nbTours);
		
		~Race();
		
		const static char* defaultDate;
		
		void setNom(char* nom);
		void setCircuit(char* nom);
		void setDate(const char* date);
		void setNbTours(const int nbTours);
		
		char* getNom() const;
		char* getCircuit() const;
		const char* getDate() const;
		int getNbTours() const;

		void Affiche() const;
		void affiche() const;
};

#endif