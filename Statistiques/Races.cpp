#include "Races.h"

using namespace std;

Races::Races(const char* chemin)
{
	this->charger(chemin);
}

// Extrait la partie de chaine entre index et ;
string extraireChaine(const string str, const int index, int& pos_pv)
{
	pos_pv = str.find_first_of(';', index);
	return str.substr(index, pos_pv - index);
}

void Races::charger(const char* chemin)
{
	ifstream fichier(chemin, ios::in);
	
	if (!fichier)
		throw Exception("Impossible d'ouvrir le fichier");
	
	this->listeRaces.clear();
	
	string ligne;
	getline(fichier, ligne); // Première ligne inutile
	while (getline(fichier, ligne)) {
		Race r;
		int pos = 0;
		
		r.setNumero(atoi(extraireChaine(ligne, pos, pos).c_str()));
		r.setAnnee(atoi(extraireChaine(ligne, pos + 1, pos).c_str()));
		r.setGrandPrix(extraireChaine(ligne, pos + 1, pos).c_str());
		r.setEcurie(extraireChaine(ligne, pos + 1, pos).c_str());
		r.setConstructeur(extraireChaine(ligne, pos + 1, pos).c_str());
		r.setMoteur(extraireChaine(ligne, pos + 1, pos).c_str());
		r.setPneu(extraireChaine(ligne, pos + 1, pos).c_str());
		r.setDepart(atoi(extraireChaine(ligne, pos + 1, pos).c_str()));
		r.setArrivee(extraireChaine(ligne, pos + 1, pos).c_str());
		r.setRemarques(extraireChaine(ligne, pos + 1, pos).c_str());
		r.setSpectateurs(atoi(extraireChaine(ligne, pos + 1, pos).c_str()));
		
		this->listeRaces.push_front(r);
	}
	
	fichier.close();
}

const list<Race>& Races::getListe() const
{
	return this->listeRaces;
}

ostream& operator<<(ostream& out, const Races& r)
{
	list<Race>::const_iterator i;
	for (i=r.getListe().begin(); i!=r.getListe().end(); i++)
		out << *i;
	
	return out;
}