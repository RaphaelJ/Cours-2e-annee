#ifndef RACE_H
#define RACE_H

#include "Date.h"
#include "Circuit.h"

class Race {
	private:
		Circuit* circuit;
		Date date;
		int nbTours;
	
	public:
		Race();
		Race(const Race& race);
		Race(Circuit* circuit, const Date date, const int nbTours);
		Race(const char* nom, const char* date, const int nbTours);
		
		~Race();
		
		void setCircuit(Circuit* circuit);
		void setCircuit(const char* nom);
		void setNom(const char* nom);
		void setDate(const Date date);
		void setDate(const char* date);
		void setNbTours(const int nbTours);
		
		Circuit* getCircuit() const;
		const char* getNom() const;
		Date getDate() const;
		int getNbTours() const;
		float getRaceLength() const;

		void Affiche() const;
		void affiche() const;
		
		Race& operator=(const Race& race2);
		
		friend ostream& operator<<(ostream& stream, Race r);
		
		class InvalidRaceSizeException : ExceptionBase {
		public:
			InvalidRaceSizeException()
			{
				this->setMessage("Longueur de la course invalide");
			}
		};
};

#endif