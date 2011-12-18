.SILENT:

ECRANX=../EcranX
ECRAN=../Ecran
GRILLE=../Grille

CC=gcc -I$(ECRANX) -I$(ECRAN) -I$(GRILLE)
FLAGS= -Wall -O -W
ALL: Tetris
OBJS = $(ECRAN)/Ecran.o $(ECRANX)/EcranX.o $(GRILLE)/Grille.o  
PROGRAMS = Tetris

Tetris:	Tetris.c $(ECRAN)/Ecran.o $(ECRANX)/EcranX.o $(GRILLE)/Grille.o
	echo Creation de Tetris...
	$(CC) $(FLAGS) Tetris.c -o Tetris $(ECRAN)/Ecran.o $(ECRANX)/EcranX.o $(GRILLE)/Grille.o -lrt -L/usr/X11R6/lib -lX11 -lpthread

$(ECRAN)/Ecran.o:	$(ECRAN)/Ecran.c $(ECRAN)/Ecran.h
		echo Creation de Ecran.o ...
		$(CC) $(FLAGS) -c $(ECRAN)/Ecran.c
		mv Ecran.o $(ECRAN)

$(ECRANX)/EcranX.o:	$(ECRANX)/EcranX.c $(ECRANX)/EcranX.h
		echo Creation de EcranX.o ...
		$(CC) $(FLAGS) -c $(ECRANX)/EcranX.c
		mv EcranX.o $(ECRANX)

$(GRILLE)/Grille.o:	$(GRILLE)/Grille.c $(GRILLE)/Grille.h
		echo Creation de Grille.o ...
		$(CC) $(FLAGS) -c $(GRILLE)/Grille.c
		mv Grille.o $(GRILLE)

clean:
	@rm -f $(OBJS) core

clobber:	clean
	@rm -f tags $(PROGRAMS)
