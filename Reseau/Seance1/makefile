CLI=Client.c Informations.o physlib.o tcplib.o
SER=Serveur.c Informations.o physlib.o tcplib.o
CC=gcc

all: BarriereEntree Serveur

BarriereEntree:	$(CLI)
		@echo "Creation de BarriereEntree"
		@$(CC) -o BarriereEntree $(CLI)

Serveur:	$(SER)
		@echo "Creation de Serveur"
		@$(CC) -o Serveur $(SER)

Informations.o:	Informations.c Informations.h
		@echo "Creation de Informations.o"
		@$(CC) -c Informations.c

physlib.o:	../lib/physlib/physlib.h ../lib/physlib/physlib.c
		@echo "Creation de physlib.o"
		@cc -c ../lib/physlib/physlib.c

tcplib.o:	../lib/tcplib/tcplib.h ../lib/tcplib/tcplib.c
		echo "Creation de tcplib.o"
		cc -c ../lib/tcplib/tcplib.c 

clean:
	@echo "Clean Up"
	rm BarriereEntree infos Serveur *.o *~