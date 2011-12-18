# Makefile des Test

COMPILER=g++ -ggdb -foptimize-sibling-calls

CIRCUITS_DIR=Circuits/
CIRCUITS_OBJ=$(CIRCUITS_DIR)/Circuits.o

all: Tests

Tests: Test2.bin Test3.bin Test4.bin Test5.bin Test6.bin Test7.bin RacingWorldChampionship

Test2.bin: Test2.o $(CIRCUITS_OBJ)
	$(COMPILER) Test2.o $(CIRCUITS_OBJ) -o Test2.bin

Test2.o:	Test2.cxx
	$(COMPILER) -c Test2.cxx

Test3.bin: Test3.o $(CIRCUITS_OBJ)
	$(COMPILER) Test3.o $(CIRCUITS_OBJ) -o Test3.bin

Test3.o:	Test3.cxx
	$(COMPILER) -c Test3.cxx

Test4.bin: Test4.o $(CIRCUITS_OBJ)
	$(COMPILER) Test4.o $(CIRCUITS_OBJ) -o Test4.bin

Test4.o:	Test4.cxx
	$(COMPILER) -c Test4.cxx

Test5.bin: Test5.o $(CIRCUITS_OBJ)
	$(COMPILER) Test5.o $(CIRCUITS_OBJ) -o Test5.bin

Test5.o:	Test5.cxx
	$(COMPILER) -c Test5.cxx

Test6.bin: Test6.o $(CIRCUITS_OBJ)
	$(COMPILER) Test6.o $(CIRCUITS_OBJ) -o Test6.bin

Test6.o:	Test6.cxx Circuits/MyVector.h Circuits/MyVector.cpp Circuits/MyList.h Circuits/MyList.cpp Circuits/MySortedList.h Circuits/MySortedList.cpp Circuits/List.h Circuits/List.cpp Circuits/Node.h
	$(COMPILER) -c Test6.cxx


Test7.bin: Test7.o $(CIRCUITS_OBJ)
	$(COMPILER) Test7.o $(CIRCUITS_OBJ) -o Test7.bin

Test7.o:	Test7.cxx Circuits/MyVector.h Circuits/MyVector.cpp Circuits/MyList.h Circuits/MyList.cpp Circuits/MySortedList.h Circuits/MySortedList.cpp Circuits/List.h Circuits/List.cpp Circuits/Node.h Circuits/FichierBinaire.h Circuits/FichierBinaire.cpp
	$(COMPILER) -c Test7.cxx

RacingWorldChampionship:	RacingWorldChampionship.o $(CIRCUITS_OBJ)
	$(COMPILER) RacingWorldChampionship.o $(CIRCUITS_OBJ) -o RacingWorldChampionship.bin

RacingWorldChampionship.o:	RacingWorldChampionship.cpp Circuits/MyVector.h Circuits/MyVector.cpp Circuits/MyList.h Circuits/MyList.cpp Circuits/MySortedList.h Circuits/MySortedList.cpp Circuits/List.h Circuits/List.cpp Circuits/Node.h Circuits/FichierBinaire.h Circuits/FichierBinaire.cpp
	$(COMPILER) -c RacingWorldChampionship.cpp

$(CIRCUITS_OBJ):	force
	cd $(CIRCUITS_DIR) && make all

force:

clean:	clean_kate_temp
	rm -f ./*.bin
	rm -f ./*.o
	cd $(CIRCUITS_DIR) && make clean

clean_kate_temp:
	rm -f ./*~
	cd $(CIRCUITS_DIR) && make clean_kate_temp
