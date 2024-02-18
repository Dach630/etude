CPP=g++ --std=c++11 -Wall

all : Tuile.o Trax.o Domino.o Plateau.o PlateauTrax.o PlateauDomino.o Fenetre.o FenetreTrax.o FenetreDomino.o main clean 

main : main.o
	$(CPP) -o main Tuile.o Domino.o Trax.o Plateau.o PlateauDomino.o PlateauTrax.o Fenetre.o FenetreDomino.o FenetreTrax.o main.o -lsfml-graphics -lsfml-window -lsfml-system

main.o : main.cpp
	$(CPP) -c main.cpp

Fenetre.o : Fenetre.cpp
	$(CPP) -c Fenetre.cpp

FenetreTrax.o : FenetreTrax.cpp
	$(CPP) -c FenetreTrax.cpp

FenetreDomino.o : FenetreDomino.cpp
	$(CPP) -c FenetreDomino.cpp

Tuile.o : Tuile.cpp
	$(CPP) -c Tuile.cpp

Trax.o : Trax.cpp
	$(CPP) -c Trax.cpp

Domino.o : Domino.cpp
	$(CPP) -c Domino.cpp

Plateau.o : Plateau.cpp
	$(CPP) -c Plateau.cpp

PlateauTrax.o : PlateauTrax.cpp
	$(CPP) -c PlateauTrax.cpp

PlateauDomino.o : PlateauDomino.cpp
	$(CPP) -c PlateauDomino.cpp

clean :
	rm *.o
