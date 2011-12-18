/******************************************
  Herman Vanstapel
  2007
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

void DelNewLine(char *Chaine)
{
 Chaine[strlen(Chaine)-1] = 0 ;
}

char ReadChar()
{
 char Tampon[80] ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 return Tampon[0] ;
} 


void AfficheRecord(struct Record *UnRecord)
{
printf("%d\n",UnRecord->Numero ) ;
 printf("%d\n",UnRecord->Valeur ) ;
 printf("%s\n",UnRecord->Memo) ;
 printf("-----------------------\n") ;
}

void SaiSieRecord(struct Record *UnRecord )
{
 char Tampon[80] ;
 printf("Saisie numero :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Numero = atoi(Tampon) ;
 printf("Saisie valeur :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 UnRecord -> Valeur = atoi(Tampon) ;
 printf("Saisie Tampon :") ;
 fgets(UnRecord->Memo,sizeof UnRecord->Memo,stdin ) ;
 DelNewLine(UnRecord->Memo) ;
 AfficheRecord(UnRecord) ;
 return ;
}

main()
{
 struct Record UnRecord ;
 FILE *sortie ;
 char NomFichier[80] ;
 char Tampon[80] ;
 int  Numero ;
 int  nbr ;

 printf("Le nom de fichier à Lire :)") ;
 fgets(NomFichier,sizeof NomFichier,stdin) ;
 DelNewLine(NomFichier) ;
 sortie = fopen(NomFichier,"r") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;

 printf("Saisie numero :") ;
 fgets(Tampon,sizeof Tampon,stdin ) ;
 Numero = atoi(Tampon) ;
 nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
 
 while ( !feof(sortie) && UnRecord.Numero != Numero )
 {
  int nbr ;
  fprintf(stderr,"Record lu %d et Position actuelle dans le fichier %d\n",nbr,ftell(sortie)) ;
  nbr = fread(&UnRecord,sizeof(UnRecord),1,sortie) ;
 }
 if ( !feof(sortie) )
	AfficheRecord(&UnRecord) ;
 fclose(sortie) ;
}
