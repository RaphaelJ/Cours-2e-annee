#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include "Ecran.h"
#include "EcranX.h"
#include "Grille.h"

//****************************************************************
#define KEY_DOWN   50
#define KEY_UP     51
#define KEY_LEFT   52
#define KEY_RIGHT  53

struct termios Term,SaveTerm;
int  ReadChar();
int  SortieIoctl(int);

GRILLE grilleTetris;
GRILLE grilleSuivant;
void   cleanGrille();
//****************************************************************

#define NB_LIGNE 20
#define NB_COLONNE 9

#define VIDE  1
#define FORME 100

int tab[NB_LIGNE][NB_COLONNE];

typedef struct
{
  int L[4];
  int C[4];
  int couleur;
} S_FORME;

S_FORME Forme[7];

typedef struct
{
   int numLigne;
   int compteur;
} S_LIGNE;

/*************************************************************************/
struct timespec deltaT;
struct sigaction sigAct;

int haut = 0;
int gauche = 0;
int droite = 0;
int rotation = 0;
int scores = 0;
int lignes = 0;
int niveau = 1;
int threadPause = 0;
int partieEnCours;
int cptLigne;
char MAJScores;
char MAJLignes;
int maxL = 0;
int minL = 0;
int cptMax = 0;
int cptMin = NB_LIGNE;

void initFormes (void);
void initAff(void);
void affScore (void);
void affLigne (void);
void affNiveau (void);
void move_left (S_FORME* forme);
void move_right (S_FORME* forme);
void move_down (S_FORME* forme);
void fctThreadClavierFin(void *p);
void handlerThreadLigne(int sig);
void handlerThreadShift(int sig);

pthread_key_t cle;

pthread_t threadForme;
pthread_t threadTimer;
pthread_t threadClavier;
pthread_t threadGenForme;
pthread_t threadLigne[NB_LIGNE];
pthread_t threadScores;
pthread_t threadShift;

void* fctThreadForme(void* param);
void* fctThreadTimer(void* param);
void* fctThreadClavier(void* param);
void* fctThreadGenForme(void* param);
void* fctThreadLigne(void* param);
void* fctThreadScores(void* param);
void* fctThreadShift(void* param);

pthread_mutex_t mutexEvent;
pthread_mutex_t mutexGrille;
pthread_mutex_t mutexTimer;
pthread_mutex_t mutexLigne;
pthread_mutex_t mutexScores;
pthread_mutex_t mutexPause;

pthread_cond_t condEvent;
pthread_cond_t condLigne;
pthread_cond_t condScores;
pthread_cond_t condPause;


/*************************************************************************/
int main(void)
{
   srand((unsigned)time(NULL));
  
   initFormes();
   
   printf("Ouverture de la grille de jeu...\n");
   if (OuvrirGrille(&grilleTetris,NB_LIGNE,NB_COLONNE,30,"Tetris") == -1)
      {
         perror("Erreur de InitGrille");
         exit(-1);
      }
   cleanGrille();
   if (OuvrirGrille(&grilleSuivant,4,NB_COLONNE,30,"Forme Suivante") == -1)
      {
         perror("Erreur de InitGrille");
         exit(-1);
      }

   pthread_mutex_init(&mutexEvent, NULL);
   pthread_cond_init(&condEvent, NULL);
   pthread_mutex_init(&mutexTimer, NULL);
   pthread_mutex_init(&mutexLigne, NULL);
   pthread_cond_init(&condLigne, NULL);
   pthread_mutex_init(&mutexScores, NULL);
   pthread_cond_init(&condScores, NULL);
   pthread_mutex_init(&mutexPause, NULL);
   pthread_cond_init(&condPause, NULL);
	   
   partieEnCours = 1;
   deltaT.tv_sec = 0;
   deltaT.tv_nsec = 500000000;
	
   sigfillset(&sigAct.sa_mask);
   sigAct.sa_handler = handlerThreadLigne;
   sigaction(SIGUSR1, &sigAct, NULL);
   sigaction(SIGALRM, &sigAct, NULL);
   sigaction(SIGUSR2, &sigAct, NULL);

   /** Creation de la cle **/
   if (pthread_key_create(&cle, NULL))
      fprintf(stderr, "Erreur de creation de la cle\n");

   /** Lancement des threads ligne **/
   int i;
   for (i = 0; i < NB_LIGNE; i++)
      {
         pthread_create(&threadLigne[i], NULL, fctThreadLigne, &i);
      }

   if(pthread_create(&threadScores, NULL, fctThreadScores, NULL))
      fprintf(stderr, "Erreur de creation du thread scores\n");

   if(pthread_create(&threadTimer, NULL, fctThreadTimer, NULL))
      fprintf(stderr, "Erreur de creation du thread timer\n");

   if(pthread_create(&threadClavier, NULL, fctThreadClavier, NULL))
      fprintf(stderr, "Erreur de creation du thread clavier\n");

   if(pthread_create(&threadShift, NULL, fctThreadShift, NULL))
      fprintf(stderr, "Erreur de creation du thread shift\n");

   
   system("clear");
   initAff();

   if(pthread_create(&threadGenForme, NULL, fctThreadGenForme, NULL))
      fprintf(stderr, "Erreur de creation du thread generateur de forme\n");
   
   pthread_join(threadGenForme, NULL);
	
   pthread_mutex_destroy(&mutexEvent);
   pthread_cond_destroy(&condEvent);
   pthread_mutex_destroy(&mutexTimer);
   pthread_mutex_destroy(&mutexLigne);
   pthread_cond_destroy(&condLigne);
   pthread_mutex_destroy(&mutexScores);
   pthread_cond_destroy(&condScores);
   pthread_mutex_destroy(&mutexPause);
   pthread_cond_destroy(&condPause);

   pthread_key_delete(cle);
   
   /********************************************************************/
   printf("Fermeture de la grille de jeu...\n");
   getchar();
   fflush(stdout);
   FermerGrille(&grilleTetris);
   FermerGrille(&grilleSuivant);
   
   if (tcsetattr(0,TCSANOW,&SaveTerm) == -1) exit(1);
   
   //exit(0);
   return 0;
}


/*************************************************************************/
/********** Initialise la grille ***** ***********************************/
/*************************************************************************/
void cleanGrille()
{
   int i, j;
   pthread_mutex_lock(&mutexGrille);
   for (i = 0 ; i<NB_LIGNE ; i++)
      {
         for (j = 0 ; j<NB_COLONNE ; j++)
            {
               tab[i][j] = VIDE;
               DessineCarre(&grilleTetris,i,j,BLANC);
            }
      }
   pthread_mutex_unlock(&mutexGrille);
}

/*************************************************************************/
/***** Fonctions de gestion du clavier ***********************************/
/*************************************************************************/
int ReadChar()
{
   char ChLu;
   
   if (tcgetattr(0,&Term) == -1) return -1;
   SaveTerm = Term;
   Term.c_lflag &= ~(ICANON | ECHO | ISIG);
   Term.c_cc[VMIN] = 1;
   
   if (tcsetattr(0,TCSANOW,&Term) == -1) return -1;
   
   fflush(stdin);
   
   if (read(0,&ChLu,1) != 1) return SortieIoctl(-1);
   if (ChLu == Term.c_cc[VINTR]) return SortieIoctl(3);
   if (ChLu == '\033')
      {
         if (read(0,&ChLu,1) == 1)
            {
               if ((char)ChLu == '[')
                  {
                     if (read(0,&ChLu,1) != 1) return SortieIoctl(-1);
                     if ((char)ChLu == 'A') return SortieIoctl(KEY_UP);
                     if ((char)ChLu == 'B') return SortieIoctl(KEY_DOWN);
                     if ((char)ChLu == 'C') return SortieIoctl(KEY_RIGHT);
                     if ((char)ChLu == 'D') return SortieIoctl(KEY_LEFT);   
                     return SortieIoctl(-1);
                  }          
            }
      }
   
   return SortieIoctl(ChLu);
} 

int SortieIoctl(int Code)
{
   if (tcsetattr(0,TCSANOW,&SaveTerm) == -1) return -1;
   return Code;
} 

void initFormes (void)
{
   int L0,C0;
   C0 = NB_COLONNE/2;
   L0 = NB_LIGNE - 1;
   
   // L premier sens
   Forme[0].C[0] = C0;
   Forme[0].L[0] = L0;
   Forme[0].C[1] = C0 - 1;
   Forme[0].L[1] = L0;
   Forme[0].C[2] = C0 + 1;
   Forme[0].L[2] = L0;
   Forme[0].C[3] = C0 + 1;
   Forme[0].L[3] = L0 - 1;
   Forme[0].couleur = ROUGE;
   
   // L second sens
   Forme[1].C[0] = C0;
   Forme[1].L[0] = L0;
   Forme[1].C[1] = C0 - 1;
   Forme[1].L[1] = L0;
   Forme[1].C[2] = C0 + 1;
   Forme[1].L[2] = L0;
   Forme[1].C[3] = C0 - 1;
   Forme[1].L[3] = L0 - 1;
   Forme[1].couleur = VERT;
   
   // S premier sens
   Forme[2].C[0] = C0;
   Forme[2].L[0] = L0;
   Forme[2].C[1] = C0 + 1;
   Forme[2].L[1] = L0;
   Forme[2].C[2] = C0;
   Forme[2].L[2] = L0 - 1;
   Forme[2].C[3] = C0 - 1;
   Forme[2].L[3] = L0 - 1;
   Forme[2].couleur = BLEU;
   
   // S second sens
   Forme[3].C[0] = C0;
   Forme[3].L[0] = L0;
   Forme[3].C[1] = C0 - 1;
   Forme[3].L[1] = L0;
   Forme[3].C[2] = C0;
   Forme[3].L[2] = L0 - 1;
   Forme[3].C[3] = C0 + 1;
   Forme[3].L[3] = L0 - 1;
   Forme[3].couleur = JAUNE;
   
   // T
   Forme[4].C[0] = C0;
   Forme[4].L[0] = L0;
   Forme[4].C[1] = C0 + 1;
   Forme[4].L[1] = L0;
   Forme[4].C[2] = C0;
   Forme[4].L[2] = L0 - 1;
   Forme[4].C[3] = C0 + 1;
   Forme[4].L[3] = L0 - 1;
   Forme[4].couleur = CYAN;
   
   // Carre
   Forme[5].C[0] = C0;
   Forme[5].L[0] = L0;
   Forme[5].C[1] = C0 + 1;
   Forme[5].L[1] = L0;
   Forme[5].C[2] = C0 - 1; 
   Forme[5].L[2] = L0;
   Forme[5].C[3] = C0;
   Forme[5].L[3] = L0 - 1;
   Forme[5].couleur = MAGENTA;
   
   // Ligne
   Forme[6].C[0] = C0;
   Forme[6].L[0] = L0;
   Forme[6].C[1] = C0 - 1;
   Forme[6].L[1] = L0;
   Forme[6].C[2] = C0 + 1; 
   Forme[6].L[2] = L0;
   Forme[6].C[3] = C0 + 2;
   Forme[6].L[3] = L0;
   Forme[6].couleur = BRUN;
}

void* fctThreadForme(void* param)
{
   S_FORME *forme;
   forme = (S_FORME *)param;
   int i;
   int move = 1;
   while(move == 1)
      {
         pthread_mutex_lock(&mutexEvent);
         pthread_mutex_lock(&mutexGrille);
         while (haut == 0 && gauche == 0 && droite == 0 && rotation == 0)
            pthread_cond_wait(&condEvent, &mutexEvent);
         move = 1;
         if(haut > 0)
            {
               for (i = 0; i < 4; i++)
                  {
                     if(forme->L[i]-1 > -1)
			{
                           if(tab[forme->L[i]-1][forme->C[i]] != VIDE && 
                              tab[forme->L[i]-1][forme->C[i]] != FORME)
                              move = 0;
			}
                     else
			move = 0;
                  }
               if(move == 1)
                  {
                     for (i = 0; i < 4; i++)
			{
			 
                           DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
			   tab[forme->L[i]][forme->C[i]] = VIDE;
                           forme->L[i] = forme->L[i] - 1;

                        }
                     haut--;
                     for (i = 0; i < 4; i++)
                        {
                           DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
                           tab[forme->L[i]][forme->C[i]] = FORME;
                        }
                  }
               else
                  {	
                     for (i = 0; i < 4; i++)
			{
                           if(tab[NB_LIGNE-1][forme->C[i]] != VIDE)
                              {
                                 AffChaine("Jeu termine ...", 12, 4, 0);
                                 partieEnCours = 0;
                              }
                           tab[forme->L[i]][forme->C[i]] = forme->couleur;
			}
                  }
            }
         if(gauche > 0)
            {
               move_left(forme);
               gauche--;
            }
         if(droite > 0)
            {
               move_right(forme);
               droite--;
            }
         if(rotation > 0) 
            {
               move_down(forme);
               rotation--;
            }
         pthread_mutex_unlock(&mutexEvent);
         pthread_mutex_unlock(&mutexGrille);
      }
   pthread_exit(NULL);
}

void* fctThreadTimer (void* param)
{
   param = NULL;

   while(1)
      {
         pthread_mutex_lock(&mutexPause);
         while(threadPause == 1)
            pthread_cond_wait(&condPause, &mutexPause);
         pthread_mutex_unlock(&mutexPause);
         pthread_mutex_lock(&mutexEvent);
         haut++;
         pthread_mutex_unlock(&mutexEvent);
         pthread_cond_signal(&condEvent);
         pthread_mutex_lock(&mutexTimer);
         nanosleep(&deltaT, NULL);
         pthread_mutex_unlock(&mutexTimer);
      }
      
   pthread_exit(NULL);
}

void* fctThreadClavier (void* param)
{
   param = NULL;
   pthread_cleanup_push(fctThreadClavierFin, 0);
   int token;
   while(1)
      {
         token = ReadChar();
         switch (token)
            {
            case KEY_UP :
               pthread_mutex_lock(&mutexPause);
               while(threadPause == 1)
                  pthread_cond_wait(&condPause, &mutexPause);
               pthread_mutex_unlock(&mutexPause);
               pthread_mutex_lock(&mutexEvent);
               haut = 19;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case KEY_DOWN :
               pthread_mutex_lock(&mutexPause);
               while(threadPause == 1)
                  pthread_cond_wait(&condPause, &mutexPause);
               pthread_mutex_unlock(&mutexPause);               
               pthread_mutex_lock(&mutexEvent);
               rotation++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case KEY_LEFT :
               pthread_mutex_lock(&mutexPause);
               while(threadPause == 1)
                  pthread_cond_wait(&condPause, &mutexPause);
               pthread_mutex_unlock(&mutexPause);
               pthread_mutex_lock(&mutexEvent);
               gauche++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);        
               break;
            case KEY_RIGHT :
               pthread_mutex_lock(&mutexPause);
               while(threadPause == 1)
                  pthread_cond_wait(&condPause, &mutexPause);
               pthread_mutex_unlock(&mutexPause);
               pthread_mutex_lock(&mutexEvent);
               droite++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case 'p':
               pthread_mutex_lock(&mutexPause);
               if(threadPause == 1)
                  {
                     AffChaine("                ", 10, 4, 0);
                     threadPause = 0;
                     pthread_cond_signal(&condPause);
                     pthread_cond_signal(&condPause);
                     pthread_cond_signal(&condPause);
                     pthread_cond_signal(&condPause);
                     pthread_cond_signal(&condPause);
                     pthread_cond_signal(&condPause);
                     pthread_cond_signal(&condPause);
                  }
               else
                  {
                     AffChaine("Jeu en pause ...", 10, 4, 0);
                     threadPause = 1;
                  }
               pthread_mutex_unlock(&mutexPause);
               break;
            default:
               system("clear");
               affScore();
               affLigne();
               affNiveau();
               if(threadPause == 1)
                  AffChaine("Jeu en pause ...", 10, 4, 0);
               break;	
            }
      }
   pthread_cleanup_pop(1);
   pthread_exit(NULL);
}

void fctThreadClavierFin(void *p)
{
   p = NULL;
   tcsetattr(0,TCSANOW,&SaveTerm);
}

void move_left (S_FORME* forme)
{
   int i;
   int move = 1;
   for (i = 0; i < 4; i++)
      {
         if(forme->C[i] - 1 > -1)
            {
               if(tab[forme->L[i]][forme->C[i]-1] != VIDE &&
                  tab[forme->L[i]][forme->C[i]-1] != FORME)
                  move = 0; 
            }
         else
            {
               move = 0; 
               i = 5;
            }
      }
	
   if(move == 1)
      {
         for (i = 0; i < 4; i++)
            {
               DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
               tab[forme->L[i]][forme->C[i]] = VIDE;
               forme->C[i] = forme->C[i] - 1;
            }
         for (i = 0; i < 4; i++)
            {
               DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
               tab[forme->L[i]][forme->C[i]] = FORME;
            }
      }
}

void move_right (S_FORME* forme)
{
   int i;
   int move = 1;
   for (i = 0; i < 4; i++)
      {
         if(forme->C[i] + 1 < NB_COLONNE)
            {
               if(tab[forme->L[i]][forme->C[i]+1] != VIDE &&
                  tab[forme->L[i]][forme->C[i]+1] != FORME)
                  move = 0; 
            }
         else
            {
               move = 0; 
               i = 5;
            }
      }
	
   if(move == 1)
      {
         for (i = 0; i < 4; i++)
            {
               DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
               tab[forme->L[i]][forme->C[i]] = VIDE;
               forme->C[i] = forme->C[i] + 1;
            }
         for (i = 0; i < 4; i++)
            {
               DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
               tab[forme->L[i]][forme->C[i]] = FORME;
            }
      }
}

void move_down (S_FORME* forme)
{
   int i, C, L, okL, okC, min, max, temp;
   for (i = 0 ; i < 4 ; i++)
      {
         DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
         tab[forme->L[i]][forme->C[i]] = VIDE;
      }
   C = forme->C[0];
   L = forme->L[0];
   okL = 0; okC = 0;
   min = 0; max = 0;
   for (i = 0 ; i < 4 ; i++) 
      {
         forme->C[i] = forme->C[i] - C;
         forme->L[i] = forme->L[i] - L;
         temp = forme->C[i];
         forme->C[i] = forme->L[i];
         forme->L[i] = temp * (-1);
         forme->C[i] = forme->C[i] + C;
         forme->L[i] = forme->L[i] + L;
         if(forme->L[i] > 19)
            okL = 1;
         if(forme->L[i] < 0)
            okL = -1;
         if(forme->C[i] > 8)
            {
               okC = 1;
               if(max < forme->C[i])
                  max = forme->C[i];
            }
         if(forme->C[i] < 0)
            {
               okC = -1;
               if(min > forme->C[i])
                  min = forme->C[i];
            }
      }
   if(okL == 1)
      {
         for(i = 0; i< 4; i++)
            forme->L[i] = forme->L[i] - 1;
      }
   if(okL == -1)
      {
         for(i = 0; i< 4; i++)
            forme->L[i] = forme->L[i] + 1;
      }
   if(okC == 1)
      {
         max = max - 8;
         for(i = 0; i< 4; i++)
            forme->C[i] = forme->C[i] - max;
      }
   if(okC == -1)
      {
         min = min * (-1);
         for(i = 0; i< 4; i++)
            forme->C[i] = forme->C[i] + min;
      }
   
   for(i = 0; i< 4; i++)
      {
         DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
         tab[forme->L[i]][forme->C[i]] = FORME;
      }
}

void* fctThreadGenForme (void* param)
{
   param = NULL;
   S_FORME *forme,*suivant;
   int i;
   int maxL;
   forme = (S_FORME*)malloc(sizeof(S_FORME));
   memcpy(forme,&Forme[rand()%7],sizeof(S_FORME));
   for (i = 0 ; i<4 ; i++) 
      DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
   
   suivant = (S_FORME*)malloc(sizeof(S_FORME));
   memcpy(suivant,&Forme[rand()%7],sizeof(S_FORME));
   for (i = 0 ; i<4 ; i++) 
      DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],suivant->couleur);
   while(partieEnCours == 1)
      {	
         pthread_mutex_lock(&mutexPause);
         while(threadPause == 1)
            pthread_cond_wait(&condPause, &mutexPause);
         pthread_mutex_unlock(&mutexPause);
         pthread_mutex_lock(&mutexEvent);
	 haut = 0;
         pthread_mutex_unlock(&mutexEvent);
         if(pthread_create(&threadForme, NULL, fctThreadForme, forme))
            fprintf(stderr, "Erreur de creation du thread forme\n");
         pthread_join(threadForme, NULL);

         maxL = 0;
         for(i = 0; i < 4; i++)
            {
               if(forme->L[i] > maxL)
                  maxL = forme->L[i];
            }

         cptLigne = 4;
         pthread_kill(threadLigne[maxL], SIGUSR1);
         pthread_mutex_lock(&mutexLigne);
         while(cptLigne != 0)
            pthread_cond_wait(&condLigne, &mutexLigne);
         pthread_mutex_unlock(&mutexLigne);
	
	
         pthread_mutex_lock(&mutexScores);
         scores++;
         MAJScores = 1;
         pthread_mutex_unlock(&mutexScores);
         pthread_cond_signal(&condScores);

         memcpy(forme,suivant,sizeof(S_FORME));
     
         pthread_mutex_lock(&mutexGrille);
         for (i = 0 ; i<4 ; i++) 
            DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],BLANC);
	 memcpy(suivant,&Forme[rand()%7],sizeof(S_FORME));
         for (i = 0 ; i<4 ; i++) 
            DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],suivant->couleur);
         pthread_mutex_unlock(&mutexGrille);
      }
   free(forme);
   free(suivant);
	
   pthread_exit(NULL);
}

void* fctThreadLigne (void* param)
{
   int* numLigne;
   S_LIGNE* ligne;
   ligne = malloc(sizeof(S_LIGNE));
   numLigne = param;
   ligne->numLigne = *numLigne; 
   ligne->compteur = 0;

   pthread_sigmask(SIG_UNBLOCK, &sigAct.sa_mask, NULL);
   pthread_setspecific(cle, ligne);
   while(partieEnCours == 1)
      {
         pause();
      }
	
   pthread_exit(NULL);
}

void handlerThreadLigne(int sig)
{
   int i, j, cpt;
   S_LIGNE *ligne;
   ligne = (S_LIGNE*) pthread_getspecific(cle);
	
   if(sig == SIGUSR1)
      {
         i = ligne->numLigne;
         pthread_mutex_lock(&mutexGrille);
         //verifie si la ligne est complete
         for (j = 0, cpt = 0; j < NB_COLONNE; j++)
            {
               if(grilleTetris.tab[i][j] != VIDE)
                  cpt++;
            }
         if(cpt == NB_COLONNE)
            {
        	
               
               //efface la ligne
               for (j = 0; j < NB_COLONNE; j++)
                  {
                     DessineCarre(&grilleTetris, i, j, BLANC);
                  }
               
               //decale les lignes
             
               for (i = ligne->numLigne; i < NB_LIGNE - 1; i++)
                  {
                     for(j = 0; j < NB_COLONNE; j++)
                        {
                           if(tab[i+1][j] != FORME)
                              {
                                 grilleTetris.tab[i][j] =  grilleTetris.tab[i+1][j];
                                 tab[i][j] = tab[i+1][j];
                              }
                        }
                   	  
                  }
          
               for (j = 0; j < NB_COLONNE; j++)
                  {
                     DessineCarre(&grilleTetris, NB_LIGNE - 1, j, BLANC);
                     tab[NB_LIGNE-1][j] = VIDE;
                  }

               //incremente son compteur
               ligne->compteur = ligne->compteur + 1;
		
               //mise a jour du score
               pthread_mutex_lock(&mutexScores);
               scores = scores + 10;
               lignes++;
               MAJLignes = 1;
               pthread_mutex_unlock(&mutexScores);
               pthread_cond_signal(&condScores);
               
            }
         pthread_mutex_lock(&mutexLigne);
               
               

         i = ligne->numLigne;
         if(i > 0 && cptLigne > 1)
            {
               pthread_kill(threadLigne[i-1], SIGUSR1);
            }
         cptLigne--;
         if(cptLigne == 0 || (cptLigne > 0 && i-1 < 0))
            {
               pthread_cond_signal(&condLigne);
               cptLigne = 0;
            }
         pthread_mutex_unlock(&mutexLigne);
         pthread_mutex_unlock(&mutexGrille);
      }
}

void affScore (void)
{
   char* temp;
   char* affTemp;
   temp = malloc(sizeof((char)scores));
   sprintf(&temp[0], "%d", scores);
   affTemp = malloc(sizeof("Score : ") + sizeof(temp));
   strcpy(affTemp, "Score : ");
   strcat(affTemp, temp);
   AffChaine(affTemp, 4, 4, 0);
		
}

void affNiveau (void)
{
   char* temp;
   char* affTemp;
   temp = malloc(sizeof((char)niveau));
   sprintf(temp, "%d", niveau);
   affTemp = malloc(sizeof("Niveau : ") + sizeof(temp));
   strcpy(affTemp, "Niveau : ");
   strcat(affTemp, temp);
   AffChaine(affTemp, 8, 4, 0);
}

void affLigne (void)
{
   char* temp;
   char* affTemp;
   temp = malloc(sizeof((char)lignes));
   sprintf(temp, "%d", lignes);
   affTemp = malloc(sizeof("Lignes : ") + sizeof(temp));
   strcpy(affTemp, "Lignes : ");
   strcat(affTemp, temp);
   AffChaine(affTemp, 6, 4, 0);
}

void* fctThreadScores(void* param)
{
   param = NULL;

   while(1)
      //while(partieEnCours == 1)
      {
         pthread_mutex_lock(&mutexScores);
         while (!MAJLignes && !MAJScores)
            pthread_cond_wait(&condScores, &mutexScores);
         pthread_mutex_unlock(&mutexScores);
         
         pthread_mutex_lock(&mutexScores);
         if (MAJScores == 1)
            {
               affScore();
               MAJScores--;
		
            }
         if (MAJLignes == 1)
            {
               lignes++;
               affLigne();
               if((lignes % 5 == 0) && (lignes != 0))
                  {
                     niveau++;
                     affNiveau();
                     long test;
                     test = deltaT.tv_nsec;
                     test = test - (test*0.2);
                     deltaT.tv_nsec = test;
                  }
               MAJLignes--;
            }
         pthread_mutex_unlock(&mutexScores);
      }
   pthread_exit(NULL);
}

void initAff(void)
{
   char* temp;
   char* affTemp;
   temp = malloc(sizeof((char)scores));
   sprintf(&temp[0], "%d", scores);
   affTemp = malloc(sizeof("Score : ") + sizeof(temp));
   strcpy(affTemp, "Score : ");
   strcat(affTemp, temp);
   AffChaine(affTemp, 4, 4, 0);
   
   temp = malloc(sizeof((char)lignes));
   sprintf(temp, "%d", lignes);
   affTemp = malloc(sizeof("Lignes : ") + sizeof(temp));
   strcpy(affTemp, "Lignes : ");
   strcat(affTemp, temp);
   AffChaine(affTemp, 6, 4, 0);

   temp = malloc(sizeof((char)niveau));
   sprintf(temp, "%d", niveau);
   affTemp = malloc(sizeof("Niveau : ") + sizeof(temp));
   strcpy(affTemp, "Niveau : ");
   strcat(affTemp, temp);
   AffChaine(affTemp, 8, 4, 0);
}

void* fctThreadShift(void* param)
{
   int alea;   
   param = NULL;
   
   sigAct.sa_handler = handlerThreadShift;
   pthread_sigmask(SIG_UNBLOCK, &sigAct.sa_mask, NULL);
   sigaction(SIGALRM, &sigAct, NULL);
   while(partieEnCours == 1)
      {
         pthread_mutex_lock(&mutexPause);
         while(threadPause == 1)
            pthread_cond_wait(&condPause, &mutexPause);
         pthread_mutex_unlock(&mutexPause);
         alea = rand()%12 + 4;
         alarm(alea);
         sleep(alea);
      }
   pthread_exit(NULL);
}

void handlerThreadShift(int sig)
{
   int cpTab[NB_LIGNE];
   int cpGrille[NB_LIGNE];
   int dep;
   int i,j;

   dep = rand()%2 + 1 ;
   
   if(sig == SIGALRM)
      {
         pthread_mutex_lock(&mutexGrille);
         if (dep == 1) // gauche
            {
               for(i = 0; i < NB_LIGNE; i++)
                  {
                     cpGrille[i] = grilleTetris.tab[i][0];
                     cpTab[i] = tab[i][0];
                  }
               
               for (i = 0; i < NB_LIGNE; i++)
                  {
                     for (j = 0; j < NB_COLONNE - 1; j++)
                        {
                           if(tab[i][j+1] != FORME && tab[i][j] != FORME)
                              {
                                 grilleTetris.tab[i][j] = grilleTetris.tab[i][j+1];
                                 tab[i][j] = tab[i][j+1];
                              }
                        }
                  }
               
               for(i = 0; i < NB_LIGNE; i++)
                  {
                     grilleTetris.tab[i][NB_COLONNE-1] = cpGrille[i];
                     tab[i][NB_COLONNE-1] = cpTab[i];
                  }
            }
         else //droite
            {
               for(i = 0; i < NB_LIGNE; i++)
                  {
                     cpGrille[i] = grilleTetris.tab[i][NB_COLONNE-1];
                     cpTab[i] = tab[i][NB_COLONNE-1];
                  }
               for (i = 0; i < NB_LIGNE; i++)
                  {
                     for (j = NB_COLONNE-1 ; j > 0; j--)
                        {
                           if(tab[i][j] != FORME && tab[i][j-1] != FORME)
                              {
                                 grilleTetris.tab[i][j] = grilleTetris.tab[i][j-1];
                                 tab[i][j] = tab[i][j-1];
                              }
                        }
                  }
               for(i = 0; i < NB_LIGNE; i++)
                  {
                     grilleTetris.tab[i][0] = cpGrille[i];
                     tab[i][0] = cpTab[i];
                  }
            }
         pthread_mutex_unlock(&mutexGrille);
      }  
}
