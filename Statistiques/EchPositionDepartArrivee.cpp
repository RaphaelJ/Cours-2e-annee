#include "EchPositionDepartArrivee.h"

EchPositionDepartArrivee::EchPositionDepartArrivee() // Private
{
	this->nom = "Positions de départ et d'arrivée";
}

EchPositionDepartArrivee::EchPositionDepartArrivee(const EchPositionDepartArrivee& e)
{
	this->nom = "Positions de départ et d'arrivée";
	
	*this = e;
}

EchPositionDepartArrivee::EchPositionDepartArrivee(const Races& races)
{
	this->nom = "Positions de départ et d'arrivée";
	
	this->data.resize(races.getListe().size());
	
	this->effectifTotal = 0;
	list<Race>::const_iterator iListe;
	vector<DataXY>::iterator iVector;
	for (iListe=races.getListe().begin(), iVector=this->data.begin();
	     iListe!=races.getListe().end();
	     iListe++) {
		if (iListe->getArrivee() > 0) { // Pas d'abandon
			iVector->x = iListe->getDepart();
			iVector->y = iListe->getArrivee();
			this->effectifTotal += 1;
			iVector++;
		}
	}
	
	// Supprime les places réservées aux abandons
	this->data.resize(this->effectifTotal);
}

EchPositionDepartArrivee& EchPositionDepartArrivee::operator=(const EchPositionDepartArrivee& e)
{
	this->data = e.getData();
	this->effectifTotal = e.getEffectifTotal();
	
	return *this;
}