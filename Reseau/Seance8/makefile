LIBS=Informations.o Reseau.o FichierTransactions.o physlib.o tcplib.o evlib.o evtmlib.o timerlib.o
CC=gcc -ggdb

all:	BarriereEntree BornePaiement BarriereSortie Serveur CreaTransacServeur

BarriereEntree:	BarriereEntree.h BarriereEntree.c $(LIBS)
		@echo "Creation de BarriereEntree"
		@$(CC) -o BarriereEntree BarriereEntree.c $(LIBS)

BornePaiement:	BornePaiement.h BornePaiement.c $(LIBS)
		@echo "Creation de BornePaiement"
		@$(CC) -o BornePaiement BornePaiement.c $(LIBS)

BarriereSortie:	BarriereSortie.h BarriereSortie.c $(LIBS)
		@echo "Creation de BarriereSortie"
		@$(CC) -o BarriereSortie BarriereSortie.c $(LIBS)

Serveur:	Serveur.h Serveur.c $(LIBS)
		@echo "Creation de Serveur"
		@$(CC) -o Serveur Serveur.c $(LIBS)

CreaTransacServeur:	CreaTransacServeur.c CreaTransacServeur.h $(LIBS)
		@echo "Creation de CreaTransacServeur"
		@$(CC) -o CreaTransacServeur CreaTransacServeur.c $(LIBS)

Informations.o:	Informations.c Informations.h
		@echo "Creation de Informations.o"
		@$(CC) -c Informations.c

Reseau.o:	Reseau.c Reseau.h
		@echo "Creation de Reseau.o"
		@$(CC) -c Reseau.c

FichierTransactions.o:	FichierTransactions.c FichierTransactions.h
		@echo "Creation de FichierTransactions.o"
		@$(CC) -c FichierTransactions.c

physlib.o:	lib/physlib/physlib.h lib/physlib/physlib.c
		@echo "Creation de physlib.o"
		@$(CC) -c lib/physlib/physlib.c

tcplib.o:	lib/tcplib/tcplib.h lib/tcplib/tcplib.c
		echo "Creation de tcplib.o"
		@$(CC) -c lib/tcplib/tcplib.c 

evlib.o:	lib/evlib/evlib.h lib/evlib/evlib.c
		@echo "Creation de evlib.c"
		@$(CC) -c lib/evlib/evlib.c 

evtmlib.o:	lib/evtmlib/evtmlib.h lib/evtmlib/evtmlib.c
		@echo "Creation de evtmlib.c"
		@$(CC) -c lib/evtmlib/evtmlib.c 

timerlib.o:	lib/timerlib/timerlib.h lib/timerlib/timerlib.c
		@echo "Creation de timerlib.c"
		@$(CC) -c lib/timerlib/timerlib.c 

clean:
	@echo "Clean Up"
	rm BarriereEntree Serveur CreaTransacServeur *.o *~