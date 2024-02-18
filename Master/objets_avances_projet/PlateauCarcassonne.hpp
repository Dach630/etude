#ifndef _PLATEAUCARCASSONNE
#define _PLATEAUCARCASSONNE

#include "Carcassonne.hpp"
#include "Plateau.hpp"

class PlateauCarcassonne : public Plateau {

	public:
		//nb partisan par joueurs;
		vector<int> partisansJ;
		//partisan partisan sur plateau 15*15
		vector<vector<int>> partisansPlateau;

		vector<Carcassonne> sacC;
		vector<vector<Carcassonne>> plateauC;

		PlateauCarcassonne();
		PlateauCarcassonne(int nbJoueurs);
		void setBag();
		bool putCar(int x, int y, Carcassonne& d, int joueur);
		void game();
		int complete(int x, int y, int joueurs);
		vector<int> completeChemin(int x, int y);
		//le x et y de la piece placer et non celui du monastere
		void completeMonastere(int x, int y, int time);

		void setUpPlateau(int taille);
		Carcassonne takeInBag();

};

#endif