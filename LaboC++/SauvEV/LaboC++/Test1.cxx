#include <stdlib.h>
#include <iostream.h>
#include "Race.h"

// Quelques conseils avant de commencer...
// * N'oubliez pas de tracer (cout << ...) tous les constructeurs et le destructeur !!! Ca, c'est pas un conseil,
//   c'est obligatoire :-)
// * N'essayez pas de compiler ce programme entierement immediatement. Mettez tout en commentaires
//   sauf le point (1) et creez votre classe (dans ce fichier pour commencer) afin de compiler et tester 
//   le point (1). Une fois que cela fonctionne, decommentez le point (2) et modifier votre classe en 
//   consequence. Vous developpez, compilez et testez donc etape par etape. N'attendez pas d'avoir encode 
//   300 lignes pour compiler...
// * Une fois que tout le programme compile et fonctionne correctement, creez le .h contenant la declaration
//   de la classe, le .cxx contenant la definition des methodes, et ensuite le makefile permettant de compiler
//   le tout grace a la commande make 

int main()
{
  cout << "(1) ***** Test constructeur par defaut + affiche *****" << endl;
  Race race;
  race.affiche();
  cout << endl;

  cout << "(2) ***** Test des setters *****" << endl;
  race.setCircuit("Spa_Francorchamps");
  race.setDate("15/08/2010");
  race.setNbTours(67);
  race.affiche();
  cout << endl;

  cout << "(3) ***** Test des getters *****" << endl;
  cout << "Le nom du circuit est  : " << race.getCircuit() << endl;
  cout << "La date est            : " << race.getDate() << endl;
  cout << "Le nombre de tours est : " << race.getNbTours() << endl;
  cout << endl;

  cout << "(4) ***** Test du constructeur d'initialisation *****" << endl;
  Race race2("Monaco","11/07/2010",54);
  race2.affiche();
  cout << endl;

  cout << "(5) ***** Test du constructeur de copie *****" << endl; 
  Race race3(race2);
  race3.setDate("15/07/2010");
  race3.setNbTours(50);
  race3.affiche();
  cout << endl;
  cout << "Montrons tout de meme que l'objet copie n'a pas ete modifie :" << endl;
  race2.affiche();
  cout << endl;

  cout << "(6) ***** Test d'allocation dynamique (constructeur par defaut) *****" << endl;
  Race* p1 = new Race();
  p1->setCircuit("Monza");
  p1->affiche();
  cout << "Le circuit de cette course est : " << p1->getCircuit() << endl;
  delete p1;
  cout << endl;

  cout << "(7) ***** Test d'allocation dynamique (constructeur de copie) *****" << endl;
  Race* p2 = new Race(race2);
  p2->setNbTours(40);
  p2->affiche();
  cout << "Le nombre de tours de cette course est : " << p2->getNbTours() << endl;
  delete p2;
  cout << endl;

  return 0;
}


