#ifndef FICHIERINDEX_H
#define FICHIERINDEX_H

typedef struct 
{ int	hdFichierData;
  int 	hdFichierIndex;
  int 	Taille;
  int 	Offset;
} FICHIER;

int FIOuverture(FICHIER *,const char *);
int FIFermeture(FICHIER);
int FIConsultation(FICHIER,const char *,void *);

#endif
