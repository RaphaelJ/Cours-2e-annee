#include "FichierIndex.h"
#include "FonctionUtile.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int FIOuverture(FICHIERINDEX *F,const char *NomFichier)
{
char 	Nom[80];
sprintf(Nom,"%s.dat",NomFichier);
if ((F->hdFichierData = open(Nom,O_RDWR)) == -1)
   return -1;

return 1;
}

int FIFermeture(FICHIERINDEX F)
{
return 1;
}

int RechercheInt(const FICHIERINDEX F,int Nb)
{
char	Buff[200];
int	rc,Pos = 0;

if (lseek(F.hdFichierData,0,0) == -1)
   return -1;
while (1)
   { if ((rc = read(F.hdFichierData,Buff,F.Taille)) < 0)
        return -1;
     if (rc == 0) break;
     if (*(int *)Buff == Nb) return Pos;
     Pos++;
   }
return Pos;
}

int FIConsultation(const FICHIERINDEX F,const void *Recherche,void *Tab,int Nb)
{
int 	rc,Trouve = 0;
char    *p;

rc = RechercheInt(F,*(int *)Recherche);
if (rc <= 0) return rc;

if (lseek(F.hdFichierData,rc * F.Taille,0) == -1)
   return -1;
while (1)
   { p = (char *)Tab + Trouve * F.Taille;
     if ((rc = read(F.hdFichierData,p,F.Taille)) < 0)
        return -1;
     if (rc == 0) break ;
     if (*(int *)p != *(int *)Recherche) break;
Trace("Trouvedans la boucle = %d",Trouve);
     Trouve++;
     if (Trouve > Nb) return Trouve +1;
   }
Trace("Trouve = %d",Trouve);
return Trouve;
}
