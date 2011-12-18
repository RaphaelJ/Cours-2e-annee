/*-------------------------------------------------------------------------
  Vanstapel Herman EPL


--------------------------------------------------------------------------

------------------------------------------------------------------------*/

#include <unistd.h>
#include <assert.h>
#include "interfaces.h"


void InternalIpv4ToS(unsigned int ip,char *str)
{
  int NM[4] ;
  if (ip==0)
      strcpy(str,"0.0.0.0") ;
  else
     {
      NM[0] = ( ip >> 24 ) & 255 ;
      NM[1] = ( ip >> 16 ) & 255 ;
      NM[2] = ( ip >> 8 ) & 255 ;
      NM[3] = ip & 255 ;
      sprintf(str,"%d.%d.%d.%d",NM[0],NM[1],NM[2],NM[3]) ;
     } 
}

struct Interface  *CreationInterface( char *NomInterface ,struct Interface *pl) 
{
 struct Interface *pcur ;
  pcur = (struct Interface *) malloc(sizeof(struct Interface)) ;
  strncpy(pcur->INomInterface,NomInterface,sizeof(pcur->INomInterface)) ;
  pcur->Ipsuiv = pl ;
  pcur->ILiaison =-1;    ; 	 /* Le premier est sacrifie  et Liaison contient le descripteur */
  pcur->IIP = -1 ;         /* Donne les adresses IP des lignes */
  pcur->ILigne = -1  ;      /* Numero de la ligne ou Interface */
  pcur->IEntreeTableRoutage =-1 ;
  fprintf(stderr,"le nouveau nom est %s \n",pcur->INomInterface) ;
  return(pcur) ;
}

struct Interface * AjouteInterface( char *NomInterface ,struct Interface *pl)
{
 struct Interface *pcur,*pprec,*pn ; 
 pcur = pl ;
 if ( pcur == NULL ) /* Creation du tout premier element */ 
     return(CreationInterface(NomInterface ,NULL) ) ;
 else
 {
  /* On ajoute l element �la fin de la liste  */

  pprec = pcur ;
  while ( pcur != NULL )
    {
     //fprintf(stderr,">> %s \n",pcur->INomInterface ) ;
     if ( strcmp(pcur->INomInterface , NomInterface )==0  )
     /* si l interface existe deja , on ne fait rien */ 
        return(NULL) ;
     pprec = pcur ;
     pcur  = pcur->Ipsuiv ;
    }
  /*---   Construction de la nouvelle interface  ---*/
  pn = CreationInterface(NomInterface ,pcur) ;
  /*-----  insert ion au bon endroit en tete ( pcur == pprec ) ou au milieu -*/
  if ( pcur == pprec )
     pl = pn ;    	
  else
     pprec -> Ipsuiv = pn ;
  return( pl ) ;
 }
}

struct Interface *RechercheInterfaceNom(char *NomInterface,struct Interface *pl)
{ 
 if ( pl == NULL )
     return(pl) ;
 while ( pl != NULL )
    {
     fprintf(stderr,"Recherche Nom %s \n",pl->INomInterface ) ;
     if ( strcmp(pl->INomInterface , NomInterface )==0  )
     /* si l interface existe deja , on ne fait rien */ 
        return(pl) ;
     pl  = pl->Ipsuiv ;
    }
 return(pl) ;
}

struct Interface *RechercheInterfaceDesc(int Desc,struct Interface *pl)
{  ;
 struct Physique * PP ; 
 if ( pl == NULL )
     return(pl) ;
 while ( pl != NULL )
    {
     PP = pl->IPhys ;
     if ((PP)->desc==Desc  )
     /* si l interface existe deja , on ne fait rien */ 
        return(pl) ;
     pl  = pl->Ipsuiv ;
    }
 return(pl) ;
}

struct Interface *RechercheInterfaceLigne(int Ligne,struct Interface *pl)
{  ;
 struct Physique * PP ;
 if ( pl == NULL )
     return(pl) ;
 while ( pl != NULL )
    {
     if ((pl->ILigne)==Ligne  )
     /* si l interface existe deja , on ne fait rien */ 
        return(pl) ;
     pl  = pl->Ipsuiv ;
    }
 return(pl) ;
}

struct Interface *SupprimeInterface(char *NomInterface , struct Interface *pl)
{
 struct Interface  *pcur, *pprec ;
 if ( pl == NULL )
    return(NULL) ;
 else
    {
     pprec = pcur = pl ;
     while( pcur != NULL )
     {
      if ( strcmp(pcur->INomInterface ,NomInterface )== 0 ) /* Suppression de la t�e */
	 if ( pcur == pprec )
            {
              pl = pcur->Ipsuiv ;
              free(pcur) ;
              return(pl) ;  
            }
         else
            {
             pprec->Ipsuiv = pcur ->Ipsuiv ;                 
	     free(pcur) ; 		   
             return(pl) ;
            }
        pprec = pcur ;    
	pcur=pcur->Ipsuiv ; 
     }
     return(pl) ;
    }
}

struct Interface *InterfaceSuivante( struct Interface *pi ) 
{
 return( pi->Ipsuiv ) ;
}

void AfficheInterfaces(struct Interface *pl)
{
 char Buffer[22] ;

 while(pl != NULL )
 {
   fprintf(stderr,"-------------------------\n") ;
   fprintf(stderr,"Ligne %d \n" ,	 pl->ILigne ) ;
   fprintf(stderr,"Liaison (Descripteur) %d \n",       pl-> ILiaison ) ;
   fprintf(stderr,"Nom Interface %s \n", pl->INomInterface ) ;
   fprintf(stderr,"Numero dans la table de routage %d \n", pl->IEntreeTableRoutage ) ;
   InternalIpv4ToS(pl->IIP,Buffer) ;
   fprintf(stderr,"IP %s \n", Buffer ) ;
   pl = pl ->Ipsuiv ;
 }
 printf(".\n") ;
}

void ModifiePhys(struct Physique *Phys,struct Interface *pl)
{
 assert(pl!=NULL) ;
 pl->IPhys = Phys ;
}

void ModifieLiaison(int Liaison,struct Interface *pl)
{
 assert(pl!=NULL) ;
 pl->ILiaison = Liaison ;
}

void ModifieIP(int IP,struct Interface *pl)
{
 assert(pl!=NULL) ;
 pl->IIP = IP ;
}

void ModifieLigne(int Ligne,struct Interface *pl)
{
 assert(pl!=NULL) ;
 pl->ILigne = Ligne ;
}

void ModifieNomInterface(char *NomInterface,struct Interface *pl)
{
 assert(pl!=NULL) ;
 strncpy(pl->INomInterface,NomInterface,sizeof(pl->INomInterface)) ;
}

void ModifieEntreeTableRoutage(int NER, struct Interface *pl) 
{
 assert(pl!=NULL) ;
 pl->IEntreeTableRoutage = NER ; 
}

 struct Physique *ObtenirPhys(struct Interface *pl)
{
 assert(pl!=NULL) ;
 return(pl->IPhys) ;
}

int ObtenirLiaison(struct Interface *pl)
{
 assert(pl!=NULL) ;
 return(pl->ILiaison) ;
}

int ObtenirIP(struct Interface *pl)
{
 assert(pl!=NULL) ;
 return(pl->IIP) ;
}

int ObtenirLigne(struct Interface *pl)
{
 assert(pl!=NULL) ;
 return(pl->ILigne) ;
}

char* ObtenirNomInterface(struct Interface *pl)
{
 assert(pl!=NULL) ;
 return(pl->INomInterface) ;
}

int ObtenirEntreeTableRoutage(struct Interface *pl)
{
 assert(pl!=NULL) ;
 return(pl->IEntreeTableRoutage) ;
}

