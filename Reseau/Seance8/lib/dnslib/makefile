# couches\makefile
# makefile serveurdns

all:	dnslib  evlib.o	tcplib.o	physlib.o

physlib.o:	../physlib/physlib.h	../physlib/physlib.c
	echo "Compilation de physlib.o"
	cc -c ../physlib/physlib.c

evlib.o:	../evlib/evlib.c	../evlib/evlib.h
	echo "compilation de evlib"
	cc -c ../evlib/evlib.c

tcplib.o:	../tcplib/tcplib.h
	echo "compilation de tcplib.o"
	cc -c ../tcplib/tcplib.c

dnslib:	dnslib.c	evlib.o	physlib.o	tcplib.o
	echo "compilation de servicedns"
	cc -c dnslib.c	
