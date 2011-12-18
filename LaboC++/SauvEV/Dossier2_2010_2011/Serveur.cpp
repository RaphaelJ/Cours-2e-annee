/* Processus serveur 
   Denys Mercenier
   Serveur.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define    SERVEUR

#include "Fichier.ini"
#include "Ecran.h"

void Handler(int);
void HandlerFinSession(int);
void UpDate();

int             idFils;
int             idQ;
FILE            *hfErr;

char *NomProcess =  "SERVEUR";
char	FichConcert[30];
char	Queue[10];

int main()
{
int             hdIn,hdOut;

/* Attachement au groupe du csh */
if (setpgid(0,getppid()) == -1)
   { Trace("Err. d'attachement au groupe du csh");
     exit(1);
   }

if ((idFils = fork()) == -1)
   { Trace("Err. de fork()");
     exit(1);
   }

if (idFils)
   { /* Processus pere */
     exit(0);
   }

// Creation des ressources
Trace("Creation des ressources");
// a l'aide des fonctions du dossier1
strcpy(Queue,"1234");
if ((idQ = msgget((key_t)atoi(Queue),IPC_CREAT|IPC_EXCL|0600)) == -1)
   { Trace("Message queue non cree (READQ)");
     exit(1);
   }
strcpy(FichConcert,"Concert.dat");
int	hdFichConcert;
if ((hdFichConcert = open(FichConcert,O_RDWR)) == -1)
    { TraceErreur("Erreur d'ouverture");
      exit(1);
    }
sprintf(FichConcert,"%d",hdFichConcert);

/* Ouverture du fichier Trace.log */

if ((hfErr = fopen("Trace.log","w")) == (FILE *)NULL)
   { TraceErreur("Err. d'ouverture du fichier Erreur.log",1);
     exit(1);
   }
Trace("FichierTrace cree");
if (dup2(fileno(hfErr),2) == -1)
   { TraceErreur("(Ddms) Err. de dup2()",1);
     exit(1);
   }

Trace("Debut du Serveur");

/* Lancement du processus Publicite */
/* ... */

UpDate();

/* Fermeture des fichiers et effacement des ipc */
(void) msgctl(idQ,IPC_RMID,0);

kill(-idFils,SIGINT);
exit(0);

}

void UpDate()
{
int           rc;
int           hdF;
pid_t         idPid;
char          Donnee[96];
int           LongueurDonnee;
char          szQueueR[10],szQueueW[10];
DEMANDE		D ;

struct sigaction     Action;

sigemptyset(&Action.sa_mask);
Action.sa_flags = 0;

Action.sa_handler = HandlerFinSession;
if (sigaction(SIGHUP,&Action,NULL) == -1) 
   { TraceErreur("Err. signal SIGHUP",1);
     return;
   }

Action.sa_handler = Handler;
if (sigaction(SIGINT,&Action,NULL) == -1) 
   { TraceErreur("Err. signal SIGHUP",1);
     return;
   }
if (sigaction(SIGQUIT,&Action,NULL) == -1) 
   { TraceErreur("Err. signal SIGHUP",1);
     return;
   }

sprintf(szQueueR,"%d",idQ);

Trace("Serveur dans fonction");

while (1)
   { idPid = 1;
Trace("Serveur dans boucle");
     if ((rc = msgrcv(idQ,&D,sizeof(D) - sizeof(long),idPid,0)) == -1)
        { TraceErreur("Erreur de Recieve()sur ...");
          return;
        }
     Trace("Reception d'une commande %d",D.Request);
     switch(D.Request)
        { //case NOUVELLEBORNE:
          //    break;
          case CONSULT:
              Trace(" Reception d'un CONSULT.");
              if ((idFils = fork()) == -1) 
                 { TraceErreur("Err. de fork()... (CONSULT)");
                   return;
                 }
              if (!idFils)
                 { /* processus fils */
                   execlp("Reservation","Reservation",szQueueR,FichConcert,NULL);
                   { TraceErreur("Err de Creation de Reservation...",1);
                   return;
                 }
                 }
              D.lType = idFils;
Trace( "id fils %d",D.lType);
              if (msgsnd(idQ,&D,sizeof(D),0) == -1)
                 { TraceErreur("Erreur de Send()...(CONSULT)",1);
                   return;
                 }
              break;

          default : Trace("Requete non connue...");
              break;
        }
   }
}

void Handler(int Sig)
{
Trace("Reception du signal %d",Sig);
(void) msgctl(idQ,IPC_RMID,0);
}

void HandlerFinSession(int Sig)
{
Trace("Fin du SERVEUR du a la cloture de la session...");
(void) msgctl(idQ,IPC_RMID,0);
}
