#include <iostream>
#include <fstream>
#include <time.h>

#include "FichierLog.h"

using namespace std;

FichierLog::FichierLog() // private
{
}

FichierLog::FichierLog(char* chemin)
{
	this->stream.open(chemin);
}

FichierLog::~FichierLog()
{
	this->stream.close();
}

FichierLog& FichierLog::operator<<(char* texte)
{
	time_t t = time(NULL);
	struct tm *date = localtime(&t);
	
	this->stream << '[' << date->tm_mday << '-' 
	                    << date->tm_mon +1 << '-'
	                    << date->tm_year + 1900 << ' '
	                    << date->tm_hour << ':'
	                    << date->tm_min << ':'
	                    << date->tm_sec << "] "
	             << texte << endl;
	
	return *this;
}


