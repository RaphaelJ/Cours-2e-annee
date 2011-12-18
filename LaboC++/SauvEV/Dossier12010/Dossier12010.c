nclude <stdio.h>
#include <unistd.h>

#include "AccesFichier.h"

FICHIER         F1;

int main()
{
printf("Debut de Dossier\n");
if (Ouverture(&F1,"Fichier.ini"))
   { perror("Err de Ouverture()");
     exit(1);
   }

Liste(F1);
if (Ajout(F1,"A","aaaa1"))
   { perror("Err de Ajout(Mercenier)");
     exit(1);
   }
Liste(F1);
if (Ajout(F1,"BBBBBBBB","bbbbbbbb2"))
   { perror("Err de Ajout(Mercenier)");
     exit(1);
   }
Liste(F1);
if (Ajout(F1,"CC","cc3"))
   { perror("Err de Ajout(Mercenier)");
     exit(1);
   }
Liste(F1);
if (Ajout(F1,"DDDDDD","ddddd4"))
   { perror("Err de Ajout(Mercenier)");
     exit(1);
   }
Liste(F1);
if (Ajout(F1,"E","E5"))
   { perror("Err de Ajout(Mercenier)");
     exit(1);
   }
Liste(F1);

if (Fermeture(F1))
   { perror("Err de Fermeture()");
     exit(1);
   }
}
