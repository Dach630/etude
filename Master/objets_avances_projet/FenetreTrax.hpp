#ifndef _FENETRETRAX
#define _FENETRETRAX

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tuile.hpp"
#include "Plateau.hpp"
#include "Trax.hpp"
#include "PlateauTrax.hpp"
using namespace sf;
using namespace std;
class FenetreTrax {
	public:
		PlateauTrax Board;
		Trax Pick;
		RenderWindow Window;
    FenetreTrax();
		int putInPlateau(int,int,int);
		void ActionRight(Sprite *t);
		void ActionLeft(Sprite *t);
		void ActionDown(Sprite *t);
		void ActionUp(Sprite *t);
		void dessinePlateau(RenderWindow &w);
		void dessineTuile(RenderWindow &w, Sprite);
		void game();
		void setPick(Trax);
};
#endif
