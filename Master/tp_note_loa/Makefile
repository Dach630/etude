CPP= g++ --std=c++11 -Wall
CCO= $(CPP) -c
OBJECTS= Arete.o Sommet.o main.o

all :		executable

executable :	$(OBJECTS)
	$(CPP) -o graph $(OBJECTS)

Arete.o :	Arete.cpp Arete.hpp
	$(CCO) Arete.cpp

Sommet.o :	Sommet.cpp Sommet.hpp
	$(CCO) Sommet.cpp

main.o :	main.cpp
	$(CCO) main.cpp

clean :
	rm *.o
