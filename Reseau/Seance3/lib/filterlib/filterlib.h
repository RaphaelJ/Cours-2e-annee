



/*--------------------------------------------------------------------------------------------------------------------------------------
 -------------------------------------------------------------------
 Vanstapel Herman EPL

 L'objectif de ce programme est de construire un noyau de firewall

 version 2004
 Utilisation d'une trame.
---------------------------------------------------------------------
 C'est la couche liaison
---------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../protocol/protocol.h"

#define DROP 1
#define ACCEPT 2

struct Regle {
      int LigneEntree ;
      int IPSource ;
      int MasqueS ;
      int IPDestination ;
      int MasqueD ;
      int PortSource ;
      int PortDestination ;
      int Protocole ;
      int Politique ;
};	

int FiltragePaquet(int LigneEntree,struct Regle TableFiltrage[],int NbrRegles, struct Paquet* PP,int *R);
void LectureTableFiltrage(char *NomFichier,struct Regle TableFiltrage[],int *NbrRegles,int NbrLignes) ;
void AffichageTableFiltrage(struct Regle TableFiltrage[],int NbrRegles) ;
