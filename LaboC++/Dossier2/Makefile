COMPILER=g++ -ggdb -foptimize-sibling-calls

BIN_DIR=./bin
OBJECTS_DIR=$(BIN_DIR)/obj
#QT=$(pkg-config --cflags --libs qt-mt)
QT=-DQT_SHARED -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -D_REENTRANT -I/opt/qt/include -L/opt/qt/lib -L/usr/X11R6/lib64 -lqt-mt -lpng -lz -lGL -lXmu -lXrender -lXrandr -lXcursor -lXinerama -lXft -lfreetype -lfontconfig -lXext -lX11 -lm -lSM -lICE -ldl -lpthread

all: $(BIN_DIR)/Borne $(BIN_DIR)/Serveur $(BIN_DIR)/Reservation $(BIN_DIR)/Publicite $(BIN_DIR)/GestServ

$(BIN_DIR)/Borne:	$(OBJECTS_DIR)/Ecran.o $(OBJECTS_DIR)/BorneReservation.o $(OBJECTS_DIR)/moc_BorneReservation.o $(OBJECTS_DIR)/Commons.o $(OBJECTS_DIR)/IndexedElement.o Borne.cpp 
	$(COMPILER) $(QT) -o $(BIN_DIR)/Borne Borne.cpp $(OBJECTS_DIR)/BorneReservation.o $(OBJECTS_DIR)/moc_BorneReservation.o $(OBJECTS_DIR)/Commons.o $(OBJECTS_DIR)/IndexedElement.o $(OBJECTS_DIR)/Ecran.o
#c++ -Wl,-R,/usr/local/qt/lib -o QtDossierReservation Main.cpp BorneReservation.o moc_BorneReservation.o   -L/usr/local/qt/lib -L/usr/openwin/lib -lqt -lXext -lX11 -lresolv -lsocket -lnsl -I/usr/local/qt/include Ecran.o

$(BIN_DIR)/Serveur:	Serveur.cpp $(OBJECTS_DIR)/Ecran.o $(OBJECTS_DIR)/Commons.o  $(OBJECTS_DIR)/IndexedElement.o
	$(COMPILER) -o $(BIN_DIR)/Serveur Serveur.cpp $(OBJECTS_DIR)/Ecran.o  $(OBJECTS_DIR)/Commons.o  $(OBJECTS_DIR)/IndexedElement.o

$(BIN_DIR)/Reservation:	Reservation.cpp $(OBJECTS_DIR)/Ecran.o $(OBJECTS_DIR)/Commons.o  $(OBJECTS_DIR)/IndexedElement.o
	$(COMPILER) -o $(BIN_DIR)/Reservation Reservation.cpp $(OBJECTS_DIR)/Ecran.o $(OBJECTS_DIR)/Commons.o  $(OBJECTS_DIR)/IndexedElement.o
#c++ -o Reservation Reservation.cpp Ecran.o

$(BIN_DIR)/Publicite:	Publicite.cpp $(OBJECTS_DIR)/Ecran.o
	$(COMPILER) -o $(BIN_DIR)/Publicite Publicite.cpp $(OBJECTS_DIR)/Ecran.o

$(BIN_DIR)/GestServ:	GestServ.cpp $(OBJECTS_DIR)/Ecran.o $(OBJECTS_DIR)/Commons.o  $(OBJECTS_DIR)/IndexedElement.o
	$(COMPILER) -o $(BIN_DIR)/GestServ GestServ.cpp $(OBJECTS_DIR)/Ecran.o  $(OBJECTS_DIR)/Commons.o  $(OBJECTS_DIR)/IndexedElement.o


$(OBJECTS_DIR)/Commons.o:	Commons.h Commons.cpp $(OBJECTS_DIR)/Ecran.o $(OBJECTS_DIR)/IndexedElement.o
	$(COMPILER) -c -o $(OBJECTS_DIR)/Commons.o Commons.cpp $(OBJECTS_DIR)/IndexedElement.o

$(OBJECTS_DIR)/Ecran.o: Ecran.h Ecran.cpp
	$(COMPILER) -c Ecran.cpp -o $(OBJECTS_DIR)/Ecran.o
# c++ -c Ecran.cpp -D SUN

$(OBJECTS_DIR)/BorneReservation.o: BorneReservation.h BorneReservation.cpp
	$(COMPILER) $(QT) -c -o $(OBJECTS_DIR)/BorneReservation.o BorneReservation.cpp
#c++ -Wall -W -O2  -DQT_NO_DEBUG -DQT_SHARED -I/usr/local/qt/mkspecs/default -I. -I. -I/usr/local/qt/include -c BorneReservation.cpp

$(OBJECTS_DIR)/moc_BorneReservation.o: moc_BorneReservation.cpp
	$(COMPILER) $(QT) -c -o $(OBJECTS_DIR)/moc_BorneReservation.o moc_BorneReservation.cpp
#c++ -Wall -W -O2  -DQT_NO_DEBUG -DQT_SHARED -I/usr/local/qt/mkspecs/default -I. -I. -I/usr/local/qt/include -c moc_BorneReservation.cppxxxxx

$(OBJECTS_DIR)/IndexedElement.o: DossierFichiersOctobre/IndexedElement.cpp DossierFichiersOctobre/IndexedElement.cpp
	$(COMPILER) -c DossierFichiersOctobre/IndexedElement.cpp -o $(OBJECTS_DIR)/IndexedElement.o

clean:	clean_kate_temp
	rm -f $(OBJECTS_DIR)/*
	rm -f $(BIN_DIR)/*

clean_kate_temp:
	rm -f ./*~
