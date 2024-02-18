#ifndef _TRAX
#define _TRAX

#include <iostream>
#include <vector>
#include "Tuile.hpp"
using namespace std;
/*
[1, 0, 1,0]

	|   1   |
	|0     0|
	|   1   |
*/
class Trax :public Tuile{
	public:
		string filename;
		Trax();
		Trax(int);
		void turnRight();
		void turnLeft();
		void turnTime2();
		void flip();
};
#endif
