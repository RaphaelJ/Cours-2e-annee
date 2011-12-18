# CIP\makefile

all:	essai	physlib.o	tcplib.o

physlib.o:	../physlib/physlib.h	../physlib/physlib.c
	echo "Compilation de physlib.o"
	cc -c ../physlib/physlib.c

tcplib.o:	../tcplib/tcplib.h	../tcplib/tcplib.c
	echo "Compilation de tcplib.o"
	cc -c ../tcplib/tcplib.c 

essai:	essai.c	physlib.o	tcplib.o
	echo "Compilation de essai"
	cc  -o essai  essai.c physlib.o tcplib.o

