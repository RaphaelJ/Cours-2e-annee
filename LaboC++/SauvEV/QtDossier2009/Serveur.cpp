#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "FonctionUtile.h"
#include "FichierIndex.h"

#include "Fichier.ini"

void Sortie(int);

int	idQ;
FICHIER F1;
LIVRE	Livre;

int main(int argc,char *argv[])
{
MESSAGE 	M;
MESSAGELIVRE 	M1;
int		rc;
int		idFils;

F1.Taille = 132;
F1.Offset = 64;

if (FIOuverture(&F1,"StockLivreSUN.dat") == -1)
   { perror("Erreur de FIOuverture()");
     exit(1);
   }


if ((idQ = msgget(CLE,IPC_CREAT | 0600)) == -1)
   { perror("Erreur de msgget() ");
     exit(1);
   }

while (1)
   { if (msgrcv(idQ,&M,sizeof(M),1,0) == -1)
        { perror("Erreur de msgrcv");
          Sortie(1);
        }
     Trace("(Serveur)         : %s",M.N);
     Trace("(Serveur) idP     : %d",M.Pid);
     Trace("(Serveur) requete : %d",M.Requete);

     switch(M.Requete)
       { case RECHERCHE:
            if ((idFils = fork()) == -1)
               { perror("Erreur de fork()");
                 exit(1);
               }
            if (!idFils)
               { // processus fils
	         char BuffIdQ[10],BuffhdFD[10],BuffhdFI[10],BuffT[10];
                 sprintf(BuffIdQ,"%d",idQ);
                 sprintf(BuffhdFD,"%d",F1.hdFichierData);
                 sprintf(BuffhdFI,"%d",F1.hdFichierIndex);
                 sprintf(BuffT,"%d",F1.Taille);
                 execlp("AccesFichier","AccesFichier",BuffIdQ,
                          BuffhdFD,BuffhdFI,BuffT,NULL);
                 perror("Erreur de execlp()");
                 exit(1);
               }
            M.Type = idFils;
            if (msgsnd(idQ,&M,sizeof(M) - sizeof(long),0) == -1)
               { Trace("(Serveur) Erreur de msgsnd(RECHERCHE)");
                 perror("");
                 exit(1);
               }
            break; 
         case IDENTIFICATION:
            M.Type = M.Pid;
            strcpy(M.N,"Inconnu\npriere de vous identifier\n");
            if (msgsnd(idQ,&M,sizeof(M) - sizeof(long),0) == -1)
               { Trace("(Serveur) Erreur de msgsnd(IDENTIFICATION)");
                 perror("");
                 exit(1);
               }
            break;
         default:
            break;
       }
   }

exit(0);
}

void Sortie(int Code)
{
exit(Code);
}
