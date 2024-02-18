#ifndef _CARCASSONNE
#define _CARCASSONNE


#include <iostream>
#include <vector>
#include <cstdlib>
#include "Tuile.hpp"

using namespace std;

class Carcassonne: public Tuile {
	
	public:
		//Carcassonne
		char type;
		bool protection;
		int center; // sert a voir si il y a une liason entre 2 cote opposer
		//marquage pour completion
		vector <int> marquage;
		int marquageC;
		// position partisan sur la tuile 3*3
		//-1 =  pas de partisan
		int jPartisan;
		// -1 = center
		// 0-7 position
		int posPartisan;

		Carcassonne();
		Carcassonne(char t);
		void turnRight();
		void turnLeft();
		void turnTime2();
		bool check(Tuile &t, int direction);

};

#endif
