#ifndef ACCESFICHIER_H
#define ACCESFICHIER_H

typedef struct
   { int        hdF;
     char       NomFichier[20];
   } FICHIER;

int Ouverture(FICHIER *,const char*);
int Fermeture(FICHIER );
int Ajout(FICHIER,const char*,const char*);
int LibereM(char*,int);
int Liste(FICHIER);
int Suppression(FICHIER,const char*);

int OffSetElm(int);
void RechercheCle(char*);
#endif
