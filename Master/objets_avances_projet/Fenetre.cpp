#include "Fenetre.hpp"

Fenetre::Fenetre() : Board{}, Pick{},Window{VideoMode(800, 600), "Projet C++ 2022-2023",Style::Titlebar|Style::Close}{}

Fenetre :: Fenetre(Plateau p, Tuile t) : Board{p}, Pick{t}, Window{VideoMode(800, 600), "Projet C++ 2022-2023",Style::Titlebar|Style::Close}{}

int Fenetre:: putInPlateau(int x,int y,int z){
  if(x>=0 && y>=0 && x<Board.getTaille() && y<Board.getTaille() && Board.plateau[x][y].isEmpty){
    return Board.put(Pick,x,y,z);
  }
  return 1;
}

void Fenetre::dessinePlateau(RenderWindow &w) {
  for (int i=0; i< Board.getTaille(); i++){
    for (int j=0; j<Board.getTaille(); j++){
      Texture texture;
      texture.loadFromFile(Board.plateau[i][j].getFilename());
      Sprite tuile;  //sprite par défaut
      tuile.setTexture(texture); //définit l'image du sprite
      tuile.setOrigin(tuile.getLocalBounds().width/2,tuile.getLocalBounds().height/ 2); //son point d'origine (ici le centre du carré)
      int x = Board.plateau[i][j].rotation;
      if (x > 0){
        for (int y=0;y<x;y++){
          tuile.rotate(90.f);
        }
      }
      if(x < 0){
        for (int y=x;y<0;y++){
          tuile.rotate(-90.f);
        }
      }
      tuile.setScale(Vector2f(0.4,0.4)); //sa proportion par rapport à la taille de la vue
      tuile.setPosition((i+1)*(((Board.taille+1)*100)/Board.taille),(j+1)*(((Board.taille+1)*100)/Board.taille));
      w.draw(tuile);
    }
  }
}

// todo Tuile courante + tourner ou a ajouter fonction auxiliaire
void Fenetre::dessineTuile(RenderWindow &w, Sprite tuile2) {
    tuile2.move(Vector2f(100,100));
    w.draw(tuile2);
}

void Fenetre::ActionRight(Sprite *t){}

void Fenetre::ActionDown(Sprite *t){}

void Fenetre::ActionLeft(Sprite *t){}

void Fenetre::ActionUp(Sprite *t){}

void Fenetre :: setPick(Tuile t){
  Pick = t;
}
