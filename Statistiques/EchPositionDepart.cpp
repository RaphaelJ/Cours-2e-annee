#include "EchPositionDepart.h"

EchPositionDepart::EchPositionDepart() // Private
{
	this->nom = "Positions de départ";
}

EchPositionDepart::EchPositionDepart(const EchPositionDepart& e)
{
	this->nom = "Positions de départ";
	
	*this = e;
}

EchPositionDepart::EchPositionDepart(const Races& races)
{
	this->nom = "Positions de départ";
	
	// Calcule le nombre d'effectifs pour chaque valeur
	map<int, int> effectifs; // valeur => effectif
	
	this->effectifTotal = 0;
	this->effectifsDistincts = 0;
	list<Race>::const_iterator i;
	for (i=races.getListe().begin(); i!=races.getListe().end(); i++) {
		// Recherche en O(log² n) (B-tree)
		map<int, int>::iterator pos;
		pos = effectifs.find(i->getDepart());
		
		if (pos == effectifs.end()) { // Non présent
			effectifs[i->getDepart()] = 1;
			this->effectifsDistincts += 1;
		} else
			effectifs[i->getDepart()] += 1;
		
		this->effectifTotal += 1;
	}
	
	this->data = mapToDataXVector(effectifs);
}

EchPositionDepart& EchPositionDepart::operator=(const EchPositionDepart& e)
{
	this->data = e.getData();
	this->effectifTotal = e.getEffectifTotal();
	this->effectifsDistincts = e.getEffectifsDistincs();
	
	return *this;
}