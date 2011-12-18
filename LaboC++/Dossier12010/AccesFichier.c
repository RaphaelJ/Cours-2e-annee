#include "AccesFichier.h"
#include "Ecran.h"

#include <fcntl.h>
#include <unistd.h>

#define         TRUE    1
#define         FALSE   0

typedef struct
{
  int OffSet;
  short Longueur;
  char Donnee[255];
} ELEMENT;

int
Ouverture (FICHIER * F, const char *NomFichier)
{
  Trace ("Ouverture du fichier %s", NomFichier);
  strcpy (F->NomFichier, NomFichier);
  if ((F->hdF = open (NomFichier, O_RDWR)) != -1)
    return 0;
  if ((F->hdF = open (NomFichier, O_RDWR | O_CREAT | O_EXCL, 0666)) == -1)
    return -1;

  ELEMENT Elm;
  Elm.OffSet = 8;
  Elm.Longueur = 0;
  if (write (F->hdF, &Elm, 8) == -1)
    return -1;
  return 0;
}

int
Fermeture (FICHIER F)
{
  Trace ("Fermeture du fichier");
  return close (F.hdF);
}

int
Ajout (FICHIER F, const char *Cle, const char *Valeur)
{
  Trace ("Ajout de --%s--%s--", Cle, Valeur);
  char *p = (char *) malloc (2 * sizeof (ELEMENT));
  ELEMENT *pElm1, *pElm2;
  ELEMENT Elm;
  int TrouveLibre = FALSE;

  sprintf (Elm.Donnee, "%s=%s", Cle, Valeur);
  int rc;
  int Pos = 0, PosInter;

  Elm.Longueur = strlen (Elm.Donnee);
  Elm.OffSet = OffSetElm (Elm.Longueur);
  lseek (F.hdF, 0, SEEK_SET);
  if ((rc = read (F.hdF, p, 2 * sizeof (ELEMENT))) == -1)
    return LibereM (p, -1);


  pElm1 = (ELEMENT *) p;
  Pos += pElm1->OffSet;
  pElm2 = (ELEMENT *) (p + pElm1->OffSet);
  int inter = OffSetElm (pElm1->Longueur);
/*
*/
  while (pElm1->OffSet < rc)
    {
      RechercheCle (pElm2->Donnee);
      if (!strcmp (pElm2->Donnee, Cle))
	return LibereM (p, 0);
      lseek (F.hdF, Pos, SEEK_SET);
      if ((rc = read (F.hdF, p, 2 * sizeof (ELEMENT))) == -1)
	return LibereM (p, -1);
      pElm1 = (ELEMENT *) p;
      inter = OffSetElm (pElm1->Longueur);
/*
*/
      Pos += pElm1->OffSet;
      if (rc == pElm1->OffSet)
	break;
      pElm2 = (ELEMENT *) (p + pElm1->OffSet);
    }
  if (TrouveLibre)
    {				/*
				 */
      return LibereM (p, 0);
    }
  lseek (F.hdF, 0, SEEK_END);
  if ((rc = write (F.hdF, &Elm, Elm.OffSet)) == -1)
    return LibereM (p, -1);
  return LibereM (p, 0);
}

int
LibereM (char *p, int rc)
{
  free (p);
  return rc;
}

int
Liste (FICHIER F)
{
  printf ("Liste du fichier : %s\n------------------\n", F.NomFichier);
  return 0;
}

int
Suppression (FICHIER F, const char *Cle)
{
  return 0;
}

int
OffSetElm (int Taille)
{
  int rc, OffSet;
  OffSet = Taille + 7;		// 6 + (Taille + 1)
  rc = OffSet % 4;
  if (rc)
    OffSet = OffSet + 4 - rc;

  return OffSet;
}

void
RechercheCle (char *Donnee)
{
  int i = 0;
  while (Donnee[i] != '=')
    i++;
  Donnee[i] = '\0';
  return;
}
