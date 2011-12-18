# Makefile de Test 1

COMPILER=c++
OBJ=Test1.o Race.o

all: Test1.bin

Test1.bin:	$(OBJ)
	$(COMPILER) -o Test1.bin Test1.o Race.o

Test1.o:	Test1.cxx Race.o
	$(COMPILER) -c Test1.cxx

Race.o:	Race.cpp Race.h
	$(COMPILER) -c Race.cpp

clean:	clean_kate_temp
	rm ./*.bin
	rm $(OBJ)

clean_kate_temp:
	rm ./*~