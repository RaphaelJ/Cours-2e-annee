# cphexS\makefile

all:	cli	ser	physlib.o	tcplib.o

physlib.o:	../physlib/physlib.h	../physlib/physlib.c
	echo "Compilation de physlib.o"
	cc -c ../physlib/physlib.c

tcplib.o:	../tcplib/tcplib.h	../tcplib/tcplib.c
	echo "Compilation de tcplib.o"
	cc -c ../tcplib/tcplib.c 

cli:	cli.c	physlib.o	tcplib.o	structure.h
	echo "Compilation de client"
	cc  -o cli  cli.c physlib.o tcplib.o

ser:	ser.c	physlib.o	tcplib.o	structure.h
	echo "Compilation de serveur"
	cc -o ser  ser.c physlib.o tcplib.o

