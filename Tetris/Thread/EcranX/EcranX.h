// Librairie simplifiee de terminal graphique
//
// Jean-Marc Wagner
// Date de creation : 27/10/2006
// Date de modification : Decembre 2008


#include<X11/Xlib.h>

#ifndef        _ECRANX_H_
#define        _ECRANX_H_

#define NOIR     0
#define BLANC    1
#define GRIS     2
#define ROUGE    3
#define BLEU     4
#define VERT     5
#define JAUNE    6
#define BRUN     7
#define MAGENTA  8
#define CYAN     9

#define CREUX 0
#define PLEIN 1

typedef struct
{
  Display* display;
  int      largeur,hauteur;
  int      screen_num;
  Window   win;
  GC       gc;
  Colormap cm;
  XColor   Noir,Blanc,Rouge,Bleu,Vert,Jaune;
  XColor   Brun,Gris,Magenta,Cyan;
} TC;

int CreeTermGraph(TC*,unsigned int largeur,unsigned int hauteur,char *titre);
int FermeTermGraph(TC *);
int setCouleurCrayon(TC *p,int couleur);
int setEpaisseurCrayon(TC *p,int e);
int DessinePoint(TC *p,int x,int y,int couleur);
int DessineLigne(TC *p,int x1,int y1,int x2,int y2,int couleur);
int DessineRectangle(TC *p,int xg,int yg,int xd,int yd,int couleur,int style);

#endif     /* _ECRANX_H_ */
