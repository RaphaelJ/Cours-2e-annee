#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <X11/Xlib.h>
#include "EcranX.h"

/*********************************************************************/
/***** CreeTermGraph : creation d'un terminal graphique          *****/
/***** p : adresse d'une structure du type TC contenant les      *****/
/*****     caracteristiques du terminal graphique                *****/
/***** largeur : largeur en pixels de la zone graphique          *****/
/***** hauteur : hauteur en pixels de la zone graphique          *****/
/***** titre : Nom de la fenetre                                 *****/
/*********************************************************************/
int CreeTermGraph(TC * p, unsigned int largeur, unsigned int hauteur,
		  const char *titre)
{
    char *display_name = getenv("DISPLAY");
    unsigned long valuemask = 0;
    XGCValues values;

    p->largeur = largeur;
    p->hauteur = hauteur;

    if ((p->display = XOpenDisplay(display_name)) == NULL)
	return -1;

    p->screen_num = DefaultScreen(p->display);

    p->win = XCreateSimpleWindow(p->display,
				 RootWindow(p->display, p->screen_num),
				 0, 0,
				 largeur, hauteur,
				 1,
				 BlackPixel(p->display, p->screen_num),
				 WhitePixel(p->display, p->screen_num));

    XStoreName(p->display, p->win, titre);
    XMapWindow(p->display, p->win);
    XFlush(p->display);

    p->gc = XCreateGC(p->display, p->win, valuemask, &values);

  /***** Allocations des couleurs *****/
    p->cm = DefaultColormap(p->display, DefaultScreen(p->display));

    if (XAllocNamedColor
	(p->display, p->cm, "black", &(p->Noir), &(p->Noir)) == 0)
	return -1;

    if (XAllocNamedColor
	(p->display, p->cm, "white", &(p->Blanc), &(p->Blanc)) == 0)
	return -1;

    if (XAllocNamedColor
	(p->display, p->cm, "red", &(p->Rouge), &(p->Rouge)) == 0)
	return -1;

    if (XAllocNamedColor(p->display, p->cm, "blue", &(p->Bleu), &(p->Bleu))
	== 0)
	return -1;

    if (XAllocNamedColor
	(p->display, p->cm, "green", &(p->Vert), &(p->Vert)) == 0)
	return -1;

    if (XAllocNamedColor
	(p->display, p->cm, "yellow", &(p->Jaune), &(p->Jaune)) == 0)
	return -1;

    if (XAllocNamedColor
	(p->display, p->cm, "brown", &(p->Brun), &(p->Brun)) == 0)
	return -1;

    if (XAllocNamedColor(p->display, p->cm, "gray", &(p->Gris), &(p->Gris))
	== 0)
	return -1;

    if (XAllocNamedColor
	(p->display, p->cm, "magenta", &(p->Magenta), &(p->Magenta)) == 0)
	return -1;

    if (XAllocNamedColor(p->display, p->cm, "cyan", &(p->Cyan), &(p->Cyan))
	== 0)
	return -1;

    if (XAllocNamedColor
	(p->display, p->cm, "orange", &(p->Orange), &(p->Orange)) == 0)
	return -1;

    XSetBackground(p->display, p->gc, p->Blanc.pixel);

    XSync(p->display, False);

    sleep(1);

    return 0;
}

/*********************************************************************/
int FermeTermGraph(TC * p)
{
    XCloseDisplay(p->display);

    return 0;
}

/*********************************************************************/
int setCouleurCrayon(TC * p, int couleur)
{
    int c;
    switch (couleur) {
    case NOIR:
	c = p->Noir.pixel;
	break;
    case BLANC:
	c = p->Blanc.pixel;
	break;
    case ROUGE:
	c = p->Rouge.pixel;
	break;
    case BLEU:
	c = p->Bleu.pixel;
	break;
    case VERT:
	c = p->Vert.pixel;
	break;
    case JAUNE:
	c = p->Jaune.pixel;
	break;
    case BRUN:
	c = p->Brun.pixel;
	break;
    case GRIS:
	c = p->Gris.pixel;
	break;
    case MAGENTA:
	c = p->Magenta.pixel;
	break;
    case CYAN:
	c = p->Cyan.pixel;
	break;
    case ORANGE:
	c = p->Orange.pixel;
	break;
    default:
	c = p->Noir.pixel;
	break;
    }
    XSetForeground(p->display, p->gc, c);
    XFlush(p->display);

    return 0;
}

/*********************************************************************/
int setEpaisseurCrayon(TC * p, int e)
{
    XSetLineAttributes(p->display, p->gc, e, LineSolid, CapRound,
		       JoinRound);
    return 0;
}

/*********************************************************************/
int DessinePoint(TC * p, int x, int y, int couleur)
{
    setCouleurCrayon(p, couleur);
    XDrawPoint(p->display, p->win, p->gc, x, y);

    XFlush(p->display);
    return 0;
}

/*********************************************************************/
int DessineLigne(TC * p, int x1, int y1, int x2, int y2, int couleur)
{
    setCouleurCrayon(p, couleur);
    XDrawLine(p->display, p->win, p->gc, x1, y1, x2, y2);

    XFlush(p->display);

    return 0;
}

/*********************************************************************/
int DessineRectangle(TC * p, int xg, int yg, int xd, int yd, int couleur,
		     int style)
{
    setCouleurCrayon(p, couleur);
    if (style == CREUX)
	XDrawRectangle(p->display, p->win, p->gc, xg, yg, (xd - xg),
		       (yd - yg));
    if (style == PLEIN)
	XFillRectangle(p->display, p->win, p->gc, xg, yg, (1 + xd - xg),
		       (1 + yd - yg));

    XFlush(p->display);

    return 0;
}

/*********************************************************************/
int DessineDisque(TC * p, int xc, int yc, int rayon, int couleur,
		  int couleurBord)
{
    int x, y;
    int xmxc2, r2, d2;
    int borne = 7;		// arbitraire...

    r2 = rayon * rayon;

    for (x = (xc - rayon); x <= (xc + rayon); x++) {
	xmxc2 = (x - xc) * (x - xc);
	for (y = (yc - rayon); y <= (yc + rayon); y++) {
	    d2 = xmxc2 + (y - yc) * (y - yc);
	    if (d2 < r2) {
		setCouleurCrayon(p, couleur);
		XDrawPoint(p->display, p->win, p->gc, x, y);
	    }

	    if ((-borne < (d2 - r2)) && ((d2 - r2) < borne)) {
		setCouleurCrayon(p, couleurBord);
		XDrawPoint(p->display, p->win, p->gc, x, y);
	    }
	}
    }

    XFlush(p->display);

    return 0;
}
