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

/*************************************************************************/
struct timespec deltaT;

int haut = 0;
int gauche = 0;
int droite = 0;
int rotation = 0;
int partieEnCours;

void initFormes (void);
void move_left (S_FORME* forme);
void move_right (S_FORME* forme);
void move_down (S_FORME* forme);

pthread_t threadForme;
pthread_t threadTimer;
pthread_t threadClavier;
pthread_t threadGenForme;

void* fctThreadForme(void* param);
void* fctThreadTimer(void* param);
void* fctThreadClavier(void* param);
void* fctThreadGenForme(void* param);

pthread_mutex_t mutexEvent;
pthread_mutex_t mutexGrille;
pthread_mutex_t mutexTimer;

pthread_cond_t condEvent;


/*************************************************************************/
int main(void)
{
   srand((unsigned)time(NULL));
 	
//A DELETE
if (tcgetattr(0,&Term) == -1) return -1;
   SaveTerm = Term;
  
   // ***** Definition des formes de base **********************
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
	   
   partieEnCours = 1;
   /*** pour les formes du Tetris **********/
   S_FORME *forme,*suivant;
   int i;
   forme = (S_FORME*)malloc(sizeof(S_FORME));
   memcpy(forme,&Forme[rand()%7],sizeof(S_FORME));
   for (i = 0 ; i<4 ; i++) 
      DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
   
   suivant = (S_FORME*)malloc(sizeof(S_FORME));
   memcpy(suivant,&Forme[rand()%7],sizeof(S_FORME));
   for (i = 0 ; i<4 ; i++) 
      DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],suivant->couleur);

   deltaT.tv_sec = 0;
   deltaT.tv_nsec = 500000000;

   if(pthread_create(&threadTimer, NULL, fctThreadTimer, NULL))
      fprintf(stderr, "Erreur de creation du thread timer\n");

    if(pthread_create(&threadClavier, NULL, fctThreadClavier, NULL))
      fprintf(stderr, "Erreur de creation du thread clavier\n");
   
   
   while(partieEnCours == 1)
      {	
	pthread_mutex_lock(&mutexEvent);
	 haut = 0;
	pthread_mutex_unlock(&mutexEvent);
         if(pthread_create(&threadForme, NULL, fctThreadForme, forme))
            fprintf(stderr, "Erreur de creation du thread forme\n");
         printf("done\n");
         pthread_join(threadForme, NULL);
         printf("join\n");
         memcpy(forme,suivant,sizeof(S_FORME));
     
	pthread_mutex_lock(&mutexGrille);
	for (i = 0 ; i<4 ; i++) 
	 DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],BLANC);
	 memcpy(suivant,&Forme[rand()%7],sizeof(S_FORME));
	for (i = 0 ; i<4 ; i++) 
      DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],suivant->couleur);
	pthread_mutex_unlock(&mutexGrille);
      }
   pthread_mutex_destroy(&mutexEvent);
   pthread_cond_destroy(&condEvent);
pthread_mutex_destroy(&mutexTimer);

   free(forme);
   free(suivant);
   
   /********************************************************************/
   printf("Fermeture de la grille de jeu...\n");
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
   for (i = 0 ; i<NB_LIGNE ; i++)
      for (j = 0 ; j<NB_COLONNE ; j++)
         {
            tab[i][j] = VIDE;
            DessineCarre(&grilleTetris,i,j,BLANC);
         }
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
                                 printf("FINI!\n");
				getchar();
                                 partieEnCours = 0;
                              }
                           tab[forme->L[i]][forme->C[i]] = forme->couleur;
			}
                  }
            }
         if(gauche > 0)
	{
            printf("gauche\n");
		move_left(forme);
		gauche--;
	}
         if(droite > 0)
	{
            printf("droite\n");
		move_right(forme);
		droite--;
	}
         if(rotation > 0) 
	{
            printf("rotation\n");
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
   int token;
   while(1)
      {
         token = ReadChar();
         switch (token)
            {
            case KEY_UP :
               pthread_mutex_lock(&mutexEvent);
               haut = 19;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case KEY_DOWN :               
               pthread_mutex_lock(&mutexEvent);
               rotation++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case KEY_LEFT :
               pthread_mutex_lock(&mutexEvent);
               gauche++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);        
               break;
            case KEY_RIGHT :
               pthread_mutex_lock(&mutexEvent);
               droite++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case 'p':
               break;
            }
      }
   pthread_exit(NULL);
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
