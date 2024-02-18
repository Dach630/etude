#include "Tuile.hpp"

Tuile::Tuile(): Filename{"./sprites/Blank-icon.png"},isEmpty{true}, rotation{0} {}

Tuile::Tuile(vector <int> v,string file): values{v},Filename{file},isEmpty{true},rotation{0} {}

//x = taille d'un cote du carre
// deplace x derniere valeur au debut
void Tuile::turnRight(int x) {
	for (int i = 0; i < x; i++) {
		values.insert(values.begin(), values[(4*x)-1]);
		values.pop_back();
	}
	rotation++;
}

// deplace x premier valeur a la fin
void Tuile::turnLeft(int x) {
	for (int i = 0; i < x; i++) {
		values.push_back(values[0]);
		values.erase(values.begin());
	}
	rotation--;
}

void Tuile::turnTime2(int x) {
	turnRight(x);
	turnRight(x);
}

vector<int> Tuile::getVal() {
	return this->values;
}

void Tuile::setVal(vector <int> val) {
    if(val.size() > 0){
        isEmpty = false;
    }
	this->values = val;
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
n = taille d'un cote
*/

bool Tuile::check(Tuile& t, int direction, int n) {
	int thisTuile = direction * n;
	int tSide = (((direction - 2) % 4) * n) + (n - 1);
	vector<int> tmp = t.getVal();
	for (int i = 0; i < n; i++) {
		if (this->values[thisTuile] != tmp[tSide - i]) {
			return false;
		}
	}
	return true;
}

string Tuile:: toString(){
	string s= "{";
	for (vector <int> :: iterator i = values.begin() ;  i != values.end() ; ++i){
		s+= ' ' << *i;
	}
	s+="}";
	return s;
}

string Tuile :: getFilename(){
	return this -> Filename;
}

void Tuile :: setFilename(string newF){
	Filename = newF;
}

ostream& operator << (ostream& out, Tuile& x) {
	out << x.toString();
	return out;
}
