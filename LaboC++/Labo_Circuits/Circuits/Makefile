COMPILER=g++ -ggdb -foptimize-sibling-calls
LINKER=ld

OBJ=Person.o Race.o Date.o Circuit.o StringProperty.o Competitor.o\
    FederationAdmin.o TeamMember.o ExceptionBase.o FichierLog.o
OUTPUT=Circuits.o

all: Circuits.o

.o:	.cpp
	$(COMPILER) -c $*.cpp

$(OUTPUT):	$(OBJ)
	$(LINKER) -r $(OBJ) -o $(OUTPUT)

StringProperty.o:	StringProperty.cpp StringProperty.h
ExceptionBase.o:	ExceptionBase.cpp ExceptionBase.h

Race.o:	Race.cpp Race.h

Date.o:	Date.cpp Date.h

Circuit.o:	Circuit.cpp Circuit.h

Person.o:	Person.cpp Person.h
Competitor.o:	Competitor.cpp Competitor.h Person.h
FederationAdmin.o:	FederationAdmin.cpp FederationAdmin.h Person.h
TeamMember.o:	TeamMember.cpp TeamMember.h Person.h

FichierLog.o:	FichierLog.cpp FichierLog.h

clean:	clean_kate_temp
	rm -f $(OBJ)
	rm -f $(OUTPUT)

clean_kate_temp:
	rm -f ./*~
