#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "FichierIndex.h"
#include "FonctionUtile.h"

#include "Fichier.ini"

MESSAGE		M;
MESSAGELIVRE	M1;

int		idQ;
FICHIER		F1;

int main(int argc,char *argv[])
{
int		rc;

Trace("\t(AccesFichier) Debut de AccesFichier");
idQ = atoi(argv[1]);

F1.hdFichierData = atoi(argv[2]);
F1.hdFichierIndex = atoi(argv[3]);
F1.Taille = atoi(argv[4]);

if (msgrcv(idQ,&M,sizeof(M),getpid(),0) == -1)
   { Trace("(AccesFichier) Err de msgrcv()");
     perror("");
     exit(1);
   }
Trace("\t(AccesFichier) Message recu");

if ((rc = FIConsultation(F1,M.N,M1.L)) == -1)
   { perror("Erreur de FIConsultation()");
     exit(1);
   }

M1.Type = M.Pid;
M1.Requete = rc;
if (msgsnd(idQ,&M1,sizeof(M1),0) == -1) 
   { Trace("(AccesFichier) Err de msgsnd()");
     exit(1);
   }
Trace("\t(ACCESFICHIER) %s",M1.L[0].Titre);
exit(0);
}
