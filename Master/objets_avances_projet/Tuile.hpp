#ifndef _TUILE
#define _TUILE

#include <iostream>
#include <vector>
using namespace std;

class Tuile {
  private:
    vector <int> values;
    string Filename;
	public:
    bool isEmpty;
    int rotation;
    Tuile();
		Tuile(vector <int> v,string filename);
		void turnRight(int x);
		void turnLeft(int x);
		void turnTime2(int x);
		vector<int> getVal();
		void setVal(vector<int> val);
    string getFilename();
    void setFilename(string newF);
		bool check(Tuile& t, int direction, int n);

		string toString();
};
ostream & operator << (ostream &out, Tuile &x);

#endif
