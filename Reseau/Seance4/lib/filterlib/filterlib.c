



/*--------------------------------------------------------------------------------------------------------------------------------------
 -------------------------------------------------------------------
 Vanstapel Herman EPL

 L'objectif de ce programme est de construire un noyau de firewall

 version 2004
 Utilisation d'une trame.
---------------------------------------------------------------------
 C'est la couche liaison
---------------------------------------------------------------------------------------------------------------------------------------*/

#include "filterlib.h"
#include <string.h>
#include "../tcplib/tcplib.h"

int FiltragePaquet(int LigneEntree,struct Regle TableFiltrage[],int NbrRegles, struct Paquet* PP,int *R)
{
 struct Segment *PS ;
 char Tampon[80] ;
 int i = 0 ;
 PS = ( struct Segment * ) PP->Buffer ;
 for( i = 0 ;i < NbrRegles ; i++ )
 {
  *R= i+1 ;
  fprintf(stderr,"\nReseau: Regle %d",*R ) ;
  if ( (TableFiltrage[i].LigneEntree !=0) && (TableFiltrage[i].LigneEntree != LigneEntree ))
     continue ;
  fprintf(stderr,"LE,") ;
  Ipv4ToS((PP->IPSource & generer_masque(TableFiltrage[i].MasqueS)), Tampon) ;
  fprintf(stderr,"R Masque %s \n",Tampon ) ;
  if ( (TableFiltrage[i].IPSource!=0) && (TableFiltrage[i].IPSource  != (PP->IPSource & generer_masque(TableFiltrage[i].MasqueS)) ))
     continue ;
  fprintf(stderr,"IPS,");   
  if ( (TableFiltrage[i].IPDestination!=0) && (TableFiltrage[i].IPDestination != (PP->IPDestination & generer_masque(TableFiltrage[i].MasqueD)) ))
     continue ;
  fprintf(stderr,"IPD,") ;   
  if ( (TableFiltrage[i].PortSource!=0) && (TableFiltrage[i].PortSource != PS->PortSource ))
     continue ;
  fprintf(stderr,"PS,") ;   
  if ( (TableFiltrage[i].PortDestination!=0) && (TableFiltrage[i].PortDestination != PS->PortDestination ))
     continue ;
  fprintf(stderr,"PD,") ;   
  if (TableFiltrage[i].Protocole!= IP)
     if ( (TableFiltrage[i].Protocole!=0) && (TableFiltrage[i].Protocole != PP->Protocole ))
        continue ;
  fprintf(stderr,"Protocole.") ;	
  if(TableFiltrage[i].Politique==DROP)
    return 1 ;
  if(TableFiltrage[i].Politique==ACCEPT)
    return 0 ;
 }
 *R = 0 ;
 return (0 );
}

void LectureTableFiltrage(char *NomFichier,struct Regle TableFiltrage[],int *NbrRegles,int NbrLignes)
{
 FILE *FichierRegles ;
 char LigneFichier[200] ;
 int Ligne,MS, MD, PortSource, PortDestination ;
 char IPSource[80],IPDestination[80],Politique[80],Protocole[80] ;
 
 FichierRegles = fopen(NomFichier,"r") ;
 if ( FichierRegles == NULL )
    {
     printf("Fichier de filtrage non ouvert \n") ;
     exit(0) ;
    }
 else
    printf("Ouverture de regles \n") ;
 *NbrRegles = 0 ;
 fgets(LigneFichier,sizeof LigneFichier,FichierRegles) ;
 while(!feof(FichierRegles))
 {
  printf(" >-> %c \n",LigneFichier[0] ) ;
  if (LigneFichier[0]=='#')
      ; 
  else
  	{
sscanf(LigneFichier,"%d %s \\ %d %s \\ %d %d %d %s %s\n",&Ligne,IPSource,&MS,IPDestination,&MD,&PortSource,&PortDestination,Protocole,Politique) ;
	 printf("%d %s \\ %d %s \\ %d %d %d %s %s\n",Ligne,IPSource,MS,IPDestination,MD,PortSource,PortDestination,Protocole,Politique ) ;
  	 if ( Ipv4ToInt(IPSource,&TableFiltrage[*NbrRegles].IPSource)== -1 )
      	   {
            printf(" Le param�re 2 n'est pas une ip\n") ;
            exit(0) ;
           }
  	 if ( Ipv4ToInt(IPDestination,&TableFiltrage[*NbrRegles].IPDestination)== -1 )
           {
            printf(" Le param�re 3 n'est pas une ip\n") ;
            exit(0) ;
      	   }
         if ( ( MS > 32 ) || ( MS < 0 ) )
	    {
             printf("Le masque source n'est pas bon %d \n", MS ) ;
	     exit(0) ;
            }
         else
	    TableFiltrage[*NbrRegles].MasqueS = MS ;
         if ( ( MD > 32 ) || ( MD < 0 ) )
	    {
             printf("Le masque destination n'est pas bon %d \n", MD ) ;
	     exit(0) ;
            }
	 else
            TableFiltrage[*NbrRegles].MasqueD = MD ;
  	 if (strcmp(Protocole,"IP")==0 )
     	   if (( PortSource == 0) && ( PortDestination == 0))
              TableFiltrage[*NbrRegles].Protocole = IP ;
           else
              {
               printf("placer des ports avec une r�le ip non sens \n") ;
	       exit(0) ;
              }
         else
    	   if (strcmp(Protocole,"UDP")==0 )
              TableFiltrage[*NbrRegles].Protocole = UDP ;
           else
              if (strcmp(Protocole,"TCP")==0 )
                 TableFiltrage[*NbrRegles].Protocole = TCP ;
              else
                 {
                  printf(" Le param�re 6 n'est pas un protocole valide \n") ;
                  exit(0) ;
                 }

         if (strcmp(Politique,"DROP")==0 )
            TableFiltrage[*NbrRegles].Politique = DROP ;
         else
            if (strcmp(Politique,"ACCEPT")==0 )
               TableFiltrage[*NbrRegles].Politique = ACCEPT ;
            else
               {
                printf(" Le param�re 7 n'est pas une politique valide \n") ;
                exit(0) ;
               }
  	if (Ligne <= NbrLignes )
      	   TableFiltrage[*NbrRegles].LigneEntree = Ligne ;
  	else
     	   {

            printf(" La ligne %d n'existe pas \n",Ligne) ;
            exit(0) ;
     	   }
        TableFiltrage[*NbrRegles].PortSource = PortSource ;
        TableFiltrage[*NbrRegles].PortDestination = PortDestination ;
        (*NbrRegles)++ ;
       }
  fgets(LigneFichier,sizeof LigneFichier,FichierRegles) ;
 }
 fclose(FichierRegles) ;
}

void AffichageTableFiltrage(struct Regle TableFiltrage[],int NbrRegles)
{
 int I = 0 ;
 char Buffer[80] ;
 while ( I < NbrRegles )
 {
  printf("%d ",TableFiltrage[I].LigneEntree ) ;
  Ipv4ToS(TableFiltrage[I].IPSource,Buffer ) ;
  printf("%s ",Buffer ) ;
  printf(" \\ %d ", TableFiltrage[I].MasqueS ) ;
  Ipv4ToS(TableFiltrage[I].IPDestination,Buffer ) ;
  printf("%s ",Buffer ) ;
  printf(" \\ %d ", TableFiltrage[I].MasqueD ) ;
  printf("%d ",TableFiltrage[I].PortSource ) ;
  printf("%d ",TableFiltrage[I].PortDestination ) ;

  if (TableFiltrage[I].Protocole == IP )
      printf("IP ") ;
  else
    if (TableFiltrage[I].Protocole == UDP )
           printf("UDP ") ;
    else
       if (TableFiltrage[I].Protocole == TCP )
           printf("TCP ") ;
       else
	   {
	    printf("Politique non connue \n") ;
	    exit(0) ;
	   }

  if (TableFiltrage[I].Politique == DROP )
      printf("DROP \n") ;
  else
    if (TableFiltrage[I].Politique == ACCEPT )
           printf("ACCEPT \n") ;
        else
	   {
	    printf("Politique non connue \n") ;
	    exit(0) ;
	   }
  I++ ;
 }
}
