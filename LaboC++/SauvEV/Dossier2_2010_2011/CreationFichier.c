#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define	false	0
#define	true	1
int hdF;

typedef struct
   { char 	Nom[20];
     char	Date[11];
     char	Salle[20];
     int	Libre;
   } CONCERT;

main()
{
CONCERT 	C;
hdF = open("Concert.dat",O_RDWR);

printf("Taille : %d\n",sizeof(CONCERT));
strcpy(C.Nom,"Bob Dylan");
strcpy(C.Date,"01/10/2011");
strcpy(C.Salle,"F.N.");
C.Libre = 150;

write(hdF,&C,sizeof(CONCERT));
strcpy(C.Nom,"Eddy Mitchell");
strcpy(C.Date,"02/12/2011");
strcpy(C.Salle,"Forum Lg");
C.Libre = 150;
write(hdF,&C,sizeof(CONCERT));

strcpy(C.Nom,"ZZ Top ");
strcpy(C.Date,"12/02/2011");
strcpy(C.Salle,"S.P. Anvers");
C.Libre = 150;
write(hdF,&C,sizeof(CONCERT));
}


