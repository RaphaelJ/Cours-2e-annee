#include "FenetreCodePostal.h"
#include <qapplication.h>


#include "FichierIndex.h"

FICHIERINDEX	F1;

int main(int argc, char *argv[])
{
F1.Taille = 120;
F1.Offset = 4;

if (FIOuverture(&F1,"CodePostalTrieCompletSUN") == -1)
   { perror("--");
     exit(1);
   }

QApplication appl(argc,argv);

RechercheCodesPostaux     F1;
F1.show();

return appl.exec();
}

