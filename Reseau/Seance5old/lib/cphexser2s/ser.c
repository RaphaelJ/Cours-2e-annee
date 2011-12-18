/*---------------------------------------------------------------
  cphexser2\ser.c
----------------------------------------------------------------*/

#include <stdio.h>

#include "../evlib/evlib.h"
#include "../physlib/physlib.h"

int main(int argc,char *argv[])
{
 int rc ;
 struct Physique L ; 
 char message[100] ;
 int tm ;
 char *Chaine ;
 static int HLs[100] ;
 static int HEs[100] ;
 int HL,HE ;
 int descphys ;
 static struct gEvenement gEv ;

 bzero(&L,sizeof(struct Physique)) ;

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
    fprintf(stderr,"Liaison Cree\n") ;
 
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
     fprintf(stderr,"Event:%d\n",HL) ;
  if ( HL == 0 )
     {
      char Buffer[100] ;
      fgets(Buffer,sizeof Buffer,stdin) ;
      Buffer[strlen(Buffer)]=0 ;
      printf("La touche enfonc� est %s \n",Buffer) ;
     }
  if ( HL == descphys )
  {
   tm = sizeof(message) ;
   rc = OrigineCouchePhysique(&L,message,&tm ) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
   else
      fprintf(stderr,"bytes lus:%d:%s\n",rc,message ) ;

   Chaine = "Bonjour Madame" ;
   rc = Repondre(&L,Chaine,strlen(Chaine)+1) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
    else
       fprintf(stderr,"bytes �ecrits :%d:%s\n",rc,Chaine ) ;
   }
 }
}

