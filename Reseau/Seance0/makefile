OBJ=CreaTransacServeur.o Informations.o
CC=cc

all:	CreaTransacServeur

CreaTransacServeur:	$(OBJ)
	@echo "[OK] creation de CreaTransacServeur"
	@$(CC) -o CreaTransacServeur $(OBJ)

Informations.o:	Informations.h Informations.c
	$(CC) -c Informations.c

CreaTransacServeur.o:	CreaTransacServeur.c Informations.o
	@echo "[OK] creation de CreaTransacServeur.o"
	@$(CC) -c CreaTransacServeur.c

clean:
	@echo "[OK] Clean up"
	@rm infos *.o *~
	
	
