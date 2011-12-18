#ifndef DATE_H
#define DATE_H

#include "ExceptionBase.h"

typedef unsigned char byte;

class Date {
	private:
		byte jour;
		byte mois;
		short annee;
	
	public:
		Date();
		Date(const Date& date);
		Date(const byte jour, const byte mois, const short annee);
		Date(const char* date);
		
		~Date();
		
		static Date defaultDate;
		
		void setJour(const byte jour);
		void setMois(const byte jour);
		void setAnnee(const short annee);
		void setDate(const char* date);
		
		byte getJour() const;
		byte getMois() const;
		short getAnnee() const;

		void Affiche() const;
		void affiche() const;
		
		Date& operator=(const Date& date2);
		
		friend ostream& operator<<(ostream& stream, const Date& date);
		
		class InvalidDateException : ExceptionBase {
		public:
			InvalidDateException()
			{
				this->setMessage("Date invalide");
			}
		};
};

#endif