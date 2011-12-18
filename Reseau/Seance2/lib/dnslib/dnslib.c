/*--------------------------------------------------------------------
 Vanstapel Herman EPL

 Service DNS
-----------------------------------------------------------------------
-----------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "../tcplib/tcplib.h"
#include "../evlib/evlib.h"
#include "../physlib/physlib.h"
#include "../protocol/protocol.h"
#include "dnslib.h" 

/* struct RequeteDNS{
      int Type ;
      int Numero ;
      int IP ;
      NomDNS Nom ;
}; 

struct NomsResolus
{
 NomDNS Nom  ;
 int	Ip   ;
 int    Vide ;
 int	Fin  ;
}; */ 

int AjoutCacheDNS(struct NomsResolus LesNomsResolus[],NomDNS Nom,int UneIp)
{
 int i = 0 ;
 while(!LesNomsResolus[i].Fin)
 {
  
  if (LesNomsResolus[i].Vide )
  {
    strncpy(LesNomsResolus[i].Nom,Nom,sizeof(LesNomsResolus[i].Nom)) ;	   
    LesNomsResolus[i].Ip   = UneIp ;
    LesNomsResolus[i].Vide = 0  ;
    LesNomsResolus[i].Fin  = 0  ;
    return(1) ;
  }
  else
     if ( strcmp(LesNomsResolus[i].Nom,Nom)==0)
        {
         strncpy(LesNomsResolus[i].Nom,Nom,sizeof(LesNomsResolus[i].Nom)) ;	   
         LesNomsResolus[i].Ip   = UneIp ;
         return(1) ;
        }
  i++ ;	 
 }
 return(0) ;
};


void AfficheCacheDNS(struct NomsResolus LesNomsResolus[] )
{
 /* ici modif */	
 int i = 0 ;
 while(!LesNomsResolus[i].Fin)
 {
  char Buffer[40] ;
 	
  if (!LesNomsResolus[i].Vide)
    {
     char Buffer[40] ;
     Ipv4ToS(LesNomsResolus[i].Ip , Buffer) ; 
     printf("%d Le nom est %s : %s\n",i,LesNomsResolus[i].Nom, Buffer) ;
    }
  i++ ;
 }
 printf("dernier indice %d\n",i);
}

int EffaceCacheDNS(struct NomsResolus  LesNomsResolus[])
{

 int i = 0 ;

 while(!LesNomsResolus[i].Fin)
 {	 
    LesNomsResolus[i].Vide = 1  ;
    LesNomsResolus[i].Fin  = 0  ;
    i++ ;
 }
 return(1) ;
}

struct NomsResolus* InitialiseCacheDNS(int NE)
{
 int i ;
 struct NomsResolus *NR ;
 NR = malloc(sizeof(struct NomsResolus)*(NE+1)) ;
 if ( NR == NULL )
    {
     perror("Plus de mémoire !") ;
     exit(0) ;
    }
 i=0 ;
 while( NE > 0 )
 {
    NR[i].Vide = 1  ;
    NR[i].Fin  = 0  ;
    i++ ;
    NE-- ;
 }

 NR[i].Vide = 1  ;
 NR[i].Fin  = 1  ;
 return(NR) ;
};

int RechercheNomCacheDNS(struct NomsResolus LesNomsResolus[],NomDNS NomAResoudre)
{
 int i = 0 ;

 while(!LesNomsResolus[i].Fin)
 {
  fprintf(stderr,"%d,Entree,Nom:%s:%s:\n",i,LesNomsResolus[i].Nom,NomAResoudre) ;	 
  if ( strcmp(LesNomsResolus[i].Nom,NomAResoudre)==0)
        return(LesNomsResolus[i].Ip) ;
  i++ ;
 }
 return(0);
}
	
int RechercheNomDB(char* FichierDNS,char *NomAResoudre)
{
 char Buffer[100] ;
 char Nom[100] ;
 char IPS[100] ;
 int  Ip ;
 FILE *fp ;

 fp = fopen(FichierDNS,"r") ;
 if ( fp== NULL )
    {
     printf("Fichier inexistant\n") ;
     exit(1) ;
    }
 else
    printf("Fichier ip ouvert\n") ;
 fgets(Buffer,sizeof Buffer,fp ) ;
 while(!feof(fp))
 {
  sscanf(Buffer,"%s %s",Nom,IPS);
  fprintf(stderr,"%s:%s;%s:\n",Nom,IPS,NomAResoudre) ;
  if ( strcmp(Nom,NomAResoudre)==0)
     if (Ipv4ToInt(IPS,&Ip)==-1)
        {
	 printf("IP invalide\n");
	 exit(1) ;
	}
     else
        return(Ip) ;
  /* on passe au suivant */
  fgets(Buffer,sizeof Buffer,fp ) ;
 }
 printf("On a rien trouvé\n") ;
 return(0) ;
};



