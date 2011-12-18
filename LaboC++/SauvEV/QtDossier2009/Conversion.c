#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "Fichier.ini"

LIVRE	Livre;
int hdF1,hdF2;

int main()
{
//hdF1 = open("StockLivre.dat", O_RDWR);
hdF2 = open("StockLivreSUN.dat", O_RDWR);

perror("--");
int i = 1;
while (read(hdF2,&Livre,sizeof(Livre)))
   { //Livre.Numero = i;
     //write(hdF2,&Livre,sizeof(Livre));
     printf("lu : %d %s\n",Livre.Numero,Livre.Titre);
     i++;
perror("zz");
   }
}

