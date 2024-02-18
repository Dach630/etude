#include "PlateauTrax.hpp"

PlateauTrax :: PlateauTrax () : Plateau{2,8} { //tous les jeux de Trax ont 2 joueurs et 8*8 cases
  Trax x{0};
  pushInBag(x); //une tuile blanche qui sera piochée si le sac n'a plus de tuiles de jeu
  Trax t {};
  for (int i =0; i< 64; i++){ //On ajoute 64 fois dans le sac la même tuile
    pushInBag(t);
  }
}

void PlateauTrax::pushInBag(Trax tuile) { //ajoute des tuiles dans le sac
	sac.push_back(tuile);
}

Trax PlateauTrax::takeInBag() { // prend une tuile dans le sac
	if (sac.size() == 0) {
		return Trax(0);
	}
	Trax r = sac[sac.size() - 1];
	sac.pop_back();
	return r;
}

vector<int> PlateauTrax :: checkLine(int x){  //donne les positions à gauche et à droite de x
  vector<int>pos;
  int posX1=0;
  int posX2=0;
  if (x==0){
    posX1=7;
    posX2=1;
  }else if(x==7){
    posX1=6;
    posX2=0;
  }else{
    posX1=x-1;
    posX2=x+1;
  }
  pos.push_back(posX1);
  pos.push_back(posX2);
  return pos;
}

vector<int> PlateauTrax :: checkColumn(int y){   //donne les positions en haut et en bas de y
  vector<int>pos;
  int posY1=0;
  int posY2=0;
  if(y==0){
    posY1=7;
    posY2=1;
  }else if(y==7){
    posY1=6;
    posY2=0;
  }else{
    posY1=y-1;
    posY2=y+1;
  }
  pos.push_back(posY1);
  pos.push_back(posY2);
  return pos;
}

int PlateauTrax :: put(Trax &t,int x,int y, int nbTour){ //met une tuile dans le plateau
  if(nbTour == 0){  // si on est au premier tour, on peut poser la tuile sur n'importe quelle case.
    Plateau :: put(t,x,y,nbTour);
    return 0;
  }
  vector<int> line = checkLine(x);
  vector<int> column = checkColumn(y);
  bool canPlace=true;
  vector<int> neighbor;
  vector<int> vals = t.getVal();
  if(seek(line[0],y) || seek(line[1],y) || seek(x,column[0]) || seek(x,column[1])){ //sinon, on vérifie si il existe une tuile adjacente
    if(seek(line[0],y)){   //si il existe une tuile à gauche, vérifie que la courante est compatible
      neighbor = check(line[0],y).getVal();
      if(neighbor[1] != vals[3]){
        canPlace =false;
        cout << "La tuile de gauche ne correspond pas " <<endl;
      }
    }
    if(seek(line[1],y)){  //même chose à droite
      neighbor = check(line[1],y).getVal();
      if(neighbor[3] != vals[1]){
        canPlace =false;
        cout << "La tuile de droite ne correspond pas " <<endl;
      }
    }
    if(seek(x,column[0])){  //en haut
      neighbor = check(x,column[0]).getVal();
      if(neighbor[2] != vals[0]){
        canPlace =false;
        cout << "La tuile du haut ne correspond pas " <<endl;
      }
    }
    if(seek(x,column[1])){  //et en bas
      neighbor = check(x,column[1]).getVal();
      if(neighbor[0] != vals[2]){
        canPlace =false;
        cout << "La tuile du bas ne correspond pas " <<endl;
      }
    }
    if(canPlace){ //si toutes les tuiles sont compatibles, on peut placer notre tuile
      Plateau :: put(t,x,y,nbTour);
      return 0;
    }
  }else{
    cout << "ne peut pas placer la tuile ici, elle n'a pas de voisin" << endl;
  }
  return 1;
}

int PlateauTrax :: win(int x,int y){ // vérifie si l'un des deux joueurs à gagner (si les deux gagnent en même temps on donnera la victoire au joueur 1)
  vector<vector<int>> positionsprec;
  int resultat = (winTrax(0,x,y,0,0,x,y,0));
  if(resultat != 0){
    return resultat;
  }
  resultat = (winTrax(0,x,y,0,0,x,y,1));
  if(resultat != 0){
    return resultat;
  }
  return 0;
}

int PlateauTrax :: winTrax(int nbverifs,int posinitialX, int posinitialY,int posprecedenteX,int posprecedenteY,int x,int y,int joueur){ // vérifie si on a une boucle
  vector <int> line = checkLine(x);
  vector <int> column = checkColumn(y);
  int bas = 2;
  int gauche = 2;
  int haut = 2;
  int droite = 2;
  if (seek(x,column[0])){
    vector <int> h = plateau[x][column[0]].getVal();
    haut = h[2];
  }
  if(seek(x,column[1])){
    vector <int> b = plateau[x][column[1]].getVal();
    bas = b[0];
  }
  if(seek(line[0],y)){
    vector <int> g = plateau[line[0]][y].getVal();
    gauche = g[1];
  }
  if(seek(line[1],y)){
    vector <int> d = plateau[line[1]][y].getVal();
    droite = d[3];
  }
  if(nbverifs > 0){
    if(posinitialX == x && posinitialY == y) {
      return joueur+1;
    }
  }
  vector <int> v = plateau[x][y].getVal();
  if(v[0] == joueur && joueur == haut){
    if(nbverifs >0){
      if (posprecedenteX!=x || posprecedenteY!=column[0]){
        nbverifs+=1;
        return winTrax(nbverifs,posinitialX,posinitialY,x,y,x,column[0],joueur);
      }
    }else{
      nbverifs+=1;
      return winTrax(nbverifs,posinitialX,posinitialY,x,y,x,column[0],joueur);
    }
  }
  if(v[1] == joueur && joueur == droite) {
    if (nbverifs>0){
      if(posprecedenteX!=line[1] || posprecedenteY!=y){
        nbverifs+=1;
        return winTrax(nbverifs,posinitialX,posinitialY,x,y,line[1],y,joueur);
      }
    }else{
      nbverifs+=1;
      return winTrax(nbverifs,posinitialX,posinitialY,x,y,line[1],y,joueur);
    }
  }
  if(v[2] == joueur && joueur == bas){
    if (nbverifs>0){
      if(posprecedenteX!=x || posprecedenteY!=column[1]){
        nbverifs+=1;
        return winTrax(nbverifs,posinitialX,posinitialY,x,y,x,column[1],joueur);
      }
    }else{
      nbverifs+=1;
      return winTrax(nbverifs,posinitialX,posinitialY,x,y,x,column[1],joueur);
    }
  }
  if(v[3] == joueur && joueur == gauche){
    if (nbverifs>0){
      if(posprecedenteX!=line[0] || posprecedenteY!=y){
        nbverifs+=1;
        return winTrax(nbverifs,posinitialX,posinitialY,x,y,line[0],y,joueur);
      }
    }else{
      nbverifs+=1;
      return winTrax(nbverifs,posinitialX,posinitialY,x,y,line[0],y,joueur);
    }
  }
  return 0;
}
