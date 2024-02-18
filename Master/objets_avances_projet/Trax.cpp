#include "Trax.hpp"

Trax::Trax() : Tuile{{1,0,1,0},"./sprites/Trax_tile_X.png"} {} //on a la même valeur pour toutes les tuiles Trax

Trax::Trax(int i): Tuile{{},"./sprites/Blank-icon.png"} {} // celle-ci sert uniquement pour indiquer quand le sac de tuiles est vide

void Trax::turnRight() { // on pivote la pièce sur la droite
	Tuile::turnRight(1);
}

void Trax::turnLeft() { //la gauche
	Tuile::turnLeft(1);
}

void Trax::turnTime2() {
	Tuile::turnTime2(1);
}

void Trax :: flip() { // on change la face de la tuile
	if (getFilename() == "./sprites/Trax_tile_X.png" ){
		setVal({1,1,0,0});
		setFilename("./sprites/Trax_tile_U.png");
	}else{
		setVal({1,0,1,0});
		setFilename("./sprites/Trax_tile_X.png");
	}
	int x = rotation;
	if(rotation > 0 ){	// on fait tourner la pièce pour faire correspondre les deux côtés
		for(int i = 0; i <x ; i++){
			turnRight();
		}
		rotation -= x;	//on enlève le nombre de fois qu'on a fait tourner le verso de la pièce  
	}
	if(rotation < 0){
		for(int i = 0; i > x; i-- ){
				turnLeft();
		}
		rotation += x;
	}
}
