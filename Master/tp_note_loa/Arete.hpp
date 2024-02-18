//
// Created by antoine on 16/10/22.
//

#ifndef TP6_ARETE_HPP
#define TP6_ARETE_HPP

#include "Sommet.hpp"
#include <iostream>
using namespace std;

class Arete {
public:
    Arete(Sommet start, Sommet dest);
    Arete(Sommet start, Sommet dest, int poids);
    //TODO : increase count in GC
    const int getPoids() const;
    void setPoids(int p);
private:
    const Sommet start;
    const Sommet dest;
    int poids;
};


#endif //TP6_ARETE_HPP
