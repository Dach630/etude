#ifndef _DOMINO
#define _DOMINO

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Tuile.hpp"

using namespace std;
/*
[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]

	|   1 2 3  |
	|12       4|
	|11       5|
	|10       6|
	|   9 8 7  |
*/
class Domino :public Tuile{
	public:
		Domino();
		void turnRight();
		void turnLeft();
		void turnTime2();
		int scoreFace(int direction);
};

//ostream & operator << (ostream &out, Domino &x);

#endif
