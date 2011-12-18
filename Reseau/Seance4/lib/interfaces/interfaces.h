/*----------------------------------------------------------------------------
  Vanstapel Herman EPL

   Prototype pour la librairie timerlib.h
------------------------------------------------------------------------------*/

#ifndef INTERFACELIB
#define INTERFACELIB
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include "../physlib/physlib.h"

#define TAILLENOMINTERFACE 40

struct Interface
{
 /* Parametres de gestion des connexions */
struct Physique *IPhys ;
int ILiaison ; 	 /* Le premier est sacrifie  et Liaison contient le descripteur */
int IIP ;         /* Donne les adresses IP des lignes */
int ILigne ;      /* Numero de la ligne ou Interface */
int IEntreeTableRoutage ;
char INomInterface[TAILLENOMINTERFACE] ;
struct Interface *Ipsuiv ;
} ;

struct Interface  *CreationInterface( char *NomInterface ,struct Interface *pl) ;
struct Interface  *AjouteInterface( char *NomInterface ,struct Interface *pl) ;
struct Interface *RechercheInterfaceNom(char *NomInterface,struct Interface *pl) ;
struct Interface *RechercheInterfaceDesc(int Desc,struct Interface *pl)  ;
struct Interface *RechercheInterfaceLigne(int Ligne,struct Interface *pl) ;
struct Interface *SupprimeInterfaces(char *NomInterface , struct Interface *pl) ;
struct Interface *InterfaceSuivante( struct Interface *pi ) ;
void AfficheInterfaces(struct Interface *pl) ;
void ModifiePhys(struct Physique *,struct Interface *) ;
void ModifieLiaison(int ,struct Interface *) ;
void ModifieIP(int ,struct Interface *) ;
void ModifieLigne(int ,struct Interface *) ;
void ModifieNomInterface(char *,struct Interface *) ;
void ModifieEntreeTableRoutage(int NER, struct Interface *) ; /* -- */
struct Physique *ObtenirPhys(struct Interface *) ;
int ObtenirLiaison(struct Interface *pl) ;
int ObtenirIP(struct Interface *pl) ;
int ObtenirLigne(struct Interface *pl) ;
char* ObtenirNomInterface(struct Interface *pl) ;
int ObtenirEntreeTableRoutage(struct Interface *) ; /* -- */
#endif 
