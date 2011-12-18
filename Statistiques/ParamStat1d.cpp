#include "ParamStat1d.h"

ParamStat1d::ParamStat1d() // Private
{
}

ParamStat1d::ParamStat1d(const ParamStat1d& p2)
{
	*this = p2;
}

ParamStat1d::ParamStat1d(const DataSourceX& data)
{
	if (data.getEffectifTotal() <= 0)
		throw Exception("L'effectif total ne peut être négatif ou non null.");
	
	this->nomSerie = data.getNom();
	
	this->moyenne = ParamStat1d::calculerMoyenne(data);
	this->mediane = ParamStat1d::calculerMediane(data);
	this->modes = ParamStat1d::calculerModes(data);
	this->ecartType = ParamStat1d::calculerEcartType(data, this->moyenne);
	this->etendue = ParamStat1d::calculerEtendue(data);
	this->CV = ParamStat1d::calculerCV(this->ecartType, this->moyenne);
}

ParamStat1d::~ParamStat1d()
{
}

const char* ParamStat1d::getNomSerie() const
{
	return this->nomSerie.c_str();
}

float ParamStat1d::getMoyenne() const
{
	return this->moyenne;
}

int ParamStat1d::getMediane() const
{
	return this->mediane;
}

const list<int>& ParamStat1d::getModes() const
{
	return this->modes;
}

float ParamStat1d::getEcartType() const
{
	return this->ecartType;
}

int ParamStat1d::getEtendue() const
{
	return this->etendue;
}

float ParamStat1d::getCV() const
{
	return this->CV;
}

float ParamStat1d::calculerMoyenne(const DataSourceX& data)
{
	int somme = 0;
	vector<DataX>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++)
		somme += i->n * i->x;
	
	return (float) somme / data.getEffectifTotal();
}

int ParamStat1d::calculerMediane(const DataSourceX& data)
{
	// Sélectionne le valeur de la médiane
	int sumPopulation = 0;
	vector<DataX>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++) {
		sumPopulation += i->n;
		if (sumPopulation >= data.getEffectifTotal() / 2)
			return i->x;
	}
	return 0;
}

list<int> ParamStat1d::calculerModes(const DataSourceX& data)
{
	list<int> modes;
	
	int max = 0; // Nombre maximum d'effectifs
	vector<DataX>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++) {
		if (modes.empty()) {
			// Premier
			modes.push_front(i->x);
			max = i->n;
		} else if (max < i->n) {
			// Nouveau mode avec plus d'effectifs
			modes.clear();
			modes.push_front(i->x);
			max = i->n;
		} else if (max == i->n) {
			// Nouveau mode avec autant d'effectifs
			modes.push_front(i->x);
		}
	}
	
	return modes;
}

float ParamStat1d::calculerEcartType(const DataSourceX& data, const float moyenne)
{
	int sumDifferences = 0; // Somme des écarts au carré
	vector<DataX>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++)
		sumDifferences += pow(i->x - moyenne, 2) * i->n;
	
	return (float) sumDifferences / data.getEffectifTotal();
}

int ParamStat1d::calculerEtendue(const DataSourceX& data)
{
	int max = data.getData().back().x;
	int min = data.getData().front().x;
	
	return max - min;
}

int ParamStat1d::calculerCV(const float ecartType, const float moyenne)
{
	return ecartType / moyenne;
}

ParamStat1d& ParamStat1d::operator=(const ParamStat1d& p2)
{
	this->nomSerie = p2.getNomSerie();
	
	this->moyenne = p2.getMoyenne();
	this->mediane = p2.getMediane();
	this->modes = p2.getModes();
	this->ecartType = p2.getEcartType();
	this->etendue = p2.getEtendue();
	this->CV = p2.getCV();
	
	return *this;
}

ostream& operator<<(ostream& out, const ParamStat1d& p)
{
	out << "=== " << p.getNomSerie() << " ===" << endl;
	out << "Moyenne: " << p.getMoyenne() << endl;
	out << "Mediane: " << p.getMediane() << endl;
	
	out << "Modes: ";
	list<int>::const_iterator it;
	for (it=p.getModes().begin(); it!=p.getModes().end(); it++) {
		out << *it << '\t';
	}
	out << endl;
	
	out << "Ecart-type: " << p.getEcartType() << endl;
	out << "Etendue: " << p.getEtendue() << endl;
	out << "CV: " << p.getCV() << endl;
	
	return out;
}