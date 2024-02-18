#include "FenetreDomino.hpp"

FenetreDomino::FenetreDomino() : Window{VideoMode(800, 600), "Projet C++ 2022-2023",Style::Titlebar|Style::Close} {
  PlateauDomino p {};
  Board = p;
  //setPick(Board.takeInBag());
  game();
}

int FenetreDomino:: putInPlateau(int x,int y,int z){
  if(x>=0 && y>=0 && x<Board.getTaille() && y<Board.getTaille() && Board.plateau[x][y].isEmpty){
    return Board.put(Pick,x,y,z);
  }
  return 1;
}

void FenetreDomino::ActionRight(){
  Pick.turnRight();
}

void FenetreDomino::ActionDown(){
  Pick.turnTime2();
}

void FenetreDomino::ActionLeft(){
  Pick.turnLeft();
}

void FenetreDomino::dessinePlateau(RenderWindow &w) {
  Text Text;
  for (int i=0; i< Board.getTaille(); i++){
    for (int j=0; j<Board.getTaille(); j++){
      if(!Board.plateau[i][j].isEmpty){
        vector <int> tile = Board.plateau[i][j].getVal();
        string s13 = "|";
        string s1 = " |"+to_string(tile[0]) + s13 + to_string(tile[1]) + s13 + to_string(tile[2]) +"| \n"+to_string(tile[11])+"| | | |"+to_string(tile[3])+"\n "+to_string(tile[10])+"| | | |"+to_string(tile[4])+"\n "+to_string(tile[9])+"| | | |"+to_string(tile[5])+"\n |"+to_string(tile[8])+s13+to_string(tile[7])+s13+to_string(tile[6])+"|\n ";
        Text.setString(s1);
        Text.move(i*10.f,j*10.f);
        w.draw(Text);
      }
    }
  }
}

void FenetreDomino::dessineTuile(RenderWindow &w, Domino &d) {
  Text Text;
  vector <int> tile = d.getVal();
  string s13 = "|";
  string s1 = " |"+to_string(tile[0]) + s13 + to_string(tile[1]) + s13 + to_string(tile[2]) +"| \n"+to_string(tile[11])+"| | | |"+to_string(tile[3])+"\n "+to_string(tile[10])+"| | | |"+to_string(tile[4])+"\n "+to_string(tile[9])+"| | | |"+to_string(tile[5])+"\n |"+to_string(tile[8])+s13+to_string(tile[7])+s13+to_string(tile[6])+"|\n ";
  Text.setString(s1);
  Text.move(100.f,100.f);
  w.draw(Text);
}

void FenetreDomino :: game(){
  View view1;
  View view2;
  int posxtuile=0;
  int nbTour=0;
  int posytuile=0;
    while (Window.isOpen()){
      Window.clear(); //remplissage en noir a l'exterieur pour eviter effacer
      dessinePlateau(Window);
      Event event;
      while (Window.pollEvent(event)){
        if (event.type == Event::Closed) {
          Window.close();
        }
        if (event.type == Event::KeyPressed){ // utilise pour tourner tuile
          if (event.key.code == Keyboard::Right){
            ActionRight();
          }
          if (event.key.code == Keyboard::Left) {
            ActionLeft();
          }
          if (event.key.code == Keyboard::Down) {
            ActionDown();
          }
        }
        cout<<"dans quelle ligne voulez-vous placer le domino ?"<<endl;
        cin>>posxtuile;
        cout<<"dans quelle colonne ?"<<endl;
        cin>>posytuile;
        int result = putInPlateau(posxtuile,posytuile,nbTour);
        if(result == 0){
          int vainqueur = Board.win(posxtuile,posytuile);
          if (vainqueur == 0 && Board.sac.size() >= 0){
            nbTour++;
            cout << "tour " << nbTour <<endl;
            Board.changeJoueur();
            int joueurannonce = Board.joueuractuel+1;
            cout << "au tour du joueur "<< joueurannonce << endl;
            //setPick(Board.takeInBag());
          }else if(vainqueur!=0){
            cout << "le joueur " << vainqueur << " a gagné"<<endl;
            exit(0);
          }else if(Board.sac.size() == 0){
            cout << "match nul" << endl;
          }
        }
      }
      view2.setViewport(sf::FloatRect(0.8f, 0, 0.8f, 1)); // cote droite 30%
      Window.setView(view2);
      dessineTuile(Window,Pick); // tuile a placé
      view1.setViewport(sf::FloatRect(0, 0, 0.8f, 1)); // cote gauche 70%
      Window.setView(view1);
      Window.display(); // affichage effectif
  }
}

void FenetreDomino :: setPick(Domino d){
  Pick = d;
}
