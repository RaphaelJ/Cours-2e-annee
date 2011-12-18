#include <stdlib.h>
#include <iostream.h>
#include <time.h>

#include "Person.h"
#include "Date.h"
#include "Competitor.h"
#include "AuthorisedPerson.h"
#include "FederationAdmin.h"
#include "TeamMember.h"

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
    //    EffEcran();
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

  return 0;
}

int Menu()
{
  cout << endl;
  cout << "----------------------------------------------------------------------------" << endl;
  cout << "--- JEU DE TEST 4 ----------------------------------------------------------" << endl;
  cout << "----------------------------------------------------------------------------" << endl;
  cout << " 1. Test de la classe Person" << endl;
  cout << " 2. Test de la classe Competitor" << endl;
  cout << " 3. Heritage et hierarchie (test des methodes (non) virtuelles)" << endl;
  cout << " 4. Test du downcasting et du dynamic-cast" << endl;
  cout << " 5. Quitter" << endl << endl;

  int ch;
  cout << "  Choix : ";
  cin >> ch; // Faites pas le biess !
  return ch;
}

/***********************************************************************************************/
void Essai1()
{
  cout << endl;
  cout << "----- 1.1 Test du constructeur d'initialisation + affiche -------------------" << endl;
  Person moi("Wagner","Jean-Marc",Date("07/02/1974"),"Belge");
  moi.affiche();
  cout << endl;

  cout << "----- 1.2 Test de l'operateur cin -------------------------------------------" << endl;
  Person p2;
  cin >> p2;
  p2.affiche();
  cout << endl;

  cout << "----- 1.3 Test de l'operateur cout ------------------------------------------" << endl;
  cout << "Voici la personne que vous venez d'encoder : " << endl;
  cout << p2 << endl;
}

/***********************************************************************************************/
void Essai2()
{
  cout << "----- 2.1 Test du constructeur d'initialisation ----------------------------" << endl;
  Competitor c("Amilton","Lewis",Date("07/01/1985"),"Anglais",18,11);
  c.affiche();
  cout << endl;

  cout << "----- 2.2 Test des methodes heritees de la classe Person -----------------" << endl;
  c.setNom("Hamilton");
  Person *p = (Person *)&c;    // on fait quoi ici ?
  p->affiche();
  cout << endl;

  cout << "----- 2.3 Allocation dynamique de Competitor avec pointeur de type Competitor ------" << endl;
  Competitor *pc = new Competitor(c); // Vive le constructeur de copie !
  pc->affiche();
  delete pc;
  cout << endl;

  cout << "----- 2.4 Allocation dynamique de Competitor avec pointeur de type Person (Upcasting) -----" << endl;
  Person *pp = new Competitor(c);
  pp->affiche();
  delete pp; // Ouch, dangereux ! le destructeur de Client n'est pas appelé ! Vraiment ?
  cout << endl;

  cout << "----- 2.5 Test de cin et cout ----------------------------------------------" << endl;
  Competitor c2;
  cin >> c2;
  cout << c2 << endl;

  cout << "----- 2.6 Test de l'operateur d'affectation --------------------------------" << endl;
  Competitor c3;
  c3 = c2;
  cout << c3 << endl;
}

/******************************************************************************************/
void Essai3()
{
  srand((unsigned)time(NULL));

  cout << "----- 3.1 Allocation dynamique de personnes --------------------------------" << endl;
  Person* person[10];

  for (int i=0 ; i<10 ; i++)   // Tracez vos constructeurs !!!
  {
    cout << endl << "Person[" << i << "] :" << endl;
    int n = rand()%4;
    switch(n)
    {
      case 0 : person[i] = new Person();
	       break;

      case 1 : person[i] = new Competitor();
               break;

      case 2 : person[i] = new FederationAdmin();
               break;

      case 3 : person[i] = new TeamMember();
               break;
    }
  }
  cout << endl;

  cout << "----- 3.2 Test de la methode NON VIRTUELLE affiche() (redefinie dans chaque classe heritee) -------" << endl;
  for (int i=0 ; i<10 ; i++)
  {
    cout << endl << "person[" << i << "] :" << endl;
    person[i]->affiche();
  }
  cout << endl;

  cout << "----- 3.3 Test de la methode VIRTUELLE getIdentification() (redefinie dans chaque classe heritee) -------" << endl;
  for (int i=0 ; i<10 ; i++)
  {
    cout << endl << "person[" << i << "] : " << person[i]->getIdentification() << endl;
  }
  cout << endl;

  cout << "----- 3.4 Liberation memoire ----------------------------------------------------------------------------" << endl;
  for (int i=0 ; i<10 ; i++) delete person[i];  // Tout se passe-t-il comme vous voulez ?
  // Pour etre plus precis, quid des destructeurs et de la virtualite ?
}

/*********************************************************************************************/
void Essai4()
{
  srand((unsigned)time(NULL));

  cout << "----- 4.1 Allocation dynamique de personnes --------------------------------" << endl;
  Person* person[10];

  for (int i=0 ; i<10 ; i++)   // Tracez vos constructeurs !!!
  {
    cout << endl << "Person[" << i << "] :" << endl;
    int n = rand()%3;
    switch(n)
    {
      case 0 : person[i] = new Competitor();
               break;

      case 1 : person[i] = new FederationAdmin();
               break;

      case 2 : person[i] = new TeamMember();
               break;
    }
  }
  cout << endl;

  cout << "----- 4.2 Test du downcasting et dynamic-cast ------------------------------" << endl;
  for (int i=0 ; i<10 ; i++)
  {
    cout << "Person[" << i << "] ";
    Competitor* pCompetitor = dynamic_cast<Competitor*>(person[i]);
    if (pCompetitor != NULL) cout << "est un Competitor" << endl;

    // A COMPLETER !!! pour FederationAdmin et TeamMember

  }
  cout << endl;
}


