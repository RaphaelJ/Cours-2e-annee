#include <stdlib.h>
#include <iostream>
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
//#include "Circuits/InvalidDateException.h"
//#include "Circuits/InvalidRaceSizeException.h"
#include "Circuits/MyVector.h"
#include "Circuits/MyList.h"
#include "Circuits/MySortedList.h"

int  Menu();
void Essai1();
void Essai2();
void Essai3();
void Essai4();
void Essai5();

int main()
{
  int choix;
  bool fini = false;
  srand((unsigned)time(NULL));
  
  while(!fini)
  {
    //    EffEcran();
    Essai5();
    choix = Menu();
    switch(choix)
    {
      case 1 : Essai1(); break;
      case 2 : Essai2(); break;
      case 3 : Essai3(); break;
      case 4 : Essai4(); break;
      case 5 : Essai5(); break;
      default : fini = true ; break;
    }
  }

  exit(0);
}

int Menu()
{
  cout << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 6 --------------------------------------------------------------------" << endl;
  cout << "--------------------------------------------------------------------------------------" << endl;
  cout << " 1. Test du template MyVector avec des entiers" << endl; 
  cout << " 2. Test du template MyVector avec des objets de la classe Race" << endl;
  cout << " 3. Test du template MyVector avec des objets de la classe Competitor" << endl;
  cout << endl << "et si vous voulez prendre de l'avance..." << endl << endl;
  cout << " 4. Test du template MyList avec des entiers" << endl;
  cout << " 5. Test du template MySortedList avec des entiers" << endl;
  cout << " 6. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  return ch;
}

/*******************************************************************************************************/
void Essai1()
{
  cout << "----- 1. Test du template MyVector avec des entiers ------------------------" << endl;
  cout << "Creation  d'un vecteur de 5 cases..." << endl;
  MyVector<int> vec(5);
  vec.affiche();                                         // --> -- -- -- -- --
  cout << endl;

  cout << "L'element d'indice 2 devient 34" << endl;
  if (vec.indiceValide(2)) vec.setElement(2,34);
  vec.affiche();                                         // --> -- -- 34 -- --
  cout << endl;

  cout << "L'element d'indice 4 devient 71" << endl;
  if (vec.indiceValide(4)) vec.setElement(4,71);
  vec.affiche();                                         // --> -- -- 34 -- 71
  cout << endl;

  cout << "On recupere l'element d'indice 2 (sans le retirer !!!)" << endl;
  if (vec.indiceValide(2) && vec.estOccupe(2))
  { 
    int val= vec.getElement(2);
    cout << "Element recupere = " << val << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl;

  cout << "On recupere l'element d'indice 3 (sans le retirer !!!)" << endl;
  if (vec.indiceValide(3) && vec.estOccupe(3))   // ce serait beau de gerer ceci avec des exceptions... :-)
  { 
    int val= vec.getElement(3);
    cout << "Element recupere = " << val << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl;

  vec.affiche();                                         // --> -- -- 34 -- 71
  cout << endl;

  cout << "On retire l'element d'indice 2" << endl;
  if (vec.indiceValide(2) && vec.estOccupe(2))   // ce serait beau de gerer ceci avec des exceptions... :-)
  { 
    int val = vec.retireElement(2);
    cout << "Element recupere = " << val << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl; 

  vec.affiche();                                         // --> -- -- -- -- 71
  cout << endl;

  cout << "On ajoute 43 en utilisant l'operateur +" << endl;
  // operator+ : Ajout dans la premiere case libre du vecteur
  vec + 43;
  vec.affiche();                                         // --> 43 -- -- -- 71
  cout << endl;

  cout << "On ajoute 59 en utilisant l'operateur +" << endl;
  vec + 59;
  vec.affiche();                                         // --> 43 59 -- -- 71
  cout << endl;
}

/*********************************************************************************************/
void Essai2()
{
  cout << "----- 2. Test du template MyVector avec des objets de la classe Race -------------" << endl;
  cout << "Creation  d'un vecteur de 7 cases..." << endl;
  MyVector<Race> vec(7);
  vec.affiche();                 
  cout << endl;

  Race r1(&Circuit::SILVERSTONE,Date("10/07/2010"),53);
  Race r2(&Circuit::SPA_FRANCORCHAMPS,Date("12/08/2010"),79);

  cout << "L'element d'indice 2 devient Silverstone" << endl;
  if (vec.indiceValide(2)) vec.setElement(2,r1);
  vec.affiche();                                  
  cout << endl;
  
  cout << "L'element d'indice 4 devient Spa-Francorchamps" << endl;
  if (vec.indiceValide(4)) vec.setElement(4,r2);
  vec.affiche();                                  
  cout << endl;

  cout << "On recupere l'element d'indice 2 (sans le retirer !!!)" << endl;
  if (vec.indiceValide(2) && vec.estOccupe(2))
  { 
    Race r = vec.getElement(2);
    cout << "Element recupere = " << r << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl;

  cout << "On recupere l'element d'indice 3 (sans le retirer !!!)" << endl;
  if (vec.indiceValide(3) && vec.estOccupe(3))   // ce serait beau de gerer ceci avec des exceptions... :-)
  { 
    Race r = vec.getElement(3);
    cout << "Element recupere = " << r << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl;

  vec.affiche();
  cout << endl;

  cout << "On retire l'element d'indice 2" << endl;
  if (vec.indiceValide(2) && vec.estOccupe(2))   // ce serait beau de gerer ceci avec des exceptions... :-)
  { 
    Race r = vec.retireElement(2);
    cout << "Element recupere = " << r << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl; 

  vec.affiche();   
  cout << endl;

  Circuit circuitMonaco("France","Monaco",3.34f);
  cout << "On ajoute Monaco (1/8/2010) en utilisant l'operateur +" << endl;
  // operator+ : Ajout dans la premiere case libre du vecteur
  vec + Race(&circuitMonaco,Date("01/08/2010"),50);
  vec.affiche();                                         
  cout << endl;

  Race rM(&circuitMonaco,Date("02/08/2010"),50);
  cout << "On ajoute Monaco (2/8/2010) en utilisant l'operateur +" << endl;
  vec + rM;
  vec.affiche();                                        
  cout << endl;
}

/*********************************************************************************************/
void Essai3()
{
  cout << "----- 3. Test du template MyVector avec des objets de la classe Competitor ------" << endl;
  cout << "Creation  d'un vecteur de 5 cases..." << endl;
  MyVector<Competitor> *p = new MyVector<Competitor>(5);
  p->affiche();                 
  cout << endl;

  Competitor c1("Hamilton","Lewis",Date("07/01/1985"),"Anglais",18,11);
  Competitor c2("Schumacher","Michael",Date("03/01/1969"),"Allemand",0,0);

  cout << "L'element d'indice 2 devient Hamilton" << endl;
  if (p->indiceValide(2))
	  p->setElement(2, c1);
  p->affiche();                                  
  cout << endl;
  
  cout << "L'element d'indice 4 devient Schumacher" << endl;
  if (p->indiceValide(4))
	  p->setElement(4,c2);
  p->affiche();                                  
  cout << endl;

  cout << "On recupere l'element d'indice 2 (sans le retirer !!!)" << endl;
  if (p->indiceValide(2) && p->estOccupe(2))
  { 
    Competitor c = p->getElement(2);
    cout << "Element recupere = " << c << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl;

  cout << "On recupere l'element d'indice 3 (sans le retirer !!!)" << endl;
  if (p->indiceValide(3) && p->estOccupe(3))   // ce serait beau de gerer ceci avec des exceptions... :-)
  { 
    Competitor c = p->getElement(3);
    cout << "Element recupere = " << c << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl;

  p->affiche();
  cout << endl;

  cout << "On retire l'element d'indice 2" << endl;
  if (p->indiceValide(2) && p->estOccupe(2))   // ce serait beau de gerer ceci avec des exceptions... :-)
  { 
    Competitor c = p->retireElement(2);
    cout << "Element recupere = " << c << endl;
  }
  else cout << "Case non occupee ou indice invalide !" << endl;
  cout << endl; 

  p->affiche();   
  cout << endl;

  cout << "On ajoute Webber en utilisant l'operateur +" << endl;
  // operator+ : Ajout dans la premiere case libre du vecteur
  (*p) + Competitor("Webber","Mark",Date("27/08/1976"),"Australien",0,0);
  p->affiche();                                         
  cout << endl;

  Competitor c("Button","Jenson",Date("19/01/1980"),"Anglais",0,0);
  cout << "On ajoute Button en utilisant l'operateur +" << endl;
  (*p) + c;
  p->affiche();                                        
  cout << endl;


  delete p;
}

/*********************************************************************************************/
void Essai4()
{
  cout << "----- 4. Test du template MyList avec des entiers -------------------------" << endl;
  MyList<int> liste;
  cout << "Nombre d'elements = " << liste.size() << endl;    // --> 0
  liste.affiche();                                           // --> rien du tout :-)
  cout << endl;

  cout << "On ajoute 3 au debut..." << endl;
  liste.ajoutePremier(3);
  cout << "Nombre d'elements = " << liste.size() << endl;    // --> 1
  liste.affiche();                                           // --> 3
  cout << endl;

  cout << "On ajoute 7 a la fin..." << endl;
  liste.ajouteDernier(7);
  cout << "Nombre d'elements = " << liste.size() << endl;    // --> 2
  liste.affiche();                                           // --> 3 7
  cout << endl;

  cout << "On ajoute 12 au debut..." << endl;
  liste.ajoutePremier(12);
  cout << "Nombre d'elements = " << liste.size() << endl;    // --> 3
  liste.affiche();                                           // --> 12 3 7
  cout << endl;

  cout << "On ajoute 19 a la fin..." << endl;
  liste.ajouteDernier(19);
  cout << "Nombre d'elements = " << liste.size() << endl;    // --> 4
  liste.affiche();                                           // --> 12 3 7 19
  cout << endl;

  cout << "On retire le premier element..." << endl;
  int ret;
  if (!liste.vide()) ret = liste.retirePremier();
  cout << "Element retire = " << ret << endl;                // --> 12
  cout << "Nombre d'elements = " << liste.size() << endl;    // --> 3
  liste.affiche();                                           // --> 3 7 19
  cout << endl;

  cout << "On retire le dernier element..." << endl;
  if (!liste.vide()) ret = liste.retireDernier();
  cout << "Element retire = " << ret << endl;                // --> 19
  cout << "Nombre d'elements = " << liste.size() << endl;    // --> 2
  liste.affiche();                                           // --> 3 7
  cout << endl;
}

/********************************************************************************************/
void Essai5()
{
  cout << "----- 5. Test du template MySortedList avec des entiers ----------------------" << endl;
  MySortedList<int> liste;
  liste.affiche();
  cout << endl;

  cout << "On insere 11..." << endl;
  liste.insere(11);
  liste.affiche();
  cout << endl;

  cout << "On insere 19..." << endl;
  liste.insere(19);
  liste.affiche();
  cout << endl;

  cout << "On insere 5..." << endl;
  liste.insere(5);
  liste.affiche();
  cout << endl;

  cout << "On insere 15..." << endl;
  liste.insere(15);
  liste.affiche();
  cout << endl;

  cout << "On insere 21..." << endl;
  liste.insere(21);
  liste.affiche();
  cout << endl;

  cout << "On met la liste en mode DECROISSANT... " << endl;
  liste.setMode(MySortedList<int>::DECROISSANT);
  liste.affiche();
  cout << endl;

  cout << "On insere 18..." << endl;
  liste.insere(18);
  liste.affiche();
  cout << endl;

  cout << "On met la liste en mode CROISSANT... " << endl;
  liste.setMode(MySortedList<int>::CROISSANT);
  liste.affiche();
  cout << endl;

  cout << "On insere 13..." << endl;
  liste.insere(13);
  liste.affiche();
  cout << endl;

  cout << "On retire le premier element..." << endl;
  if (!liste.vide())
  { 
    int ret = liste.retirePremier();
    cout << "Element retire = " << ret << endl;
  }
  else cout << "Impossible, liste vide..." << endl;
  liste.affiche();
  cout << endl;

  cout << "On retire le dernier element..." << endl;
  if (!liste.vide())
  { 
    int ret = liste.retireDernier();
    cout << "Element retire = " << ret << endl;
  }
  else cout << "Impossible, liste vide..." << endl;
  liste.affiche();
  cout << endl;
}
