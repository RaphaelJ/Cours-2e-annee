#include <qapplication.h>
#include "BorneReservation.h"

#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include "Fichier.ini"
#include "Ecran.h"

int		idQ;
int      idReservation = 0;

char	*NomProcess = "Main";


void Alerte(int);
void NouvellePub(int);
BorneReservation *Connect;

int main( int argc, char **argv )
{
struct sigaction Action;
char    Queue[10];

printf("id : %d\n",getpid());

Action.sa_handler = Alerte;
sigemptyset(&Action.sa_mask);
Action.sa_flags = 0;

sigaction(SIGALRM,&Action,NULL);

Action.sa_handler = NouvellePub;
sigaction(SIGUSR1,&Action,NULL);

// a l'aide des fonctions du dossier1
strcpy(Queue,"1234");
if ((idQ = msgget((key_t)atoi(Queue),0)) == -1)
   { TraceErreur("Message queue non cree (READQ)");
     exit(1);
   }

    QApplication a( argc, argv );
    Connect = new BorneReservation();
    //a.setMainWidget( connect );
    Connect->show();
    return a.exec();
}

void Alerte(int Sig)
{
printf("Recetion d'un SIGALRM\n");
Connect->AffichageMenu("1 - Concert\n2 - Theatre\n3 - Restaurant");

return;
}

void NouvellePub(int Sig)
{
static int i = 0;
char *Tab[] = {"\nNotes UNIX disponibles chez DEFI",
               "\nN'OUBLIEZ PAS DE TRAVAILLER",
               "\nIl y a un examen en Janvier",
               "\nBon courage"};

if (i == 4) i = 0;
Connect->AffichagePublicite(Tab [i]);
i++;
return;
}

