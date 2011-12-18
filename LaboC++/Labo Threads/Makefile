COMPILER=g++ -ggdb -pthread -D_REENTRANT

all:	Labo2.bin Labo1.bin Labo3a.bin Labo3b.bin

Labo1.bin:	Labo1.cpp
	$(COMPILER) -o Labo1.bin Labo1.cpp

Labo2.bin:	Labo2.cpp
	$(COMPILER) -o Labo2.bin Labo2.cpp

Labo3a.bin:	Labo3a.cpp
	$(COMPILER) -o Labo3a.bin Labo3a.cpp

Labo3b.bin:	Labo3b.cpp
	$(COMPILER) -o Labo3b.bin Labo3b.cpp

clean:	clean_kate_temp
	rm -f ./*.bin
	rm -f ./*.o

clean_kate_temp:
	rm -f ./*~
