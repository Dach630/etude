#ifndef _PLATEAUTRAX
#define _PLATEAUTRAX

#include <iostream>
//#include <SFML/Graphics.hpp>
#include <vector>
#include "Plateau.hpp"
#include "Trax.hpp"

using namespace std;
class PlateauTrax : public Plateau {
	public:
		vector <Trax> sac;
		PlateauTrax();
		void pushInBag(Trax tuile);
		Trax takeInBag();
	 	int put(Trax &,int,int,int);
		vector<int> checkLine(int);
		vector<int> checkColumn(int);
		int win(int,int);
		int winTrax(int,int,int,int,int,int,int,int);
};
#endif
