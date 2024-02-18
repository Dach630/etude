#include "Carcassonne.hpp"

Carcassonne::Carcassonne() {
	isEmpty = true;
}
/*
0 = plaine
1 = chemin
2 = ville
3 = autre
*/
Carcassonne::Carcassonne(char t) {
	isEmpty = false;
	int jPartisan = -1;
	vector <int> marquage = { -1,-1,-1,-1, -1,-1,-1,-1 };
	int marquageC = -1;
	vector<int> val;
	switch (int(t)){
		case int('A') :
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(0);
			center = 3;
			protection = false;
			break;
		case int('B') :
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			center = 3;
			protection = false;
			break;
		case int('C') :
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			center = 2;
			protection = true;
			break;
		case int('D') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(1);
			center = 1;
			protection = false;
			break;
		case int('E') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			center = 0;
			protection = false;
			break;
		case int('F') :
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			center = 2;
			protection = true;
			break;
		case int('G') :
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			center = 2;
			protection = false;
			break;
		case int('H') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			center = 0;
			protection = false;
			break;
		case int('I') :
			val.push_back(4); // cas particulier ville separe
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			center = 0;
			protection = false;
			break;
		case int('J') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(0);
			center = 1;
			protection = false;
			break;
		case int('K') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			center = 1;
			protection = false;
			break;
		case int('L') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			center = 3;
			protection = false;
			break;
		case int('M') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			center = 0;
			protection = true;
			break;
		case int('N') :
			val.push_back(0);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			center = 0;
			protection = false;
			break;
		case int('O') :
			val.push_back(2);
			val.push_back(1);
			val.push_back(1);
			val.push_back(2);
			center = 0;
			protection = true;
			break;
		case int('P') :
			val.push_back(2);
			val.push_back(2);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(2);
			center = 1;
			protection = false;
			break;
		case int('Q') :
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			center = 2;
			protection = true;
			break;
		case int('R') :
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(2);
			center = 2;
			protection = false;
			break;
		case int('S') :
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(2);
			center = 2;
			protection = true;
			break;
		case int('T') :
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(2);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(2);
			center = 2;
			protection = false;
			break;
		case int('U') :
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(0);
			center = 1;
			protection = true;
			break;
		case int('V') :
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			center = 1;
			protection = false;
			break;
		case int('W') :
			val.push_back(0);
			val.push_back(0);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			center = 3;
			protection = false;
			break;
		case int('X') :
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			val.push_back(0);
			val.push_back(1);
			center = 3;
			protection = false;
			break;
		default:
			return;
	}
	setVal(val);
	type = t;
}

void Carcassonne::turnLeft() {
	Tuile::turnLeft(1);
}

void Carcassonne::turnRight() {
	Tuile::turnRight(1);
}

void Carcassonne::turnTime2() {
	Tuile::turnTime2(1);
}
/*
		|    |
		| t0 |
		|    |

|    |	|    |	|    |
| t3 |	|this|	| t1 |
|    |	|    |	|    |

		|    |
		| t2 |
		|    |

direction = 0 ou 1 ou 2 ou 3
*/
bool Carcassonne::check(Tuile& t, int direction){
	return t.getVal()[(direction * 2 + 5) % 9] == getVal()[direction * 2 + 1];
}