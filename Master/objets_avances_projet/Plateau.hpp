#ifndef _PLATEAU
#define _PLATEAU

#include <ostream>
#include <vector>
#include "Tuile.hpp"
#include "Trax.hpp"
using namespace std;

class Plateau {
	private:

	public:
		Plateau();
		Plateau(int,int);
		vector<Tuile> sac;
		vector<vector<Tuile>> plateau;
		vector<int> joueurs;
		int joueuractuel;
		int nbJoueurs;
		int taille; // taille * taille = plateau entier
		void setUpJoueurs(int);
		void setUpPlateau(int);
		void pushInBag(Tuile *tuile);
		Tuile takeInBag();
		int put(Tuile &tuile, int,int,int);
		Tuile check(int,int);
		bool seek(int,int);
		void setTaille(int);
		int getTaille();
		int getNbJoueurs();
		void changeJoueur();
		int win(int,int);
		void addScore(int);
};

//ostream& operator << (ostream& out, Plateau& x);

#endif
