#include <iostream>
#include <SFML/Graphics.hpp>
#include "Domino.hpp"
#include "Trax.hpp"
#include "Fenetre.hpp"
#include "FenetreDomino.hpp"
#include "FenetreTrax.hpp"
#include "PlateauDomino.hpp"
#include "PlateauTrax.hpp"
using namespace sf;
using namespace std;

void gameChoice() {
    int choix = 0;
    while (true) {
        cout << "Choisisez le jeu:\n"
            << "\t1.Dominos\n"
            << "\t2.Trax\n"
            << "\t3.Carcassonne\n"
            << "\t0.Quitter\n";
        cin >> choix;
        switch (choix) {
        case 1:
          {
            FenetreDomino d {};
            break;
          }
        case 2:
          {
            FenetreTrax t {};
            break;
          }
        case 3:
          {
            //FenetreCarcassonne * c -> new FenetreCarcassonne();
            break;
          }
        case 0:
          {
            cout << "Aurevoir." << endl;
            break;
          }
        default:
            cout << "je n'ai pas compris.\n";
            break;
        }
        if (choix == 0) {
            break;
        }
    }
}

/*
void testDomTurn() {
    Domino* testD = new Domino();
    cout << "\ntest\n";
    for (int x : testD->getVal()) {
        cout << x << "\n";
    }
    cout << "\ntest\n";
    testD->turnRight();
    for (int x : testD->getVal()) {
        cout << x << "\n";
    }
    cout << "\ntest\n";
    testD->turnLeft();
    for (int x : testD->getVal()) {
        cout << x << "\n";
    }
    cout << "\ntest\n";
    testD->turnTime2();
    for (int x : testD->getVal()) {
        cout << x << "\n";
    }
}

void testTraxTurn() {
  Trax * testT = new Trax();
  cout << "\ntest\n";
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
  cout << "\ntest\n";
  testT->turnRight();
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
  cout << "\ntest\n";
  testT->turnLeft();
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
  cout << "\ntest\n";
  testT->turnTime2();
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
  cout << "\ntest" <<endl;
  testT->flip();
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
  cout << "\ntest\n";
  testT->turnRight();
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
  cout << "\ntest\n";
  testT->turnLeft();
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
  cout << "\ntest\n";
  testT->turnTime2();
  for (int x : testT->getVal()) {
      cout << x << "\n";
  }
}
*/

int main(){
    gameChoice();
    //new FenetreTrax();
    //testDomTurn();
    //testTraxTurn();
    return EXIT_SUCCESS;
}
