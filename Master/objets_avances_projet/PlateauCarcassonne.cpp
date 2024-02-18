#include "PlateauCarcassonne.hpp"

PlateauCarcassonne::PlateauCarcassonne() {

}

PlateauCarcassonne::PlateauCarcassonne(int joueurs) {
	setUpJoueurs(joueurs);
	for (int i = 0; i < joueurs; i++) {
		partisansJ.push_back(8);
	}
	setBag();
	setUpPlateau(15);
	
	// placer la case de depart au centre
}
void PlateauCarcassonne::setBag() {
	Carcassonne* d;
	for (int i = 0; i < 2; i++) {
		d = new Carcassonne('A');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 4; i++) {
		d = new Carcassonne('B');
		sacC.push_back(*d);
	}

	d = new Carcassonne('C');
	sacC.push_back(*d);

	for (int i = 0; i < 4; i++) {
		d = new Carcassonne('D');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 5; i++) {
		d = new Carcassonne('E');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 2; i++) {
		d = new Carcassonne('F');
		sacC.push_back(*d);
	}

	d = new Carcassonne('G');
	sacC.push_back(*d);

	for (int i = 0; i < 3; i++) {
		d = new Carcassonne('H');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 2; i++) {
		d = new Carcassonne('I');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 3; i++) {
		d = new Carcassonne('J');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 3; i++) {
		 d = new Carcassonne('K');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 3; i++) {
		d = new Carcassonne('L');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 2; i++) {
		d = new Carcassonne('M');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 3; i++) {
		d = new Carcassonne('N');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 2; i++) {
		d = new Carcassonne('O');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 3; i++) {
		d = new Carcassonne('P');
		sacC.push_back(*d);
	}

	d = new Carcassonne('Q');
	sacC.push_back(*d);

	for (int i = 0; i < 3; i++) {
		d = new Carcassonne('R');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 2; i++) {
		d = new Carcassonne('S');
		sacC.push_back(*d);
	}

	d = new Carcassonne('T');
	sacC.push_back(*d);

	for (int i = 0; i < 8; i++) {
		d = new Carcassonne('U');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 9; i++) {
		d = new Carcassonne('V');
		sacC.push_back(*d);
	}
	for (int i = 0; i < 4; i++) {
		d = new Carcassonne('W');
		sacC.push_back(*d);
	}

	d = new Carcassonne('X');
	sacC.push_back(*d);
}

bool PlateauCarcassonne::putCar(int x, int y, Carcassonne& c, int joueur) {
	int taille = getTaille();
	if (x < 0 || y < 0 || x >= taille || y >= taille) {
		return false;
	}
	if (x > 0) {
		Carcassonne t = plateauC[x - 1][y];
		if (!t.isEmpty) {
			if (!c.check(t, 0)) {
				return false;
			}
		}
	}
	if (y > 0) {
		Carcassonne t = plateauC[x][y - 1];
		if (!t.isEmpty) {
			if (!c.check(t, 3)) {
				return false;
			}
		}
	}
	if (x + 1 < taille) {
		Carcassonne t = plateauC[x + 1][y];
		if (!t.isEmpty) {
			if (!c.check(t, 2)) {
				return false;
			}
		}
	}
	if (y + 1 < taille) {
		Carcassonne t = plateauC[x][y + 1];
		if (!t.isEmpty) {
			if (!c.check(t, 1)) {
				return false;
			}
		}
	}
	plateauC[x][y] = c;
	complete(x, y, joueur);
	return true;
}

int PlateauCarcassonne::complete(int x, int y, int joueurs) {
	Carcassonne t = plateauC[x][y];
	int tmpc = t.center;
	if (tmpc == 3) {

	}
	if (tmpc == 1) {

	}
	return 0;
}
// 
vector<int> PlateauCarcassonne::completeChemin(int x, int y){
	vector<int> j = {};
	int taille = getTaille();
	if (x < 0 || y < 0 || x >= taille || y >= taille) {
		j.push_back(-1);
	}
	int tmpX = x;
	int tmpY = y;
	Carcassonne t = plateauC[x][y];
	if (t.center == 3) {
		t = plateauC[tmpX][tmpY];
		while (true) {
			if (x < 0 || y < 0 || x >= taille || y >= taille) {
				j.push_back(-1);
			}
		}
	}
	else if (t.center == 1) {
		
	}
	return j;
}
// 
void PlateauCarcassonne::completeMonastere(int x, int y, int time = 0){
	vector<int> res = {};
	if (x < 0 || y < 0 || x >= taille || y >= taille) {
		return;
	}
	int full = 0;
	if (plateauC[x][y].type == 'A' || plateauC[x][y].type == 'B') {
		if (!plateauC[x - 1][y - 1].isEmpty &&
			!plateauC[x - 1][y].isEmpty &&
			!plateauC[x - 1][y + 1].isEmpty &&
			!plateauC[x][y - 1].isEmpty &&
			!plateauC[x][y + 1].isEmpty &&
			!plateauC[x + 1][y - 1].isEmpty &&
			!plateauC[x + 1][y].isEmpty &&
			!plateauC[x + 1][y + 1].isEmpty) {
			if (plateauC[x][y].jPartisan > 0 && plateauC[x][y].posPartisan == -1) {
				joueurs[plateauC[x][y].jPartisan] += 8;
			}
		}
	}
	if (time == 1) {
		return;
	}
	completeMonastere(x-1, y-1, time + 1);
	completeMonastere(x-1, y, time + 1);
	completeMonastere(x-1, y+1, time + 1);
	completeMonastere(x, y-1, time + 1);
	completeMonastere(x, y+1, time + 1);
	completeMonastere(x+1, y-1, time + 1);
	completeMonastere(x+1, y, time + 1);
	completeMonastere(x+1, y+1, time + 1);
}

void PlateauCarcassonne::setUpPlateau(int taille) {
	this->taille = taille;
	for (int i = 0; i < taille; i++) {
		vector <Carcassonne> pl;
		for (int j = 0; j < taille; j++) {
			Carcassonne* t = new Carcassonne();
			pl.push_back(*t);
		}
		plateauC.push_back(pl);
	}
}

Carcassonne PlateauCarcassonne::takeInBag() {
	int tmp = rand() % sacC.size();
	Carcassonne c = sacC[tmp];
	sacC.erase(sacC.begin() + tmp);
	return c;
}

