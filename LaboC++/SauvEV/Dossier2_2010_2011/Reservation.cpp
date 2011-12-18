/* Processu qui s'occupe de la reservation
   Denys MERCENIER
   Reservation.c
*/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "Fichier.ini"
#include "Ecran.h"

char *NomProcess = "\tRESERVATION";

int         idQ;

char        Donnee[250];
int         LongueurDonnee;

CONCERT    Element;

int main(int argc,char *argv[])
{
int         rc;
int         idPid,hdFich;
MSCONCERT	C;
DEMANDE		D;
 
idPid = getpid();

idQ = atoi(argv[1]);

hdFich = atoi(argv[2]);

if ((rc = msgrcv(idQ,&C,sizeof(C) - sizeof(long),getpid(),0)) < 0)
   { TraceErreur("Erreur de Recieve()sur %d",idQ);
     return 1;
   }

Trace("MessageRecu");
if (lseek(hdFich, 0,0) == -1) 
   { Trace("\t(Reservation) Erreur de lseek()");
     return 1;
   }
int i = 0;
while (read(hdFich,&C.Concert[i],sizeof(CONCERT)) > 0)
     i++;
Trace("Nombre de concerts : %d",i);

Trace("Renvoie a %d",C.idProcess);
C.lType = C.idProcess;
C.idProcess = getpid();
if (msgsnd(idQ,&C,i * sizeof(CONCERT) + sizeof(pid_t) +sizeof(int),0) ==  -1)
   { TraceErreur("Erreur de Send() ...(%d)",C.lType);
     return 1;
   }

idPid = getpid();
D.lType = getpid();
D.idProcess = getpid();

Trace("attend");
if ((rc = msgrcv(idQ,&D,sizeof(D) - sizeof(long),getpid(),0)) < 0)
   { TraceErreur("Erreur de Recieve()sur %d",idQ);
     return 1;
   }

if (D.Request == ANNULER) exit(0);

Trace("recu message concert %d  nbplaces %d",D.Message[0],D.Message[1]);
lseek(hdFich,(D.Message[0] - 1)* sizeof(CONCERT),SEEK_SET);
if(read(hdFich,&Element,sizeof(CONCERT)) < 0) exit(1);


// verifier si stock correcte
// ...
// Attend une confirmation
///...

int	S1 = D.Message[0] - 1,S2 = D.Message[1];

if (D.Request == ANNULER) exit(0);

Trace("Nouveau stock avant%d",Element.Libre);
Element.Libre -= S2;
Trace("stock apres  %d",Element.Libre);
lseek(hdFich,S1* sizeof(CONCERT),SEEK_SET);
write(hdFich,&Element,sizeof(CONCERT));
Trace("fin ");
exit(0);
}
