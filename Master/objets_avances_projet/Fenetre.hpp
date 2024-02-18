#ifndef _FENETRE
#define _FENETRE

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tuile.hpp"
#include "Plateau.hpp"
#include "Domino.hpp"
#include "Trax.hpp"
#include "PlateauDomino.hpp"
#include "PlateauTrax.hpp"
using namespace sf;
using namespace std;

class Fenetre{
	protected:
		Plateau Board;
		Tuile Pick;
		RenderWindow Window;
	public:
		Fenetre();
		Fenetre(Plateau,Tuile);
		void setPick(Tuile);
		int putInPlateau(int,int,int);
		void dessinePlateau(RenderWindow &w);
		void dessineTuile(RenderWindow &w, Sprite);
		void ActionRight(Sprite *t);
		void ActionLeft(Sprite *t);
		void ActionDown(Sprite *t);
		void ActionUp(Sprite *t);
		void game();
};
#endif
