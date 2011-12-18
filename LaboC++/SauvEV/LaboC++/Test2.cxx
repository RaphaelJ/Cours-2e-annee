#include <stdlib.h>
#include <iostream.h>
#include "Race.h"
#include "Date.h"
#include "Circuit.h"

int main()
{
  cout << endl << "(1) ***** Test de la classe Date *****" << endl;
  Date date1,date2(10,8,2010),date3("11/08/2010"),date4(date2);
  date1.affiche();
  cout << endl;
  date2.affiche();
  cout << endl;
  date3.affiche();
  cout << endl;
  date4.setJour(12);  
  date4.affiche();
  cout << endl << endl;

  cout << "(2) **** Test de la classe Circuit *****" << endl;
  Circuit circuitMonaco("France","Monaco",3.34f); //ne pas oublier les autres constructeurs !
  circuitMonaco.affiche();
  cout << endl << endl;

  // Modifications de la classe Race :
  // La chaine de caracteres date est remplacee par une instance de la classe Date
  // La chaine de caracteres circuit est remplacee par un pointeur vers un objet de
  // la classe Circuit
  cout << "(3) ***** Test du constructeur par defaut de Race *****" << endl;
  Race race1;
  race1.affiche();
  cout << endl;

  cout << "(4) **** Test des setters *****" << endl;
  Date d("11/07/2010");
  race1.setDate(d);
  race1.setCircuit(&circuitMonaco);
  race1.setNbTours(78);
  race1.affiche();
  cout << "Longueur totale de la course = " << race1.getRaceLength() << " km" << endl;
  cout << endl;

  cout << "(5) ***** Test du constructeur d'initialisation de Race *****" << endl;
  Race race2(&circuitMonaco,Date("12/07/2010"),79);
  race2.affiche();
  cout << "Le mois de cette course est : " << race2.getDate().getMois() << endl << endl;

  cout << "(6) ***** Test du constructeur de copie de Race *****" << endl;
  Race *p = new Race(race2);
  p->setDate(Date(13,7,2010));
  p->affiche();
  delete p;
  cout << endl;

  cout << "(7) ***** Test de la variable membre statique SPA_FRANCORCHAMPS *****" << endl;
  Circuit circuit = Circuit::SPA_FRANCORCHAMPS; 
  // SPA_FRANCORCHAMPS est une instance de la classe Circuit 
  // quel est le constructeur appelé pour circuit ?
  circuit.setLongueur(8.5f);
  Circuit::SPA_FRANCORCHAMPS.affiche();
  cout << endl;
  circuit.affiche();
  cout << endl << endl;

  return 0;
}


