#ifndef FICHIERLOG_H
#define FICHIERLOG_H

#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

class FichierLog {
	private:
		ofstream stream;
		
		FichierLog();
	public:
		FichierLog(char* chemin);
		
		~FichierLog();
		
		FichierLog& operator<<(char* texte);
};

#endif