#include "PlateauDomino.hpp"

PlateauDomino::PlateauDomino() {
	PlateauDomino(2);
}

PlateauDomino::PlateauDomino(int nbJoueurs) {
	setUpJoueurs(nbJoueurs);
	nbJoueurs *= 13;
	for (int i = 0; i < nbJoueurs; i++) {
		Domino* d = new Domino();
		pushInBag(d);
	}
	double x = sqrt(nbJoueurs);
	int l = x + 1 ;
	taille = l;
	setUpPlateau(l);
}
/*
|--> y
|
v
x
*/

bool PlateauDomino::putDom(int x, int y,int nbTour, Domino& d) {
	int taille = getTaille();
	if (x < 0 || y < 0 || x >= taille || y >= taille) {
		return false;
	}
	int score = 0;
	if (x - 1 >= 0) {
		Tuile t = check(x - 1, y);
		if (!t.isEmpty) {
			if (d.check(t, 0, 3)) {
				score += d.scoreFace(0);
			}
			else {
				return false;
			}
		}
	}
	if (y - 1 >= 0) {
		Tuile t = check(x, y - 1);
		if (!t.isEmpty) {
			if (d.check(t, 3, 3)) {
				score += d.scoreFace(3);
			}
			else {
				return false;
			}
		}
	}
	if (x + 1 < taille) {
		Tuile t = check(x + 1, y);
		if (!t.isEmpty) {
			if (d.check(t, 2, 3)) {
				score += d.scoreFace(2);
			}
			else {
				return false;
			}
		}
	}
	if (y + 1 < taille) {
		Tuile t = check(x, y + 1);
		if (!t.isEmpty) {
			if (d.check(t, 1, 3)) {
				score += d.scoreFace(1);
			}
			else {
				return false;
			}
		}
	}
	addScore(score);
	put(d, x, y,nbTour);
	changeJoueur();
	return true;
}

int takeline(){
	int posX = 0;
	int taille = getTaille();
		cout << "sur quelle ligne poser la tuile ?"<<endl;
	cin >> posX;
	if (posX< 0 || posX > taille){
		cout << "ligne invalide" << endl;
		return takeline()
	}
	return posX;
}

int takecolumn(){
	int posY = 0;
	int taille = getTaille();
		cout << "sur quelle colonne ?"<<endl;
	cin >> posY;
	if (posY< 0 || posY > taille){
		cout << "colonne invalide" << endl;
		return takecolumn()
	}
	return posY;
}

/*
void PlateauDomino::game() {
	int turn = 0;
	int taille = getTaille();
	int nbTour = 0;
	int nbjoueurs = getNbJoueurs();
	while (sac.size() > 0) {
		Tuile actual = takeInBag();
		while (true) {
			int x = takeline();
			int y = takecolumn();
			putDom(x,y,nbTour,actual);
			//discard;
			break;
			// if (put ) {break;}

		}

		turn = (turn + 1) % nbJoueurs;
	}
}*/
