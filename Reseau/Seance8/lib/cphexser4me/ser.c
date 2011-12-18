/*---------------------------------------------------------------
  Herman Vanstapel 2004
   Cpheser4me\ser.c
----------------------------------------------------------------*/

#include <stdio.h>

#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "message.h"

/*
struct Message
{
  int Entier1 ;
  int Entier2 ;
  int Resultat ;
  char Commentaire[200] ;
};
*/

int main(int argc,char *argv[])
{
 int rc ;
 struct Physique L ; /* pour eviter un bug curieux !!!!!!!*/
 int tm ;
 int HLs[100] ;
 int HEs[100] ;
 char Buffer[50] ;
 int HL,HE ;
 int descphys ;
 static struct gEvenement gEv ;
 int IPR,PORTD ;


 bzero(&L,sizeof (struct Physique)) ;
 bzero(HLs, sizeof(HLs )) ;
 bzero(HEs, sizeof(HEs)) ;

 printf("Ceci est le serveur\n") ;
 if ( argc!=3)
 {
  printf("ser ser port \n") ;
  exit(1) ;
 }

 descphys = CreerConnexion(&L,argv[1],atoi(argv[2]),NULL,0) ;
 if ( descphys == -1 )
    perror("CreerLiaison:") ;
 else
    printf("Liaison Cree \n") ;

 HLs[descphys]=1 ;
 HLs[0] = 1 ;

 rc = PrepareEvenement(&gEv,HLs,HEs,100,300,0 ) ;
 if ( rc== -1 )
    perror("PrepareEvenement:") ;

 while(1)
 {
  rc = AttendreEvenement(&gEv,&HL,&HE) ;
  if ( rc == -1 )
     perror("AttendreEvenement:") ;
  else
     printf("Event:%d\n",HL) ;
  if ( HL == 0 )
     {
      char Buffer[100] ;
      fgets(Buffer,sizeof Buffer,stdin) ;
      Buffer[strlen(Buffer)]=0 ;
      printf("La touche enfoncee est %s \n",Buffer) ;
      sleep(10) ;
     }
  if ( HL == descphys )
  {
   struct Message Msg ;
   tm = sizeof(struct Message) ;
   rc = OrigineCouchePhysique(&L,&Msg,&tm ) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
   else
      printf("bytes:%d:%d + %d : %s\n",rc,Msg.Entier1,Msg.Entier2,Msg.Commentaire ) ;

   IPR=IPDistante(&L)    ;
   PORTD=PortDistant(&L) ;
   Ipv4ToS(IPR, Buffer) ;
   printf("IP distante %s Port Distant %d \n",Buffer,PORTD ) ;

   /* calcul de la r�onse */
   Msg.Resultat = Msg.Entier1 + Msg.Entier2 ;
   rc = Repondre(&L,&Msg,sizeof(struct Message)) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
    else
       printf("bytes ecrits :%d\n",rc ) ;
   }
 }
}

