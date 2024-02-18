#ifndef _PLATEAUDOMINO
#define _PLATEAUDOMINO

#include "Domino.hpp"
#include "Plateau.hpp"
#include <cmath>
class PlateauDomino : public Plateau{
	private:

	public:
		PlateauDomino();
		PlateauDomino(int);
		int takeline();
		int takecolumn();
		bool putDom(int,int,int,Domino& d);
	//	void game();
};

//ostream& operator << (ostream& out, PlateauDomino& x);

#endif
