# Premier Makefile

A1_PATH=A1
ECRAN_PATH=Ecran
TRACE_PATH=Trace

COMPILER=cc -I $(ECRAN_PATH) -I $(TRACE_PATH)
OBJ=A1.o Ecran.o Trace.o

all: App

App:	$(OBJ)
	$(COMPILER) -o A1.bin $(OBJ)

A1.o:	$(A1_PATH)/A1.c $(A1_PATH)/A1.h $(ECRAN_PATH)/Ecran.h $(TRACE_PATH)/Trace.h
	$(COMPILER) -c $(A1_PATH)/A1.c

Ecran.o:	$(ECRAN_PATH)/Ecran.c $(ECRAN_PATH)/Ecran.h
	$(COMPILER) -c $(ECRAN_PATH)/Ecran.c

Trace.o:	$(TRACE_PATH)/Trace.c $(TRACE_PATH)/Trace.h
	$(COMPILER) -c $(TRACE_PATH)/Trace.c

clean_kate_temp:
	rm ./*~

clean:
	rm A1.bin
	rm ./$(OBJ)