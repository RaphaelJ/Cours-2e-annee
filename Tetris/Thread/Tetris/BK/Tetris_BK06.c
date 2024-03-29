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
   int dir;
} S_FORME;

S_FORME Forme[7];

/*************************************************************************/

pthread_t threadForme;
void* fctThreaForme(void* param);
pthread_mutex_t mutexEvent;
pthread_cond_t condEvent;
int haut = 0;

pthread_t threadTimer;
void* fctThreadTimer(void* param);
struct timespec deltaT;
int libre;

pthread_t threadClavier;
void* fctThreadClavier(void* param);
void handlerThreadForme(int sig);
struct sigaction sigAct;
int gauche = 0;
int droite = 0;
int rotation = 0;
void fctThreadClavierFin(void *p);

pthread_mutex_t mutexGrille;
int isFree(S_FORME* forme);

pthread_t threadGenForme;
void* fctThreadGenForme(void* param);
int partieEnCours = 0;
void enoughPlace(S_FORME* forme);

pthread_t threadLigne[NB_LIGNE];
//pthread_t threadLigne;
void* fctThreadLigne(void* param);
typedef struct
{
   int numLigne;
   int compteur;
} S_LIGNE;
pthread_key_t cle;
struct sigaction sigLigne;
void handlerThreadLigne(int sig);
int maxL;
pthread_cond_t condLigne;
pthread_mutex_t mutexLigne;
int cptLigne;

int scores = 0;
int lignes = 0;
int niveau = 1;
char MAJScores;
char MAJLignes;
pthread_mutex_t mutexScores;
pthread_cond_t condScores;
pthread_t threadScores;
void* fctThreadScores(void* param);

pthread_t threadShift;
void* fctThreadShift(void* param);
void handlerThreadShift(int sig);
pthread_mutex_t mutexShift;
pthread_cond_t condShift;
int shift;
pthread_mutex_t mutexAttShift;
pthread_cond_t condAttShift;
int AttShift;

void initForme(void);
void initAff(void);

/*************************************************************************/
int main(void)
{
   srand((unsigned)time(NULL));
   
   // ***** Definition des formes de base **********************
   initForme();
   
   printf("Ouverture de la grille de jeu...\n");
   if (OuvrirGrille(&grilleTetris,NB_LIGNE,NB_COLONNE,30,"Tetris") == -1)
      {
         perror("Erreur de InitGrille");
         exit(-1);
      }
   
   if (OuvrirGrille(&grilleSuivant,4,NB_COLONNE,30,"Forme Suivante") == -1)
      {
         perror("Erreur de InitGrille");
         exit(-1);
      }
   
   /*** Initialisation des mutex et conditions  ***/
   pthread_mutex_init(&mutexEvent, NULL);
   pthread_cond_init(&condEvent, NULL);
   pthread_mutex_init(&mutexGrille, NULL);
   pthread_mutex_init(&mutexLigne, NULL);
   pthread_cond_init(&condLigne, NULL);
   pthread_mutex_init(&mutexScores, NULL);
   pthread_cond_init(&condScores, NULL);
   pthread_mutex_init(&mutexShift, NULL);
   pthread_cond_init(&condShift, NULL);
   pthread_mutex_init(&mutexAttShift, NULL);
   pthread_cond_init(&condAttShift, NULL);
   
   /*** Initialisations ***/
   deltaT.tv_sec = 0;
   deltaT.tv_nsec = 500000000;
   partieEnCours = 1;
   cptLigne = 4;
   
   
   sigfillset(&sigAct.sa_mask);
   sigAct.sa_handler = handlerThreadLigne;
   sigaction(SIGUSR1, &sigAct, NULL);
   sigaction(SIGALRM, &sigAct, NULL);

   /** Initialisation de la structure S_LIGNE **/
   S_LIGNE ligne[20];

   /** Creation de la cle **/
   if (pthread_key_create(&cle, NULL))
      fprintf(stderr, "Erreur de creation de la cle\n");
    
   /** Lancement des threads ligne **/
   int i;
   for (i = 0; i < NB_LIGNE; i++)
      {
         ligne[i].numLigne = i;
         ligne[i].compteur = 0;
         pthread_create(&threadLigne[i], NULL, fctThreadLigne, &ligne[i]);
      }
   
   printf("Appuyez sur une touche pour commencer\n");
   getchar();
   cleanGrille();
   system("clear");
   initAff();

   if(pthread_create(&threadGenForme, NULL, fctThreadGenForme, NULL))
      fprintf(stderr, "Erreur de creation du thread generateur de formes\n");

   if(pthread_create(&threadTimer, NULL, fctThreadTimer, NULL))
      fprintf(stderr, "Erreur de creation du thread timer\n");
                     
   if(pthread_create(&threadClavier, NULL, fctThreadClavier, NULL))
      fprintf(stderr, "Erreur de creation du thread clavier\n");

   if(pthread_create(&threadScores, NULL, fctThreadScores, NULL))
      fprintf(stderr, "Erreur de creation du thread scores\n");

   if(pthread_create(&threadShift, NULL, fctThreadShift, NULL))
      fprintf(stderr, "Erreur de creation du thread shift\n");

   
   pthread_join(threadGenForme, NULL);

   /** synchronisation des threads ligne **/
  
   /*for (i = 0; i < NB_LIGNE; i++)
      {
         pthread_join(threadLigne[i], NULL);
         printf("join %i\n", i);
      }*/
   
   pthread_key_delete(cle);
   pthread_mutex_destroy(&mutexEvent);
   pthread_cond_destroy(&condEvent);
   pthread_mutex_destroy(&mutexGrille);
   pthread_mutex_destroy(&mutexLigne);
   pthread_cond_destroy(&condLigne);
   pthread_mutex_destroy(&mutexScores);
   pthread_cond_destroy(&condScores);
   pthread_mutex_destroy(&mutexShift);
   pthread_cond_destroy(&condShift);
   pthread_mutex_destroy(&mutexAttShift);
   pthread_cond_destroy(&condAttShift);

   printf("Partie terminee...\n");
   printf("Appuyez sur une touche pour quitter\n");
   getchar();
      
   /********************************************************************/
   printf("Fermeture de la grille de jeu...\n");
  
   fflush(stdout);
   FermerGrille(&grilleTetris);
   FermerGrille(&grilleSuivant);
   
   if (tcsetattr(0,TCSANOW,&SaveTerm) == -1) 
      exit(1);
  
   exit(0);
}

void initAff(void)
{
   /** **/
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

void initForme(void)
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


/*************************************************************************/
/********** Thread forme *************************************************/
/*************************************************************************/
void* fctThreadForme(void* param)
{
   //printf("--Thread forme\n");

   libre = 0;
   int i;
   S_FORME *forme;
   forme = param;
   int cdOK;
   int cgOK;
   int okL = 0, okC = 0;
   int max = 0, min = 0;
   int C = 0, L = 0;
   int temp = 0;

   pthread_mutex_lock(&mutexAttShift);
   AttShift = 1;
   pthread_mutex_unlock(&mutexAttShift);
   while(haut == 0)// && rotation == 0 && droite == 0 && gauche == 0)
      {
         pthread_cond_wait(&condEvent, &mutexEvent);
         pthread_mutex_lock(&mutexAttShift);
         while(AttShift == 0)
            pthread_cond_wait(&condAttShift, &mutexAttShift);
         pthread_mutex_unlock(&mutexAttShift);

         if(haut == 19)
            {
               while(isFree(forme) == 0);
               haut--;
            }

         else if(haut > 0)
            {
               if(isFree(forme) == 0)
                  haut--;
				  
               /*for (i = 0; i < NB_LIGNE; i++)
                  {
                     for (j = 0; j < NB_COLONNE; j++)
                        printf("%4d ", tab[i][j]);
                     printf("\n");
                  }
                  printf("\n");printf("\n");printf("\n");*/
            }
               
         cgOK = 0;
         if(gauche > 0)
            {
               //printf("a gauche\n");
               for (i = 0; i < 4; i++)
                  {
                     if(forme->C[i] -1 < 0)
                        cgOK = -1;
                  }
               if(cgOK == 0)
                  {
                     pthread_mutex_lock(&mutexGrille);
                     for (i = 0; i < 4; i++)
                        {
                           DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
                           tab[forme->L[i]][forme->C[i]] = VIDE;
                        }
                     pthread_mutex_unlock(&mutexGrille);
                     for (i = 0; i < 4; i++)
                        {
                           forme->C[i] = forme->C[i] - 1;
                           tab[forme->L[i]][forme->C[i]] = FORME;
                        }
                  }
               gauche--;
            }
       
         cdOK = 0;
         if(droite > 0)
            {
               //printf("a droite\n");
               for (i = 0; i < 4; i++)
                  {
                     if(forme->C[i] + 1 > 8)
                        cdOK = -1;
                  }
               if(cdOK == 0)
                  {
                     pthread_mutex_lock(&mutexGrille);
                     for (i = 0; i < 4; i++)
                        {
                           DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
                           tab[forme->L[i]][forme->C[i]] = VIDE;
                        }
                     pthread_mutex_unlock(&mutexGrille);
                     for (i = 0; i < 4; i++)
                        {
                           forme->C[i] = forme->C[i] + 1;
                           tab[forme->L[i]][forme->C[i]] = FORME;
                        }
                  }
               droite--;
            }
         
         if(rotation > 0)
            {
               //printf("rotation \n");
               pthread_mutex_lock(&mutexGrille);
               for (i=0 ; i<4 ; i++)
			   {
                  DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
				  tab[forme->L[i]][forme->C[i]] = VIDE;
			   }
               pthread_mutex_unlock(&mutexGrille);
               C = forme->C[0];
               L = forme->L[0];
               okL = 0;
               okC = 0;
               for (i=0 ; i<4 ; i++) 
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
               
               pthread_mutex_lock(&mutexGrille);
               for(i = 0; i< 4; i++)
			   {
                  DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
				  tab[forme->L[i]][forme->C[i]] = FORME;
			   }
               pthread_mutex_unlock(&mutexGrille);
               
               rotation--;
            }
      }
   pthread_exit(NULL);
   
}

int isFree(S_FORME* forme)
{
   int i;
   libre = 0;
   
   pthread_mutex_lock(&mutexGrille);
   for (i = 0; i < 4; i++)
   {
      DessineCarre(&grilleTetris,forme->L[i],forme->C[i],BLANC);
      tab[forme->L[i]][forme->C[i]] = VIDE;
   }
   
   pthread_mutex_unlock(&mutexGrille);
   
   for (i = 0; i < 4; i++)
      {
         if(tab[(forme->L[i])-1][forme->C[i]] != VIDE)
            {
               libre = -1;
               //printf("pas libre\n");
               //printf("L = %d et C = %d\n", forme->L[i]-1, forme->C[i]);
            }
      }
   if (libre == 0)
      {
         for (i = 0; i < 4; i++)
            {
               //grilleTetris.tab[forme->L[i]][forme->C[i]] = VIDE;
               tab[forme->L[i]][forme->C[i]] = VIDE;
               forme->L[i] = forme->L[i] - 1;
            }
      }
   pthread_mutex_lock(&mutexGrille);
   for (i = 0; i < 4; i++)
   {
      DessineCarre(&grilleTetris,forme->L[i],forme->C[i], forme->couleur);
      tab[forme->L[i]][forme->C[i]] = FORME;
   }
   pthread_mutex_unlock(&mutexGrille);
   return libre;
}

void enoughPlace(S_FORME* forme)
{
   int i;
    for (i = 0; i < 4; i++)
      {
         //if(grilleTetris.tab[(forme->L[i])-1][forme->C[i]] != VIDE)
         if(tab[(forme->L[i])-1][forme->C[i]] != VIDE)
            {
               //printf("--Plus de place pour la forme\n");
               partieEnCours = 0;
               pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
               pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
               pthread_cancel(threadClavier);
            }
      }
}

/*************************************************************************/
/********** Thread timer *************************************************/
/*************************************************************************/
void* fctThreadTimer(void* param)
{
   
   param = NULL;
   //printf("--Thread timer\n");

   while(1)
      {
         pthread_mutex_lock(&mutexEvent);
         haut++;
         pthread_mutex_unlock(&mutexEvent);
         pthread_cond_signal(&condEvent);
         nanosleep(&deltaT, NULL);
         if (partieEnCours == 0)
            break;
      }
      
   pthread_exit(NULL);
}

/*************************************************************************/
/********** Thread clavier ***********************************************/
/*************************************************************************/
void* fctThreadClavier(void* param)
{
   param = NULL;
   //printf("--Thread clavier\n");
   pthread_cleanup_push(fctThreadClavierFin, 0);
   int token;
   while(1)
      {
         token = ReadChar();
         switch (token)
            {
            case KEY_UP :
               //printf("KEY_UP\n");
               //haut++;
               haut = 19;
               pthread_cond_signal(&condEvent);
               break;
            case KEY_DOWN :
               //printf("KEY_DOWN\n");
               pthread_mutex_lock(&mutexEvent);
               rotation++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case KEY_LEFT :
               //printf("KEY_LEFT\n");
               pthread_mutex_lock(&mutexEvent);
               gauche++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);        
               break;
            case KEY_RIGHT :
               //printf("KEY_RIGHT\n");
               pthread_mutex_lock(&mutexEvent);
               droite++;
               pthread_mutex_unlock(&mutexEvent);
               pthread_cond_signal(&condEvent);
               break;
            case 'p':
               printf("Pause ...\n");
               break;
            }
         if(partieEnCours == 0)
            break;
      }
   pthread_cleanup_pop(1);
   pthread_exit(NULL);
}

void fctThreadClavierFin(void *p)
{
   p = NULL;
   //printf("Reinitialisation du terminal\n");
   tcsetattr(0,TCSANOW,&SaveTerm);
}

/*************************************************************************/
/********** Thread Generateur de formes **********************************/
/*************************************************************************/
void* fctThreadGenForme(void* param)
{
   S_FORME *forme,*suivant;
   int i;
   param = NULL;
   forme = (S_FORME*)malloc(sizeof(S_FORME));
   memcpy(forme,&Forme[rand()%7],sizeof(S_FORME));
   suivant = (S_FORME*)malloc(sizeof(S_FORME));
   
   memcpy(suivant,&Forme[rand()%7],sizeof(S_FORME));
   for (i = 0 ; i<4 ; i++) 
      DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],suivant->couleur);
  
   while (partieEnCours == 1)
      {
         
         pthread_mutex_lock(&mutexGrille);
         for (i = 0 ; i < 4 ; i++)
            {
               DessineCarre(&grilleTetris,forme->L[i],forme->C[i],forme->couleur);
               tab[forme->L[i]][forme->C[i]] = FORME;
            }
         pthread_mutex_unlock(&mutexGrille);
         
         
         if(pthread_create(&threadForme, NULL, fctThreadForme, forme))
            fprintf(stderr, "Erreur de creation du thread forme\n");
         
         //printf("Attente thread forme\n");
         pthread_join(threadForme, NULL);

         //printf("Forme immobilisee..\n");
         maxL = 0;
         for(i = 0; i < 4; i++)
            {
               if(forme->L[i] > maxL)
                  maxL = forme->L[i];
            }
         for (i = 0; i < 4; i++)
            {
               grilleTetris.tab[forme->L[i]][forme->C[i]] = forme->couleur;
               tab[forme->L[i]][forme->C[i]] = forme->couleur;
            }
         
         pthread_kill(threadLigne[maxL], SIGUSR1);
         pthread_mutex_lock(&mutexLigne);
         while(cptLigne != 0)
            pthread_cond_wait(&condLigne, &mutexLigne);
         pthread_mutex_unlock(&mutexLigne);
		 
		 
         
         pthread_mutex_lock(&mutexScores);
         scores++;
         pthread_mutex_unlock(&mutexScores);
         MAJScores = 1;
         pthread_cond_signal(&condScores);


         //printf("Nouvelle forme...\n");
         cptLigne = 4;
         memcpy(forme,suivant,sizeof(S_FORME));
         enoughPlace(forme);
         
         /** Efface la grille suivante **/
         
         for (i = 0 ; i<4 ; i++) 
            DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],BLANC);
         /** Genere une nouvelle forme "suivante" **/
         memcpy(suivant,&Forme[rand()%7],sizeof(S_FORME));
         for (i = 0 ; i<4 ; i++) 
            DessineCarre(&grilleSuivant,suivant->L[i]-NB_LIGNE+3,suivant->C[i],suivant->couleur);
         
         haut = 0;
      }
   free(forme);
   free(suivant);
   pthread_exit(NULL);
}

/*************************************************************************/
/********** Thread ligne *************************************************/
/*************************************************************************/
void* fctThreadLigne(void* param)
{
   S_LIGNE *pligne;
   pligne = (S_LIGNE*)param; 
      
   pthread_sigmask(SIG_UNBLOCK, &sigAct.sa_mask, NULL);

   pthread_setspecific(cle, pligne);
  
   //while(1)
   while(partieEnCours == 1)
   {
      pause();
      maxL = maxL - 1;
      if (maxL > -1 && cptLigne > 1)
         {
            pthread_kill(threadLigne[maxL], SIGUSR1);
         }
      cptLigne--;
      if(cptLigne == 0 || (cptLigne > 0 && maxL < 0))
         {
            pthread_cond_signal(&condLigne);
            cptLigne = 0;
         }
   }
   pthread_exit(NULL);
}


/*************************************************************************/
/********** Handler thread ligne *****************************************/
/*************************************************************************/
void handlerThreadLigne(int sig)
{ 
   int i, j, cpt;

   S_LIGNE *ligne;

   ligne = (S_LIGNE*) pthread_getspecific(cle);
  
   if (sig == SIGUSR1)
      {
         i = ligne->numLigne;
         ligne->compteur =  ligne->compteur + 1;
		 
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
                     pthread_mutex_lock(&mutexGrille);
                     DessineCarre(&grilleTetris, i, j, BLANC);
                     pthread_mutex_unlock(&mutexGrille);
                  }
               
               //decale les lignes
               pthread_mutex_lock(&mutexGrille);
               for (i = ligne->numLigne; i < NB_LIGNE - 1; i++)
                  {
                     for(j = 0; j < NB_COLONNE; j++)
                        {
                           if(grilleTetris.tab[i+1][j] != FORME)
                              {
                                 grilleTetris.tab[i][j] =  grilleTetris.tab[i+1][j];
                                 tab[i][j] = tab[i+1][j];
                              }
                        }
                     
                  }
               pthread_mutex_unlock(&mutexGrille);
               for (j = 0; j < NB_COLONNE; j++)
                  {
                     pthread_mutex_lock(&mutexGrille);
                     DessineCarre(&grilleTetris, NB_LIGNE - 1, j, BLANC);
                     pthread_mutex_unlock(&mutexGrille);
                     tab[NB_LIGNE-1][j] = VIDE;
                  }
				  
               //incremente son compteur
               ligne->compteur = ligne->compteur + 1;

               //mise a jour du score
                scores = scores + 10;
                pthread_mutex_lock(&mutexScores);
                lignes++;
                pthread_mutex_unlock(&mutexScores);
                MAJLignes = 1;
                pthread_cond_signal(&condScores);
            }
      }
}

/*************************************************************************/
/********** Thread scores ************************************************/
/*************************************************************************/

void* fctThreadScores(void* param)
{
   param = NULL;
   char* temp;
   char* affTemp;

   //while(1)
   while(partieEnCours == 1)
      {
         pthread_mutex_lock(&mutexScores);
         while (!MAJLignes && !MAJScores)
            pthread_cond_wait(&condScores, &mutexScores);
         pthread_mutex_unlock(&mutexScores);
         
         if (MAJScores == 1)
            {
               temp = malloc(sizeof((char)scores));
               sprintf(&temp[0], "%d", scores);
               affTemp = malloc(sizeof("Score : ") + sizeof(temp));
               strcpy(affTemp, "Score : ");
               strcat(affTemp, temp);
               //system("clear");
               //printf("\t Scores : %d\n", scores);
               AffChaine(affTemp, 4, 4, 0);
               MAJScores--;
            }
         if (MAJLignes == 1)
            {
               lignes++;
               temp = malloc(sizeof((char)lignes));
               sprintf(temp, "%d", lignes);
               affTemp = malloc(sizeof("Lignes : ") + sizeof(temp));
               strcpy(affTemp, "Lignes : ");
               strcat(affTemp, temp);
               AffChaine(affTemp, 6, 4, 0);
               //printf("\t Lignes : %d\n", lignes);
               if((lignes % 5 == 0) && (lignes != 0))
                  {
                     niveau++;
                     //printf("\t Niveau : %d\n", niveau);
                     temp = malloc(sizeof((char)niveau));
                     sprintf(temp, "%d", niveau);
                     affTemp = malloc(sizeof("Niveau : ") + sizeof(temp));
                     strcpy(affTemp, "Niveau : ");
                     strcat(affTemp, temp);
                     AffChaine(affTemp, 8, 4, 0);
                     long test;
                     test = deltaT.tv_nsec;
                     test = test - (test*0.2);
                     deltaT.tv_nsec = test;
                  }
               MAJLignes--;
            }
      }
   pthread_exit(NULL);
}

/*************************************************************************/
/********** Thread shift  ************************************************/
/*************************************************************************/
void* fctThreadShift(void* param)
{
   int alea;   
   param = NULL;
   
   //printf("--Thread Shift\n");
   sigAct.sa_handler = handlerThreadShift;
   pthread_sigmask(SIG_UNBLOCK, &sigAct.sa_mask, NULL);
   sigaction(SIGALRM, &sigAct, NULL);
   while(partieEnCours == 1)
      {
         alea = rand()%12 + 4;
         alarm(alea);
         pthread_mutex_lock(&mutexShift);
         shift = 1;
         pthread_mutex_unlock(&mutexShift);
         pthread_mutex_lock(&mutexShift);
         while(shift == 1)
            pthread_cond_wait(&condShift, &mutexShift);
         pthread_mutex_unlock(&mutexShift);
      }
   pthread_exit(NULL);
}

/*************************************************************************/
/********** Handler thread shift *****************************************/
/*************************************************************************/
void handlerThreadShift(int sig)
{
   int cpTab[NB_LIGNE];
   int cpGrille[NB_LIGNE];
   int dep;
   int i,j;
   
   //printf("--Handler Thread Shift\n");
   dep = rand()%2 + 1 ;
   
   if(sig == SIGALRM)
      {
         pthread_mutex_lock(&mutexAttShift);
         AttShift = 0;
         pthread_mutex_unlock(&mutexAttShift);
         //printf("dep = %d\n", dep);
         if (dep == 1) // gauche
            {
               for(i = 0; i < NB_LIGNE; i++)
                  {
                     cpGrille[i] = grilleTetris.tab[i][0];
                     cpTab[i] = tab[i][0];
                  }
               
               pthread_mutex_lock(&mutexGrille);
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
               pthread_mutex_unlock(&mutexGrille);
            }
         else //droite
            {
               for(i = 0; i < NB_LIGNE; i++)
                  {
                     cpGrille[i] = grilleTetris.tab[i][NB_COLONNE-1];
                     cpTab[i] = tab[i][NB_COLONNE-1];
                  }
               pthread_mutex_lock(&mutexGrille);
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
               pthread_mutex_unlock(&mutexGrille);
               
            }
         pthread_mutex_lock(&mutexShift);
         shift = 0;
         pthread_mutex_unlock(&mutexShift);
         pthread_cond_signal(&condShift);
         
         pthread_mutex_lock(&mutexAttShift);
         AttShift = 1;
         pthread_mutex_unlock(&mutexAttShift);
         pthread_cond_signal(&condAttShift);
      }  
}

/*************************************************************************/
/********** Initialise la grille *****************************************/
/*************************************************************************/
void cleanGrille()
{
   int i, j;
   for (i = 0 ; i<NB_LIGNE ; i++)
      for (j = 0 ; j<NB_COLONNE ; j++)
         {
            //tab[i][j] = VIDE;
            tab[i][j] = 1;
            DessineCarre(&grilleTetris,i,j,BLANC);
         }
}

/*************************************************************************/
/*****Fonctions de gestion du clavier ***********************************/
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




