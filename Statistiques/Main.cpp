#include <iostream>
#include <fstream>

#include "Exception.h"
#include "Races.h"
#include "ParamStat1d.h"
#include "ParamStat2d.h"

#include "EchPositionDepart.h"
#include "EchPositionArrivee.h"
#include "EchNombreSpectateurs.h"

#include "EchPositionDepartArrivee.h"

using namespace std;

template <typename T>
inline void enregistrerVersFichier(const char* chemin, const T objet);

int main(void)
{
	try {
		Races r = Races("MichaelSchumacher.csv");
		
		ParamStat1d statsPositionDepart((DataSourceX) EchPositionDepart(r));
		cout << statsPositionDepart;
		enregistrerVersFichier<ParamStat1d>("resultats/PositionsDepart", statsPositionDepart);
		cout << "Resultats enregistrés dans resultats/PositionsDepart" << endl;
		
		ParamStat1d statsPositionArrivee((DataSourceX) EchPositionArrivee(r));
		cout << statsPositionArrivee;
		enregistrerVersFichier<ParamStat1d>("resultats/PositionsArrivee", statsPositionArrivee);
		cout << "Resultats enregistrés dans resultats/PositionsArrivee" << endl;
		
		ParamStat1d statsNombreSpectateurs((DataSourceX) EchNombreSpectateurs(r, 5000));
		cout << statsNombreSpectateurs;
		enregistrerVersFichier<ParamStat1d>("resultats/NombreSpectateurs", statsNombreSpectateurs);
		cout << "Resultats enregistrés dans resultats/NombreSpectateurs" << endl;
		
		ParamStat2d statsDepartsArrivees ((DataSourceXY) EchPositionDepartArrivee(r));
		cout << statsDepartsArrivees;
		enregistrerVersFichier<ParamStat2d>("resultats/DepartsArrivees", statsDepartsArrivees);
		cout << "Resultats enregistrés dans resultats/DepartsArrivees" << endl;		
	} catch (Exception e) {
		cerr << e;
	}
}

// Enregistre l'affichage d'un objet quelconque vers un fichier
// L'objet doit supporter l'opérateur <<.
template <typename T>
inline void enregistrerVersFichier(const char* chemin, const T objet)
{
	fstream fichier(chemin, ios::out | ios::trunc);
	
	if (!fichier)
		throw Exception("Impossible d'ouvrir le fichier");
	
	fichier << objet;
	
	fichier.close();
}