/*---------------------------------------------------------------
  cphexser4\ser.c
----------------------------------------------------------------*/

#include <stdio.h>
#include "../evlib/evlib.h"
#include "../physlib/physlib.h"

int main(int argc,char *argv[])
{
 int rc ;

 char message[100] ;
 int tm ;
 char *Chaine ;
 int HL,HE ;
 int descphys ;

  int HLs[100] ;
  int HEs[100] ;
  struct Physique L ; 
  struct gEvenement gEv ;
  int PortD ;
  int IPD ;
  char ips[17] ;

  bzero(HLs,sizeof HLs ) ;
  bzero(HEs,sizeof HEs ) ;
  bzero(&L, sizeof ( struct Physique))  ; /* pour eviter un bug curieux !!!!!!!*/
  bzero(&gEv,sizeof(struct gEvenement )) ;

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
      fprintf(stderr,"La touche enfoncee est %s \n",Buffer) ;
      sleep(10) ;
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
      fprintf(stderr,"bytes:%d:%s\n",rc,message ) ;

   IPD =  IPDistante(&L)  ;
   PortD= PortDistant(&L) ;
   Ipv4ToS(IPD,ips)       ;
   printf(" IP client %s Port client %d \n",ips,PortD) ;

   Chaine = "Bonjour Madame" ;
   rc = Repondre(&L,Chaine,strlen(Chaine)+1) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
    else
       fprintf(stderr,"bytes ecrits :%d:%s\n",rc,Chaine ) ;
   }
 }
}

