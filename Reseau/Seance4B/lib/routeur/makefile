# routeur\makefile
all:	routeur	evlib.o	physlib.o	filterlib.o	tcplib.o	interfaces.o

physlib.o:	../physlib/physlib.h	../physlib/physlib.c
	echo "Compilation de physlib.o"
	cc -c ../physlib/physlib.c

evlib.o:	../evlib/evlib.c	../evlib/evlib.h
	echo "compilation de evlib"
	cc -c ../evlib/evlib.c

tcplib.o:	../tcplib/tcplib.c    ../tcplib/tcplib.h
	echo "compilation de tcplib.o"
	cc -c ../tcplib/tcplib.c

filterlib.o:	../filterlib/filterlib.h	../filterlib/filterlib.c
	echo "compilation de filterlib"
	cc -c ../filterlib/filterlib.c

interfaces.o:	../interfaces/interfaces.h	../interfaces/interfaces.c
	echo "compilation de interfaces"
	cc -c	../interfaces/interfaces.c

routeur:	routeur.c	../protocol/protocol.h	evlib.o	physlib.o filterlib.o	interfaces.o	tcplib.o
	echo "compilation de routeur"
	cc -o routeur routeur.c	evlib.o	physlib.o	filterlib.o	tcplib.o	interfaces.o	
