//
// Created by antoine on 16/10/22.
//

#ifndef TP6_SOMMET_HPP
#define TP6_SOMMET_HPP

#include <iostream>
using namespace std;

class Sommet {
public:
    Sommet(string label);
    Sommet(Sommet &s);
    //TODO : increase count in GC
    void setMarquage(int x);
    const string getLabel() const;
private:
    string label;
    int marquage;
};


#endif //TP6_SOMMET_HPP
