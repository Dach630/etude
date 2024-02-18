#include "FenetreTrax.hpp"

FenetreTrax::FenetreTrax() : Window{VideoMode(800, 600), "Projet C++ 2022-2023",Style::Titlebar|Style::Close} {
  PlateauTrax p {};
  Board = p;
  setPick(Board.takeInBag());
  game();
}

int FenetreTrax:: putInPlateau(int x,int y,int z){
  if(x>=0 && y>=0 && x<Board.getTaille() && y<Board.getTaille() && Board.plateau[x][y].isEmpty){
    return Board.put(Pick,x,y,z);
  }
  return 1;
}

void FenetreTrax::ActionRight(Sprite *t){
  Pick.turnRight();
  t->rotate(90.f);
}

void FenetreTrax::ActionDown(Sprite *t){
  Pick.turnTime2();
  t->rotate(180.f);
}

void FenetreTrax::ActionLeft(Sprite *t){
  Pick.turnLeft();
  t->rotate(-90.f);
}

void FenetreTrax :: ActionUp(Sprite *t){
  Pick.flip();
  vector <int> ch = Pick.getVal();
}

void FenetreTrax::dessinePlateau(RenderWindow &w) {
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

void FenetreTrax::dessineTuile(RenderWindow &w, Sprite tuile2) {
    tuile2.move(Vector2f(100,100));
    w.draw(tuile2);
}

void FenetreTrax :: game(){
  View view1;
  View view2;
  Sprite tuile;  //sprite par défaut
  int posxtuile=0;
  int nbTour = 0;
  int posytuile=0;
    while (Window.isOpen()){
      Window.clear(); //remplissage en noir a l'exterieur pour eviter effacer
      dessinePlateau(Window);
      Event event;
      Texture texture;
      texture.loadFromFile(Pick.getFilename());
      tuile.setOrigin(tuile.getLocalBounds().width/2,tuile.getLocalBounds().height/ 2); //son point d'origine (ici le centre du carré)
      tuile.setScale(Vector2f(0.4,0.4));
      tuile.setTexture(texture);
      while (Window.pollEvent(event)){
        if (event.type == Event::Closed) {
          Window.close();
        }
        if (event.type == Event::KeyPressed){ // utilise pour tourner tuile
          if (event.key.code == Keyboard::Right){
            ActionRight(&tuile);
          }
          if (event.key.code == Keyboard::Left) {
            ActionLeft(&tuile);
          }
          if (event.key.code == Keyboard::Down) {
            ActionDown(&tuile);
          }
          if (event.key.code == Keyboard::Up) {
            ActionUp(&tuile);
          }
        }
        if (event.type == Event::MouseButtonPressed) {
          int taille = Board.getTaille(); // taille du plateau a remplacer
          Vector2f vectmp = view1.getSize();// taille de la view
              //decoupe
          vectmp.x /= taille;
          vectmp.y /= taille;
              // position relative au niveau de a view
          Vector2i pixelPos = sf::Mouse::getPosition(Window);
          Vector2f worldPos = Window.mapPixelToCoords(pixelPos);
            // position dans plateau (attention si click sur la partie gauche donne des val plus grande que taille)
          posxtuile = worldPos.x / vectmp.x;
          posytuile = worldPos.y / vectmp.y;
              //position pour placer image sur view.
          vectmp.x = posxtuile * vectmp.x;
          vectmp.y = posytuile * vectmp.y;
          int result = putInPlateau(posxtuile,posytuile,nbTour);
          if(result == 0){
            tuile.setRotation(0.f);
            int vainqueur = Board.win(posxtuile,posytuile);
            if (vainqueur == 0 && Board.sac.size() >= 0){
              nbTour++;
              cout << "tour " << nbTour <<endl;
              Board.changeJoueur();
              int joueurannonce = Board.joueuractuel+1;
              cout << "au tour du joueur "<< joueurannonce << endl;
              setPick(Board.takeInBag());
            } else if(vainqueur!=0){
                cout << "le joueur " << vainqueur << " a gagné"<<endl;
                exit(0);
            } else if(Board.sac.size() == 0){
                cout << "match nul" << endl;
            }
          }
        }
      }
      view2.setViewport(sf::FloatRect(0.8f, 0, 0.8f, 1)); // cote droite 30%
      Window.setView(view2);
      dessineTuile(Window,tuile); // tuile a placé
      view1.setViewport(sf::FloatRect(0, 0, 0.8f, 1)); // cote gauche 70%
      Window.setView(view1);
      Window.display(); // affichage effectif
  }
}

void FenetreTrax :: setPick(Trax t){
  Pick = t;
}
