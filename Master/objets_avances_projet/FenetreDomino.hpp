#ifndef _FENETREDOMINO
#define _FENETREDOMINO

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tuile.hpp"
#include "Plateau.hpp"
#include "Domino.hpp"
#include "PlateauDomino.hpp"
using namespace sf;
using namespace std;
class FenetreDomino {
	public:
		PlateauDomino Board;
		Domino Pick;
		RenderWindow Window;
    FenetreDomino();
		int putInPlateau(int,int,int);
		void ActionRight();
		void ActionLeft();
		void ActionDown();
		void dessinePlateau(RenderWindow &w);
		void dessineTuile(RenderWindow &w,Domino &d);
		void game();
		void setPick(Domino);
};
#endif
