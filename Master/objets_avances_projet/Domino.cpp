#include "Domino.hpp"

Domino::Domino() {
	vector<int> val;
	for (int i = 0; i < 12; i++) {
		val.push_back(rand() % 5);
	}
	setVal(val);;
}

void Domino::turnRight() {
	Tuile::turnRight(3);
}

void Domino::turnLeft() {
	Tuile::turnLeft(3);
}

void Domino::turnTime2() {
	Tuile::turnTime2(3);
}

/*
|  0  |
|3   1|
|  2  |
apres un check
*/
int Domino::scoreFace(int direction) {
	if (direction < 0 || direction > 3) {
		return 0;
	}
	vector<int> val = this->getVal();
	int decalage = direction * 3;
	int res = 0 ;
	for (int i = 0; i < 3; i++) {
		res += val[i + decalage];
	}
	return res;
}
