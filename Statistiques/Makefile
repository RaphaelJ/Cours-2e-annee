OBJ=Race.o Races.o EchPositionDepart.o EchPositionArrivee.o EchNombreSpectateurs.o EchPositionDepartArrivee.o ParamStat1d.o ParamStat2d.o
CC=g++ -DLIN -ggdb

all: Statistiques

Statistiques:	$(OBJ) Main.cpp Exception.h
	$(CC) -o Statistiques Main.cpp $(OBJ)

Race.o:	Race.cpp Race.h
	$(CC) -c Race.cpp

Races.o:	Races.cpp Races.h Race.o Exception.h
	$(CC) -c Races.cpp

EchPositionDepart.o:	EchPositionDepart.cpp EchPositionDepart.h DataSourceX.h\
	DataSource.h DataX.h
	$(CC) -c EchPositionDepart.cpp

EchPositionArrivee.o:	EchPositionArrivee.cpp EchPositionArrivee.h DataSourceX.h\
	DataSource.h DataX.h
	$(CC) -c EchPositionArrivee.cpp

EchNombreSpectateurs.o:	EchNombreSpectateurs.cpp EchNombreSpectateurs.h DataSourceX.h\
	DataSource.h DataX.h
	$(CC) -c EchNombreSpectateurs.cpp

EchPositionDepartArrivee.o:	EchPositionDepartArrivee.cpp EchPositionDepartArrivee.h\
	DataSourceXY.h	DataSource.h DataXY.h
	$(CC) -c EchPositionDepartArrivee.cpp

ParamStat1d.o:	ParamStat1d.cpp ParamStat1d.h DataSourceX.h DataSource.h DataX.h
	$(CC) -c ParamStat1d.cpp

ParamStat2d.o:	ParamStat2d.cpp ParamStat2d.h DataSourceXY.h DataSource.h DataXY.h
	$(CC) -c ParamStat2d.cpp

clean:
	rm ./*.o
	rm ./*~