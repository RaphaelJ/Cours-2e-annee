#include <stdlib.h>
#include <iostream>

#include "Circuits/Circuit.h"

int main()
{
  Circuit c, c1("Belgique","Spa_Francorchamps",7.004);
  Circuit c2(Circuit::SILVERSTONE);
  Circuit c3(c1);
  Circuit total;
  
  float longueur;
  
  cout << endl << "(1) ***** Test de l'opérateur d'affectation *****" << endl;
  c = c1;
  c1.affiche();
  cout << endl;  
  c.affiche();
  cout << endl << endl;

  cout << "(2) ***** Test de l'operateur + --> c3 = c2 + 0.5 *****" << endl;
  c3 = c2 + 0.5;
  cout << "--> Voici c3 :" << endl;
  c3.affiche();
  cout << endl;
  cout << "--> Montrons que c2 n'a pas change :" << endl;
  c2.affiche();
  cout << endl << endl;

  cout << "(3) ***** Test de l'operateur + --> c1 = c1 + 0.25 *****" << endl;
  cout << "--> Voici c1 avant : ";
  c1.affiche();
  cout << endl;
  c1 = c1 + 0.25;
  cout << "--> Voici c1 apres : ";
  c1.affiche();
  cout << endl << endl;

  cout << "(4) ***** Test de l'operateur - --> c3 = c2 - 1.25 *****" << endl;
  c3 = c2 - 1.25;
  cout << "--> Voici c3 :";
  c3.affiche();
  cout << endl;
  cout << "--> Montrons que c2 n'a pas change :";
  c2.affiche();
  cout << endl << endl; 

  cout << "(5) ***** Test de l'operateur + --> c = c1 + c2 *****" << endl;
  cout << "--> Pour rappel, voici c1 :";
  c1.affiche();
  cout << endl;
  cout << "--> Pour rappel, voici c2 :";
  c2.affiche();
  cout << endl;
  c = (c1 + c2);
  cout << "--> et voici c : ";
  c.affiche();
  cout << endl << "--> Montrons que c1 et c2 n'ont pas change :" << endl;
  cout << "--> c1 : ";
  c1.affiche();
  cout << endl;
  cout << "--> c2 : ";
  c2.affiche();  
  cout << endl << endl;

  cout << "(6) ***** Test de l'operateur - --> longueur = c - c2 *****" << endl;
  cout << "--> Pour rappel, voici c :";
  c.affiche();
  cout << endl;
  cout << "--> Pour rappel, voici c2 :";
  c2.affiche();
  cout << endl;
  longueur = c - c2;
  cout << "--> et voici longueur = " << longueur << " km" << endl;
  cout << "--> Montrons que c et c2 n'ont pas change :" << endl;
  cout << "--> c : ";
  c.affiche();
  cout << endl;
  cout << "--> c2 : ";
  c2.affiche();  
  cout << endl << endl;

  cout << "(7) ***** Test de l'opérateur << *****" << endl;
  cout << "--> Affichons c    : " << c << endl;
  cout << "--> Affichons c2   : " << c2 << endl;
  cout << "--> Affichons c+c2 : " << c+c2 << endl << endl;

  cout << "(8) ***** Test de total = c1 + c2 + c3 *****" << endl;
  cout << "c1 : " << c1 << endl;
  cout << "c2 : " << c2 << endl;
  cout << "c3 : " << c3 << endl;
  total = c1 + c2 + c3;
  cout << "Total : " << total << endl << endl;

  cout << "(9) ***** Test des operateurs de comparaison < > *****" << endl;
  cout << "--> c2 = " << c2 << endl;
  cout << "--> c3 = " << c3 << endl;
  if (c2 < c3) cout << "Le circuit c2 est plus petit que c3" << endl;
  if (c2 > c3) cout << "Le circuit c2 est plus grand que c3" << endl; 
  cout << endl; 

  cout << "(10) ***** Test de l'operateur de pre-incrementation *****" << endl;
  cout << "--> Affichons d'abord c :" << c << endl;
  cout << "--> Resultat de cout << ++c << endl; :" << endl;  
  cout << ++c << endl;        // Si tout va bien, c est incremente avant d'etre affiche !
  cout << "--> et on reaffiche c :" << endl;
  cout << c << endl <<  endl;

  cout << "(11) ***** Test de l'operateur de post-incrementation *****" << endl;
  cout << "--> Affichons d'abord c2 :" << c2 << endl;
  cout << "--> Resultat de cout << c2++ << endl; :" << endl;  
  cout << c2++ << endl;        // Si tout va bien, c2 est incremente apres avoir ete affiche !
  cout << "--> et on reaffiche c2 :" << endl;
  cout << c2 << endl <<  endl;

  return 0;
}


