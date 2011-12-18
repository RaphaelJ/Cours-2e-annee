echo creation de BorneReservation.o
c++ -Wall -W -O2  -DQT_NO_DEBUG -DQT_SHARED -I/usr/local/qt/mkspecs/default -I. -I. -I/usr/local/qt/include -c BorneReservation.cpp

echo creation de moc_BorneReservation.o
c++ -Wall -W -O2  -DQT_NO_DEBUG -DQT_SHARED -I/usr/local/qt/mkspecs/default -I. -I. -I/usr/local/qt/include -c moc_BorneReservation.cpp

echo creation de Ecran.o -D SUN
c++ -c Ecran.cpp -D SUN

echo creation de QtDossierReservation
c++ -Wl,-R,/usr/local/qt/lib -o QtDossierReservation Main.cpp BorneReservation.o moc_BorneReservation.o   -L/usr/local/qt/lib -L/usr/openwin/lib -lqt -lXext -lX11 -lresolv -lsocket -lnsl -I/usr/local/qt/include Ecran.o

echo creation de Reservation
c++ -o Reservation Reservation.cpp Ecran.o

echo creation de Serveur
c++ -o Serveur Serveur.cpp Ecran.o

echo creation de QtDossierReservation
