# couches\makefile
# makefile unpc

all:	unpc	dnslib.o	evlib.o		tcplib.o	physlib.o

physlib.o:	../physlib/physlib.h	../physlib/physlib.c
	echo "Compilation de physlib.o"
	cc -c ../physlib/physlib.c

evlib.o:	../evlib/evlib.c	../evlib/evlib.h
	echo "compilation de evlib"
	cc -c ../evlib/evlib.c

tcplib.o:	../tcplib/tcplib.c	../tcplib/tcplib.h
	echo "compilation de tcplib.o"
	cc -c ../tcplib/tcplib.c

dnslib.o:	../dnslib/dnslib.h	../dnslib/dnslib.c   
	echo "compilation de dnslib"
	cc -c ../dnslib/dnslib.c
			
unpc:	unpc.c	dnslib.o	evlib.o		physlib.o	tcplib.o
	echo "compilation de clientpc"
	cc -o unpc	unpc.c evlib.o	physlib.o	tcplib.o	dnslib.o  
