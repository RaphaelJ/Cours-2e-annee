#include <qapplication.h>
#include "FenetreSaisie.h"

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Fichier.ini"
#include "FonctionUtile.h"

int	idQ;

FenetreSaisie     *F1;

int main(int argc, char *argv[])
{
Trace("Debut de l'application");
if ((idQ = msgget(CLE,0)) == -1)
   { perror("Erreur");
     exit(1);
   }

QApplication appl(argc,argv);

F1 = new FenetreSaisie();
F1->show();

return appl.exec();
}

