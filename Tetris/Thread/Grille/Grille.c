#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "EcranX.h"
#include "Grille.h"

void* FctThreadRefresh(void *p);

/****************************************************************************************/
int OuvrirGrille(GRILLE *pg,int Ligne,int Colonne,int TailleCarre,char* titre)
{
  int hauteur,largeur,l,c;

  if ((Ligne<=0) || (Colonne<=0) || (TailleCarre<=1) || (Ligne>100) || (Colonne>100)) return -1;

  for (l=0 ; l<Ligne ; l++)
    for (c=0 ; c<Colonne ; c++) pg->tab[l][c] = BLANC;

  pg->Ligne       = Ligne;
  pg->Colonne     = Colonne;
  pg->TailleCarre = TailleCarre;

  hauteur = 1 + Ligne * TailleCarre;
  largeur = 1 + Colonne * TailleCarre;

  if (CreeTermGraph(&(pg->tc),largeur,hauteur,titre) == -1)
  {
    perror("Erreur de CreeTermGraph ");
    return (-1);
  }

  pthread_mutex_init(&(pg->MUTEX),NULL);
  pg->alive = 1;
  pthread_create(&(pg->threadRefresh),NULL,FctThreadRefresh,(void*)pg);
  
  return 0;  
}

/****************************************************************************************/
void DessinerGrillage(GRILLE *pg)
{
  int i,hauteur,largeur;
  hauteur = 1 + pg->Ligne * pg->TailleCarre;
  largeur = 1 + pg->Colonne * pg->TailleCarre;
  
  pthread_mutex_lock(&(pg->MUTEX));
  if (pg->alive)
  {
    setEpaisseurCrayon(&(pg->tc),1);
  
    for (i=0 ; i<=pg->Colonne ; i++) DessineLigne(&(pg->tc),(i*pg->TailleCarre),0,(i*pg->TailleCarre),(hauteur-1),GRIS);
    for (i=0 ; i<=pg->Ligne ; i++)   DessineLigne(&(pg->tc),0,(i*pg->TailleCarre),(largeur-1),(i*pg->TailleCarre),GRIS);
  }
  pthread_mutex_unlock(&(pg->MUTEX));  
}

/****************************************************************************************/
int FermerGrille(GRILLE *pg)
{
  pthread_cancel(pg->threadRefresh);

  pthread_mutex_lock(&(pg->MUTEX));
  FermeTermGraph(&(pg->tc));
  pg->alive = 0;
  pthread_mutex_unlock(&(pg->MUTEX));

  pthread_mutex_destroy(&(pg->MUTEX));
  return 0;
}

/****************************************************************************************/
int DessineCarre(GRILLE *pg,int ligne,int colonne,int couleur)
{
  int xa,ya,xb,yb;

  if ((ligne>=0) && (ligne<pg->Ligne) && (colonne>=0) && (colonne<pg->Colonne))
  {
    pthread_mutex_lock(&(pg->MUTEX));
    if (pg->alive)
    {
      pg->tab[ligne][colonne] = couleur;
  
      xa = 1 + colonne * pg->TailleCarre;
      ya = 1 + ligne * pg->TailleCarre;
      xb = xa + pg->TailleCarre - 2;
      yb = ya + pg->TailleCarre - 2;

      DessineRectangle(&(pg->tc),xa,ya,xb,yb,couleur,PLEIN);
    }
    pthread_mutex_unlock(&(pg->MUTEX));
    return 0;
  }

  return -1;
}

/****************************************************************************************/
void* FctThreadRefresh(void *p)
{
  int l,c;
  int xa,ya,xb,yb;
  struct timespec  temps;
  GRILLE *pg = (GRILLE*)p;
  
  temps.tv_sec = 1;
  temps.tv_nsec = 0;
  
  while (1)
  {
    DessinerGrillage(pg);
    pthread_mutex_lock(&(pg->MUTEX));
    if (pg->alive)
    {
      for (l=0 ; l<pg->Ligne ; l++)
        for (c=0 ; c<pg->Colonne ; c++)
        {
          xa = 1 + c * pg->TailleCarre;
          ya = 1 + l * pg->TailleCarre;
          xb = xa + pg->TailleCarre - 2;
          yb = ya + pg->TailleCarre - 2;

          DessineRectangle(&(pg->tc),xa,ya,xb,yb,pg->tab[l][c],PLEIN);                      
        }
    }
    pthread_mutex_unlock(&(pg->MUTEX));
                      
    nanosleep(&temps,NULL);
  }  
}
