#include "Plateau.hpp"

void Plateau::setUpJoueurs(int nombres) {
	this -> nbJoueurs = nombres;
	for (int i = 0; i < nombres; i++) {
		joueurs.push_back(0);
	}
	joueuractuel = 0;
}

void Plateau::setUpPlateau(int taille) {
	this->taille = taille;
	for (int i = 0; i < taille; i++) {
		vector <Tuile> pl;
		for (int j = 0; j < taille; j++) {
			Tuile* t = new Tuile();
			pl.push_back(*t);
		}
		plateau.push_back(pl);
	}
}

Plateau::Plateau() {}

Plateau::Plateau(int n, int t) {
	setUpJoueurs(n);
	setUpPlateau(t);
}

void Plateau::pushInBag(Tuile* tuile) {
	sac.push_back(*tuile);
}

Tuile Plateau::takeInBag() {
	if (sac.size() == 0) {
		return Tuile();
	}
	Tuile r = sac[sac.size() - 1];
	sac.pop_back();
	return r;
}

int Plateau::put(Tuile &tuile, int x, int y, int z) {
	if(plateau[x][y].isEmpty){
		plateau[x][y] = tuile;
		plateau[x][y].isEmpty = false;
		return 0;
	}
	return 1;
}

Tuile Plateau::check(int x, int y) {
	return this->plateau[x][y];
}

bool Plateau :: seek(int x,int y){ //vérifie si une case est remplie
  return (!plateau[x][y].isEmpty);
}

void Plateau::addScore(int score) {
	joueurs[joueuractuel] += score;
}

int Plateau::getTaille() {
	return taille;
}

int Plateau::getNbJoueurs() {
	return nbJoueurs;
}

int Plateau::win(int x,int y){
	return 0;
}

void Plateau :: changeJoueur (){
	joueuractuel++;
	joueuractuel = joueuractuel % getNbJoueurs();
}
