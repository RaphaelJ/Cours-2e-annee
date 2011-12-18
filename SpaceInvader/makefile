ECRANX=EcranX
ECRAN=Ecran
GRILLE=Grille

CC=g++ -DLINUX -pthread -lrt -L/usr/X11R6/lib -lX11 -lpthread
ALL: SpaceInvader
OBJS = $(ECRAN)/Ecran.o $(ECRANX)/EcranX.o $(GRILLE)/Grille.o Canon.o Missile.o Bombe.o \
Aliens.o ReadChar.o Utils.o Score.o
PROGRAMS = SpaceInvader

SpaceInvader:	SpaceInvader.c $(OBJS)
	$(CC) SpaceInvader.c -o SpaceInvader $(OBJS)

$(ECRAN)/Ecran.o:	$(ECRAN)/Ecran.c $(ECRAN)/Ecran.h
	$(CC) -c $(ECRAN)/Ecran.c
	mv Ecran.o $(ECRAN)

$(ECRANX)/EcranX.o:	$(ECRANX)/EcranX.c $(ECRANX)/EcranX.h
	$(CC) -c $(ECRANX)/EcranX.c
	mv EcranX.o $(ECRANX)

$(GRILLE)/Grille.o:	$(GRILLE)/Grille.c $(GRILLE)/Grille.h
	$(CC) -c $(GRILLE)/Grille.c
	mv Grille.o $(GRILLE)

Canon.o:	Canon.h Canon.c Defines.h
	$(CC) -c Canon.c

Missile.o:	Missile.h Missile.c Defines.h
	$(CC) -c Missile.c

Bombe.o:	Bombe.h Bombe.c Defines.h
	$(CC) -c Bombe.c

Aliens.o:	Aliens.h Aliens.c Defines.h
	$(CC) -c Aliens.c

Score.o:	Score.h Score.c Defines.h
	$(CC) -c Score.c

ReadChar.o:	ReadChar.h ReadChar.c Defines.h
	$(CC) -c ReadChar.c

Utils.o:	Utils.h Utils.c Defines.h
	$(CC) -c Utils.c

clean:
	rm -f $(OBJS) core
