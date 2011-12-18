#include "ParamStat2d.h"

ParamStat2d::ParamStat2d() // Private
{
}

ParamStat2d::ParamStat2d(const ParamStat2d& p2)
{
	*this = p2;
}

ParamStat2d::ParamStat2d(const DataSourceXY& data)
{
	if (data.getEffectifTotal() <= 0)
		throw Exception("L'effectif total ne peut être négatif ou non null.");
	
	this->nomSerie = data.getNom();
	
	this->moyenneX = ParamStat2d::calculerMoyenneX(data);
	this->moyenneY = ParamStat2d::calculerMoyenneY(data);
	this->ecartTypeX = ParamStat2d::calculerEcartTypeX(data, this->moyenneX);
	this->ecartTypeY = ParamStat2d::calculerEcartTypeY(data, this->moyenneY);
	this->etendueX = ParamStat2d::calculerEtendueX(data);
	this->etendueY = ParamStat2d::calculerEtendueY(data);
	this->correlationLineaire = ParamStat2d::calculerCorrelationLineaire(
		data, this->moyenneX, this->moyenneY
	);
	this->regressionA = ParamStat2d::calculerRegressionA(
		data, this->moyenneX, this->moyenneY
	);
	this->regressionB = ParamStat2d::calculerRegressionB(
		data, this->moyenneX, this->moyenneY, this->regressionA
	);
}

ParamStat2d::~ParamStat2d()
{
}

const char* ParamStat2d::getNomSerie() const
{
	return this->nomSerie.c_str();
}

float ParamStat2d::getMoyenneX() const
{
	return this->moyenneX;
}

float ParamStat2d::getMoyenneY() const
{
	return this->moyenneY;
}

float ParamStat2d::getEcartTypeX() const
{
	return this->ecartTypeX;
}

float ParamStat2d::getEcartTypeY() const
{
	return this->ecartTypeY;
}

int ParamStat2d::getEtendueX() const
{
	return this->etendueX;
}

int ParamStat2d::getEtendueY() const
{
	return this->etendueY;
}

float ParamStat2d::getCorrelationLineaire() const
{
	return this->correlationLineaire;
}

float ParamStat2d::getRegressionA() const
{
	return this->regressionA;
}

float ParamStat2d::getRegressionB() const
{
	return this->regressionB;
}

float ParamStat2d::calculerMoyenneX(const DataSourceXY& data)
{
	int somme = 0;
	vector<DataXY>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++)
		somme += i->x;
	
	return (float) somme / data.getEffectifTotal();
}

float ParamStat2d::calculerMoyenneY(const DataSourceXY& data)
{
	int somme = 0;
	vector<DataXY>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++)
		somme += i->y;
	
	return (float) somme / data.getEffectifTotal();
}

float ParamStat2d::calculerEcartTypeX(const DataSourceXY& data, const float moyenneX)
{
	int sumDifferences = 0; // Somme des écarts au carré
	vector<DataXY>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++)
		sumDifferences += pow(i->x - moyenneX, 2);
	
	return (float) sumDifferences / data.getEffectifTotal();
}

float ParamStat2d::calculerEcartTypeY(const DataSourceXY& data, const float moyenneY)
{
	int sumDifferences = 0; // Somme des écarts au carré
	vector<DataXY>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++)
		sumDifferences += pow(i->y - moyenneY, 2);
	
	return (float) sumDifferences / data.getEffectifTotal();
}

int ParamStat2d::calculerEtendueX(const DataSourceXY& data)
{
	int min, max;
	vector<DataXY>::const_iterator i = data.getData().begin();
	max = min = i->x;
	for (i++; i!=data.getData().end(); i++) {
		if (i->x < min)
			min = i->x;
		else if (i->x > max)
			max = i->x;
	}
	return max - min;
}

int ParamStat2d::calculerEtendueY(const DataSourceXY& data)
{
	int min, max;
	vector<DataXY>::const_iterator i = data.getData().begin();
	max = min = i->y;
	for (i++; i!=data.getData().end(); i++) {
		if (i->y < min)
			min = i->y;
		else if (i->y > max)
			max = i->y;
	}
	return max - min;
}

float ParamStat2d::calculerCorrelationLineaire(const DataSourceXY& data, const float moyenneX,
				               const float moyenneY)
{
	float dividente = 0;
	float diviseur1 = 0;
	float diviseur2 = 0;
	
	vector<DataXY>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++) {
		dividente += (i->x - moyenneX) * (i->y - moyenneY);
		diviseur1 += pow(i->x - moyenneX, 2);
		diviseur2 += pow(i->y - moyenneY, 2);
	}
	
	return dividente / (sqrt(diviseur1) * sqrt(diviseur2));
}

float ParamStat2d::calculerRegressionA(const DataSourceXY& data, const float moyenneX,
				       const float moyenneY)
{
	float dividente = 0;
	float diviseur = 0;
	
	vector<DataXY>::const_iterator i;
	for (i=data.getData().begin(); i!=data.getData().end(); i++) {
		dividente += (i->x - moyenneX) * (i->y - moyenneY);
		diviseur += pow(i->x - moyenneX, 2);
	}
	
	return dividente / diviseur;
}

float ParamStat2d::calculerRegressionB(const DataSourceXY& data, const float moyenneX,
				       const float moyenneY, const float regressionA)
{
	return moyenneY - regressionA * moyenneX;
}

ParamStat2d& ParamStat2d::operator=(const ParamStat2d& p2)
{
	this->nomSerie = p2.getNomSerie();
	
	this->moyenneX = p2.getMoyenneX();
	this->moyenneY = p2.getMoyenneY();
	this->ecartTypeX = p2.getEcartTypeX();
	this->ecartTypeY = p2.getEcartTypeY();
	this->etendueX = p2.getEtendueX();
	this->etendueY = p2.getEtendueY();
	this->regressionA = p2.getRegressionA();
	this->regressionB = p2.getRegressionB();
	this->correlationLineaire = p2.getCorrelationLineaire();
	
	return *this;
}

ostream& operator<<(ostream& out, const ParamStat2d& p)
{
	out << "=== " << p.getNomSerie() << " ===" << endl;
	out << "Moyennes : X: " << p.getMoyenneX() <<
	                 " Y: " << p.getMoyenneY() << endl;
	out << "Ecarts types : X: " << p.getEcartTypeX() <<
	                     " Y: " << p.getEcartTypeY() << endl;
	out << "Etendues : X: " << p.getEtendueX() <<
	                 " Y: " << p.getEtendueY() << endl;
	out << "Regressions : a: " << p.getRegressionA() <<
	                     " b: " << p.getRegressionB() << endl;
	out << "Correlation lineaire : " << p.getCorrelationLineaire()
	    << endl;
	
	return out;
}