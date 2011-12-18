#include "EchPositionArrivee.h"

EchPositionArrivee::EchPositionArrivee() // Private
{
	this->nom = "Positions d'arrivée";
}

EchPositionArrivee::EchPositionArrivee(const EchPositionArrivee& e)
{
	this->nom = "Positions d'arrivée";
	
	*this = e;
}

EchPositionArrivee::EchPositionArrivee(const Races& races)
{
	this->nom = "Positions d'arrivée";
	
	// Calcule le nombre d'effectifs pour chaque valeur
	map<int, int> effectifs; // valeur => effectif
	
	this->effectifTotal = 0;
	this->effectifsDistincts = 0;
	list<Race>::const_iterator i;
	for (i=races.getListe().begin(); i!=races.getListe().end(); i++) {
		if (i->getArrivee() > 0) { // Ignore les courses non finies
			// Recherche en O(log² n) (B-tree)
			map<int, int>::iterator pos;
			pos = effectifs.find(i->getArrivee());
			
			if (pos == effectifs.end()) { // Non présent
				effectifs[i->getArrivee()] = 1;
				this->effectifsDistincts += 1;
			} else
				effectifs[i->getArrivee()] += 1;
			
			this->effectifTotal += 1;
		}
	}
	
	this->data = mapToDataXVector(effectifs);
}

EchPositionArrivee& EchPositionArrivee::operator=(const EchPositionArrivee& e)
{
	this->data = e.getData();
	this->effectifTotal = e.getEffectifTotal();
	this->effectifsDistincts = e.getEffectifsDistincs();
	
	return *this;
}