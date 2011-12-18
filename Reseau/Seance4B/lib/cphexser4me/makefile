#  Cpheser4me\makefile

all:	cli	ser	physlib.o	tcplib.o

physlib.o:	../physlib/physlib.h	../physlib/physlib.c
	echo "Compilation de physlib.o"
	cc -c ../physlib/physlib.c

tcplib.o:	../tcplib/tcplib.h	../tcplib/tcplib.c
	echo "Compilation de tcplib.o"
	cc -c ../tcplib/tcplib.c

evlib.o:	../evlib/evlib.c	../evlib/evlib.h
	echo "Compilation de evlib.c"
	cc -c ../evlib/evlib.c 

timerlib.o:	../timerlib/timerlib.c	../timerlib/timerlib.h
	echo "Compilation de timerlib.o"
	cc -c ../timerlib/timerlib.c

evtmlib.o:	../evtmlib/evtmlib.c	../evtmlib/evtmlib.h	../timerlib/timerlib.o
	echo "Compilation de evtmlib.o"
	cc -c ../evtmlib/evtmlib.c

cli:	cli.c	physlib.o	tcplib.o	timerlib.o	evlib.o		evtmlib.o
	echo "Compilation de client"
	cc  -o cli  cli.c physlib.o tcplib.o timerlib.o evlib.o evtmlib.o

ser:	ser.c	physlib.o	tcplib.o	evlib.o	
	echo "Compilation de serveur"
	cc -o ser  ser.c physlib.o tcplib.o evlib.o

