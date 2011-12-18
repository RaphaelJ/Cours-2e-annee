/* Exercice 1 :
   Gestion d'un fichier.
   IN.PR.E.S.
   Denys MERCENIER
   Ecran.h
*/

#ifndef        _ECRAN_H_
#define        _ECRAN_H_

#define        NORM      0
#define        GRAS      1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


/* fonctions simplifiees de gestion d'ecran */

void EffEcran(void);
int LitChaine(char *,int,int,int,int);
void AffChaine(char *,int,int,int);
int Menu(void);
void Pause(void);
void Trace(char *,...);
void Affiche(char *,...);
void SortieErreur(char *,int);
void SauveCurseur(void);
void RestitueCurseur(void);
void EffCadre(int ,int ,int ,int);

#endif     /* _ECRAN_H_ */
