#include <stdlib.h>
#include <iostream.h>
#include <time.h>

#include "Race.h"
#include "Circuit.h"
#include "Date.h"
#include "Person.h"
#include "Competitor.h"
#include "AuthorisedPerson.h"
#include "FederationAdmin.h"
#include "TeamMember.h"
#include "ExceptionBase.h"
#include "InvalidDateException.h"
#include "InvalidRaceSizeException.h"

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();

int main()
{
  int choix;
  bool fini = false;
  srand((unsigned)time(NULL));

  while(!fini)
  {
    choix = Menu();
    switch(choix)
    {
      case 1 : Essai1(); break;
      case 2 : Essai2(); break;
      case 3 : Essai3(); break;
      case 4 : Essai4(); break;
      case 5 : fini = true ; break;
    }
  }

  exit(0);
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 5 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Test preliminaire de la classe ExceptionBase" << endl;
  cout << " 2. Test des methodes susceptibles de lancer une exception InvalidDateException" << endl;
  cout << " 3. Test de la methode (de Race) susceptible de lancer une InvalidRaceSizeException" << endl;
  cout << " 4. Test de la gestion de plusieurs exceptions en meme temps" << endl;
  cout << " 5. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  return ch;
}

/**********************************************************************************************/
void Essai1()
{
  cout << endl;
  cout << "----- 1. Test preliminaire de la classe ExceptionBase ---------------------" << endl;
  try
  {
    int n = rand()%2;
    if (n == 0)
    {
      ExceptionBase ex("Ceci est un test");
      throw ex;
      // Attention, ce throw n'est ici que pour tester la classe ExceptionBase
      // La bonne pratique veut que les throw apparaissent dans les fonctions 
      // susceptibles de poser problème comme un constructeur ou une fonction
      // membre présentant des parametres non adaptes. 
    }
    cout << "Tout se passe bien :-)" << endl;
  }
  catch (ExceptionBase e)
  {
    cout << "ExceptionBase !!!" << endl;
    cout << "Message = " << e.getMessage() << endl;
  }
  cout << endl;
}

/**********************************************************************************************/
void Essai2()
{
  cout << "----- 2. Test des methodes susceptibles de lancer une exception InvalidDateException --------" << endl;
  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant (try...catch)
  // en particulier : afficher le message de l'exception lancee

  {
    cout << "--> Creation d'un objet de la classe Date <--" << endl;
    char buffer[80];
    cout << "Date (##/##/####) = ";
    cin >> buffer;
    Date date(buffer); // !!!
    date.affiche();
    cout << endl << endl;

    cout << "--> Creation d'un objet de la classe Person <--" << endl;
    Person person;     // attention, voir classes derivees aussi...
    cin >> person;     // !!!
    cout << person;
    cout << endl << endl;

    cout << "--> Creation d'un objet de la classe Race <--" << endl;
    cout << "Date de la course (##/##/####) = ";
    cin >> buffer;
    Race race(&Circuit::SPA_FRANCORCHAMPS,Date(buffer),54);
    race.affiche();
    cout << endl << endl;
  }
  
  cout << endl;
}

/*********************************************************************************************/
void Essai3()
{
  cout << "----- 3. Test de la methode (de Race) susceptible -----" << endl;
  cout << "-----    de lancer une InvalidRaceSizeException       -----" << endl;

  // A COMPLETER : Traitez l'exception susceptible d'etre lancee par le bloc de code suivant
  {
    cout << "--> Creation d'un objet de la classe Race <--" << endl; 
    int n;
    cout << "Nombre de tours = ";
    cin >> n;
    cout << "Circuit :" << endl;
    cout << " 1) Spa Francorchamps" << endl;
    cout << " 2) Silverstone" << endl << endl;
    cout << "Choix :";
    int ch;
    cin >> ch;
    Circuit *pCircuit;
    switch(ch)
    {
      case 1  : pCircuit = &Circuit::SPA_FRANCORCHAMPS; break;
      case 2  : pCircuit = &Circuit::SILVERSTONE; break;
      default : pCircuit = NULL;
    } 
    Race race(pCircuit,Date(15,8,2010),n);
    race.affiche();
    cout << "Longueur de la course = " << race.getRaceLength() << " km" << endl;
  }

  cout << endl;
}

/*********************************************************************************************/
void Essai4()
{
  cout << "----- 4. Test de la gestion de plusieurs exceptions en meme temps ----------" << endl;
  // A COMPLETER : Traitez LES(!!!) exceptions susceptibles d'etre lancees par le le bloc de code suivant
  {
    cout << "--> Creation d'un objet de la classe Race <--" << endl; 
    char buffer[80];
    cout << "Date de la course (##/##/####) : ";
    cin >> buffer;
    Date date(buffer);
    int n;
    cout << "Nombre de tours = ";
    cin >> n;
    cout << "Circuit :" << endl;
    cout << " 1) Spa Francorchamps" << endl;
    cout << " 2) Silverstone" << endl << endl;
    cout << "Choix :";
    int ch;
    cin >> ch;
    Circuit *pCircuit;
    switch(ch)
    {
      case 1  : pCircuit = &Circuit::SPA_FRANCORCHAMPS; break;
      case 2  : pCircuit = &Circuit::SILVERSTONE; break;
      default : pCircuit = NULL;
    } 
    Race race(pCircuit,date,n);
    race.affiche();
    cout << "Longueur de la course = " << race.getRaceLength() << " km" << endl;
  }

  cout << endl; 
}

