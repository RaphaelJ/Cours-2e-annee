#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>

#include "Circuits/Race.h"
#include "Circuits/Circuit.h"
#include "Circuits/Date.h"
#include "Circuits/Person.h"
#include "Circuits/Competitor.h"
#include "Circuits/AuthorizedPerson.h"
#include "Circuits/FederationAdmin.h"
#include "Circuits/TeamMember.h"
#include "Circuits/ExceptionBase.h"
#include "Circuits/MyVector.h"
#include "Circuits/MyList.h"
#include "Circuits/MySortedList.h"
#include "Circuits/FichierLog.h"
#include "Circuits/FichierBinaire.h"

int  Menu();
void Essai1();
// void Essai2();
void Essai3();
void Essai4();
void Essai5();
void Essai6();

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
//       case 2 : Essai2(); break;
       case 3 : Essai3(); break;
       case 4 : Essai4(); break;
       case 5 : Essai5(); break;
       case 6 : Essai6(); break; 
      case 7 : fini = true ; break; 
    }
  }

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 7 ---------------------------------------------------------" << endl;
  cout << "---------------------------------------------------------------------------" << endl;
  cout << " 1. Test de la classe FichierLog" << endl;
  cout << " 2. Test preliminaire de la serialisation d'un Circuit" << endl;
  cout << " 3. Test de FichierCircuit : Creation du fichier avec quelques circuits" << endl;
  cout << " 4. Test de FichierCircuit : Listing (cout) des circuits present dans le fichier" << endl;
  cout << " 5. Test de FichierCircuit : Ajout d'un circuit au fichier existant" << endl;
  cout << " 6. Test de FichierCircuit : Recherche d'un circuit dans le fichier" << endl;
  cout << " 7. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  return ch;
}

/*********************************************************************************************/
void Essai1()  // Pour cet essai, on utilise les flux caracteres (<<)
{
  cout << "----- 1. Test de la classe FichierLog -------------------------------------" << endl;
  FichierLog fl("RacingWorldChampionship.log");
  fl << "Login de David Coulthard (Red Bull Racing Team)";
  sleep(2);
  fl << "Competitor Lewis Hamilton won at Spa-Francorchamps in 2010";
}

/*********************************************************************************************
void Essai2()  // A partir de cet essai (et pour les autres qui suivent) : les flux bytes (read et write) !!!!
{
  cout << "----- 2. Test preliminaire de la serialisation d'un Circuit ------" << endl;
  // Pas encore de classe FichierCircuit !!! Le Circuit gere lui-meme sa serialisation !!!!

  Circuit c("France","Monaco",3.34f);
  c.affiche();
  cout << endl;

  cout << "----- Sauvegarde du Circuit dans le fichier Monaco.dat -----" << endl;
  ofstream fichier1("Monaco.dat",ios::out);
  c.save(fichier1);
  fichier1.close();

  cout << "----- Chargement du Circuit situe dans le fichier Monaco.dat -----" << endl;
  ifstream fichier2("Monaco.dat",ios::in);
  Circuit c2;
  c2.load(fichier2);
  fichier2.close();
  c2.affiche();
  cout << endl;
}*/

/*********************************************************************************************/
void Essai3()
{
  cout << "----- 3. Test de FichierCircuit : creation du fichier avec quelques circuits -----" << endl;

  Circuit c1(Circuit::SPA_FRANCORCHAMPS);
  Circuit c2(Circuit::SILVERSTONE);
  Circuit c3("France","Monaco",3.34f);
  Circuit c4("Italie","Monza",5.793f);

  FichierBinaire<Circuit> fichier("Circuits.dat");
  fichier.save(c1);
  fichier.save(c2);
  fichier.save(c3);
  fichier.save(c4);
}

/*********************************************************************************************/
void Essai4()
{
  cout << "-----  4. Test de FichierCircuit : Listing (cout) des circuits present dans le fichier -----" << endl;
  FichierBinaire<Circuit> fichier("Circuits.dat");
  fichier.list(cout);  // n'affiche que sur le cout... ooouuhh!!!
}

/********************************************************************************************/
void Essai5()
{
  cout << "----- 5. Test de FichierCircuit : Ajout d'un circuit au fichier existant -----" << 
endl;

  Circuit c("Allemagne","Nurburgring",5.148f);

  FichierBinaire<Circuit> fichier("Circuits.dat");
  fichier.save(c);
  fichier.list(cout);
}

/*********************************************************************************************/
void Essai6()
{
  cout << "----- 6. Test de FichierCircuit : Recherche d'un circuit dans le fichier -----" << endl;
  Circuit c;

  FichierBinaire<Circuit> fichier("Circuits.dat");

  int ret = fichier.load(c,"Monaco");   // Pour bien faire, c doit etre passe par...
  if (ret == 0)
  {
    cout << "----> Circuit trouve <----" << endl;
    c.affiche();
  }
  else cout << "-----> Circuit NON trouve !!! <-----" << endl;

  ret = fichier.load(c,"Inpres");
  if (ret == 0)
  {
    cout << "----> Circuit trouve <----" << endl;
    c.affiche();
  }
  else cout << "-----> Circuit NON trouve !!! <-----" << endl;
}