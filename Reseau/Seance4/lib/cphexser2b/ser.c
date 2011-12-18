/*---------------------------------------------------------------
  cphexser2b\ser.c
----------------------------------------------------------------*/

#include <stdio.h>

#include "../evlib/evlib.h"
#include "../physlib/physlib.h"

int  main(int argc,char *argv[])
{
 int rc ;
 struct Physique L1,L2 ;
 char message[100] ;
 int tm ;
 char *Chaine ;
 static int HLs[100] ;
 static int HEs[100] ;
 int HL,HE ;
 int descphys,descphys2 ;
 static struct gEvenement gEv ;

 bzero(&L1,sizeof(struct Physique)) ;
 bzero(&L2,sizeof(struct Physique)) ;

 printf("Ceci est le serveur\n") ;
 if ( argc!=4)
 {
  printf("ser ipser port port \n") ;
  exit(1) ;
 }

 descphys = CreerConnexion(&L1,argv[1],atoi(argv[2]),NULL,0) ;
 if ( descphys == -1 )
    perror("CreerLiaison:1") ;
 else
    fprintf(stderr,"Liaison Cree \n") ;

 descphys2 = CreerConnexion(&L2,argv[1],atoi(argv[3]),NULL,0) ;
 if ( descphys == -1 )
    perror("CreerLiaison:2") ;
 else
    fprintf(stderr,"Liaison Cree \n") ;
 
 HLs[descphys]  = 1 ;
 HLs[descphys2] = 1 ;
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
      fprintf(stderr,"La touche enfonc� est %s \n",Buffer) ;
     }
  if ( HL == descphys )
  {
   tm = sizeof(message) ;
   rc = OrigineCouchePhysique(&L1,message,&tm ) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
   else
      fprintf(stderr,"bytes:%d:%s\n",rc,message ) ;
      printf("Je vous repond quand il y'aura reception sur le second port\n") ;

   }
  if ( HL == descphys2 )
  {
   tm = sizeof(message) ;
   rc = OrigineCouchePhysique(&L2,message,&tm ) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
   else
      fprintf(stderr,"bytes:%d:%s\n",rc,message ) ;

   Chaine = "Bonjour Madame 2" ;
   rc = Repondre(&L2,Chaine,strlen(Chaine)+1) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
    else
       fprintf(stderr,"Reponse 2 bytes ecrits :%d:%s\n",rc,Chaine ) ;
   
   Chaine = "Bonjour Madame 1" ;
   rc = Repondre(&L1,Chaine,strlen(Chaine)+1) ;
   if ( rc == -1 )
      {
       perror("OrigineCouchePhysique") ;
       return(-1) ;
      }
    else
       fprintf(stderr,"Reponse 1 bytes ecrits :%d:%s\n",rc,Chaine ) ;
   }
   
 }
}

