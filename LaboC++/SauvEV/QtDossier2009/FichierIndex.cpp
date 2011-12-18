#include "FichierIndex.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int FIOuverture(FICHIER *F,const char *NomFichier)
{
if ((F->hdFichierData = open(NomFichier,O_RDWR)) == -1)
   return -1;

return 1;
}

int FIFermeture(FICHIER F)
{
return 1;
}

int FIConsultation(FICHIER F,const char *Recherche,void *Tab)
{
int 	rc;
int	Pos;

Pos = atoi(Recherche);

if (lseek(F.hdFichierData,Pos * F.Taille,0) == -1)
   return -1;
if ((rc = read(F.hdFichierData,Tab,F.Taille)) < 0)
   return -1;
if (rc == 0) return 0;
return 1;
}
