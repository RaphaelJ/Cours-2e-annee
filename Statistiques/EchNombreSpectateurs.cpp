#include "EchNombreSpectateurs.h"

EchNombreSpectateurs::EchNombreSpectateurs() // Private
{
	this->nom = "Nombre de spectateurs";
}

EchNombreSpectateurs::EchNombreSpectateurs(const EchNombreSpectateurs& e)
{
	this->nom = "Nombre de spectateurs";
	
	*this = e;
}

EchNombreSpectateurs::EchNombreSpectateurs(const Races& races, const int taille_classes)
{
	if (taille_classes <= 0) {
		throw Exception(
			"La taille des classes doit être positive et non nulle"
		);
	}
	
	
	this->nom = "Nombre de spectateurs";
	
	// Calcule le nombre d'effectifs pour chaque classe
	map<int, int> effectifs; // classe => effectif
	
	this->effectifTotal = 0;
	this->effectifsDistincts = 0; // Nombre de classes
	list<Race>::const_iterator i;
	for (i=races.getListe().begin(); i!=races.getListe().end(); i++) {
		// Calcule la valeur centrale de la classe qui comprends la valeur
		// Ex.: taille de 1000 et valeur de 3600
		//	3600 // 1000 = 3 # Numero de la classe
		//	3 * 1000 = 3000 # Borne inférieure de la classe
		//	3000 + (1000 // 2) = 3500 # Valeur centrale de la classe
		// 3600 est compris dans la troisième classe, dont la valeur centrale
		// est 3500.
		int num_classe = ((*i).getSpectateurs() / taille_classes) 
		                 * taille_classes
				 + (taille_classes / 2);
		
		// Recherche en O(log² n) (B-tree)
		map<int, int>::iterator pos;
		pos = effectifs.find(num_classe);
		
		if (pos == effectifs.end()) { // Non présent
			effectifs[num_classe] = 1;
			this->effectifsDistincts += 1;
		} else
			pos->second += 1;
		
		this->effectifTotal += 1;
	}
	
	this->data = mapToDataXVector(effectifs);
}

EchNombreSpectateurs& EchNombreSpectateurs::operator=(const EchNombreSpectateurs& e)
{
	this->data = e.getData();
	this->effectifTotal = e.getEffectifTotal();
	this->effectifsDistincts = e.getEffectifsDistincs();
	
	return *this;
}