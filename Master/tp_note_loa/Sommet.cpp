//
// Created by antoine on 16/10/22.
//

#include <iostream>

using namespace std;

#include "Sommet.hpp"

Sommet::Sommet(string label) : label{label} {} //<-- constructor here
//TODO : unicité des sommets

const string Sommet::getLabel() const {
    return this->label;
}

void Sommet::setMarquage(int x) {
    this->marquage = x;
}