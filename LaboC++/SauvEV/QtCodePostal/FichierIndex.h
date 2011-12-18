#ifndef FICHIERINDEX_H
#define FICHIERINDEX_H

typedef struct 
{ int	hdFichierData;
  int 	hdFichierIndex;
  int 	Taille;
  int 	Offset;
} FICHIERINDEX;

int FIOuverture(FICHIERINDEX *,const char *);
int FIFermeture(FICHIERINDEX);
int RechercheInt(const FICHIERINDEX,int);
int FIConsultation(const FICHIERINDEX,const void *,void *,int);

#endif
