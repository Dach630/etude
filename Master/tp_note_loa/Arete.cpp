//
// Created by antoine on 16/10/22.
//

#include <iostream>
using namespace std;
#include "Arete.hpp"

Arete::Arete(Sommet start, Sommet dest) : start{start}, dest{dest} {} //<-- constructor here

const int Arete::getPoids() const {
    return this->poids;
}

void Arete::setPoids(int p) {
    this->poids = p;
}
