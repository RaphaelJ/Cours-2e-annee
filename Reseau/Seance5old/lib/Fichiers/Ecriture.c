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
 printf("%d\n",UnRecord->Numero ) ;
 printf("%d\n",UnRecord->Valeur ) ;
 printf("%s\n",UnRecord->Memo) ;
 printf("-----------------------\n") ;
 return ;
}

main()
{
 struct Record UnRecord ;
 FILE *sortie ;
 char NomFichier[80] ;
 char Redo ;

 printf("Le nom de fichier à creer :)") ;
 fgets(NomFichier,sizeof NomFichier,stdin) ;
 DelNewLine(NomFichier) ;
 sortie = fopen(NomFichier,"a") ; /* Si le fichier existe, on le cree sinon on ajoute */
 if ( sortie == NULL )
    {
     fprintf(stderr,"Echec Ouverture\n") ;
     exit(0) ;
    }
 else
    fprintf(stderr,"Ouverture reussie \n") ;
 setvbuf(sortie, (char *)NULL, _IOLBF, 0) ; /* ceci supprime la bufferisation */
 Redo='y' ;
 while ( Redo=='Y' || Redo=='y')
 {
  int nbr ;
  printf("Position actuelle dans le fichier %d\n",ftell(sortie)) ;
  SaiSieRecord(&UnRecord ) ;
  nbr = fwrite(&UnRecord,sizeof(UnRecord),1,sortie) ;
  fprintf(stderr,"%d Bytes écrits\n",nbr) ; /* affiche le nombre de record et pas de bytes */
  printf("Encoder un autre (Y/N) ?)") ;
  Redo=ReadChar() ;
 }
 fclose(sortie) ;
}
