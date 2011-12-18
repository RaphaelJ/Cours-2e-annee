#ifndef ECHNOMBRESPECTATEURS_H
#define ECHNOMBRESPECTATEURS_H

#include <algorithm>
#include <list>
#include <map>
#include <string>

#include "Exception.h"
#include "Races.h"
#include "DataSourceX.h"
#include "DataX.h"

using namespace std;

class EchNombreSpectateurs : public DataSourceX {
	private:		
		EchNombreSpectateurs();
		
	public:
		EchNombreSpectateurs(const EchNombreSpectateurs& e);
		EchNombreSpectateurs(const Races& races, const int taille_classes);
		
		EchNombreSpectateurs& operator=(const EchNombreSpectateurs& e);
};

#endif