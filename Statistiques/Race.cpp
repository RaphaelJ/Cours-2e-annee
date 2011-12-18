#include "Race.h"

Race::Race()
{
	this->numero = 0;
	this->annee = 0;
	this->depart = 0;
	this->arrivee = 0;
	this->spectateurs = 0;

	this->grandPrix = "";
	this->ecurie = "";
	this->constructeur = "";
	this->moteur = "";
	this->pneu = "";
	this->remarques = "";
}

Race::Race(const Race &r)
{
	*this = r;
}

Race::~Race()
{
}

void Race::setNumero(int numero)
{
	this->numero = numero;
}

void Race::setAnnee(int annee)
{
	this->annee = annee;
}

void Race::setGrandPrix(const char* grandPrix)
{
	this->grandPrix = grandPrix;
}

void Race::setEcurie(const char* ecurie)
{
	this->ecurie = ecurie;
}

void Race::setConstructeur(const char* constructeur)
{
	this->constructeur = constructeur;
}

void Race::setMoteur(const char* moteur)
{
	this->moteur = moteur;
}

void Race::setPneu(const char* pneu)
{
	this->pneu = pneu;
}

void Race::setDepart(int depart)
{
	this->depart = depart;
}

void Race::setArrivee(int arrivee)
{
	this->arrivee = arrivee;
}

void Race::setArrivee(const char* arrivee)
{
	if (strcmp(arrivee, "ab") == 0)
		this->setArrivee(AB);
	else if (strcmp(arrivee, "dsq") == 0)
		this->setArrivee(DSQ);
	else
		this->setArrivee(atoi(arrivee));
}

void Race::setRemarques(const char* remarques)
{
	this->remarques = remarques;
}

void Race::setSpectateurs(int spectateurs)
{
	this->spectateurs = spectateurs;
}

int Race::getNumero() const
{
	return this->numero;
}

int Race::getAnnee() const
{
	return this->annee;
}

const char* Race::getGrandPrix() const
{
	return this->grandPrix.c_str();
}

const char* Race::getEcurie() const
{
	return this->ecurie.c_str();
}

const char* Race::getConstructeur() const
{
	return this->constructeur.c_str();
}

const char* Race::getMoteur() const
{
	return this->moteur.c_str();
}

const char* Race::getPneu() const
{
	return this->pneu.c_str();
}

int Race::getDepart() const
{
	return this->depart;
}

int Race::getArrivee() const
{
	return this->arrivee;
}

const char* Race::getRemarques() const
{
	return this->remarques.c_str();
}

int Race::getSpectateurs() const
{
	return this->spectateurs;
}

Race& Race::operator=(const Race& r)
{
	this->setNumero(r.getNumero());
	this->setAnnee(r.getAnnee());
	this->setDepart(r.getDepart());
	this->setArrivee(r.getArrivee());
	this->setSpectateurs(r.getSpectateurs());

	this->setGrandPrix(r.getGrandPrix());
	this->setEcurie(r.getEcurie());
	this->setConstructeur(r.getConstructeur());
	this->setMoteur(r.getMoteur());
	this->setPneu(r.getPneu());
	this->setRemarques(r.getRemarques());
	
	return *this;
}

bool Race::operator<(const Race& r)
{
	return Race::cmp(*this, r) < 0;
}
bool Race::operator>(const Race& r)
{
	return Race::cmp(*this, r) > 0;
}
bool Race::operator==(const Race& r)
{
	return Race::cmp(*this, r) == 0;
}
bool Race::operator!=(const Race& r)
{
	return Race::cmp(*this, r) != 0;
}

int Race::cmp(const Race& r1, const Race& r2)
{
	if (r1.numero < r2.numero)
		return -1;
	else if (r1.numero > r2.numero)
		return 1;
	else
		return 0;
}

ostream& operator<<(ostream &out, const Race& r)
{
	out << "Numero: " << r.getNumero() << '\t'
	    << "GP: " << r.getGrandPrix() << '\t'
	    << "Depart: " << r.getDepart() << '\t'
	    << "Spectateurs: " << r.getSpectateurs() << '\t';
	
	if (r.getArrivee() <= -1)
		out << "Resultat: " << "AB";
	else
		out << "Resultat: " << r.getArrivee();
	    
	return out << endl;
}
