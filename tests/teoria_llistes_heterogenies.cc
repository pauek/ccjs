
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Punt { float x, y; };

//+figura
class Figura {
public:
  virtual bool a_dins(const Punt& p) const;
};

// bool Figura::a_dins(const Punt& p) const {
//   return false;
// }
//-figura

//+taula
const int MAX_FIGURES = 200;

struct TaulaFigures {
  Figura *fig[MAX_FIGURES];
  int numfig;
};
//-taula

//+rectangle
class Rectangle : public Figura {
  float dalt, baix, dreta, esquerra;
public:
  Rectangle(istream& i);
  bool a_dins(const Punt& p) const;
};

Rectangle::Rectangle(istream& i) {
  i >> esquerra >> baix >> dreta >> dalt;
}

bool Rectangle::a_dins(const Punt& p) const {
  return p.x > esquerra && p.x < dreta && p.y > baix && p.y < dalt;
}
//-rectangle

//+llegeix
void llegeix_figures(TaulaFigures& T) {
  ifstream Ff("figures.txt");
  string tipus;
  Ff >> tipus;
  while (!Ff.eof()) {
    Figura *nova;
    if (tipus == "rectangle") {
      // crear un rectangle i llegir-lo
      nova = new Rectangle(Ff);
    } 
    else {
      cout << "No conec la figura " << tipus << endl;
      std::exit(1); // marxa del programa
    }
    T.fig[T.numfig] = nova;
    T.numfig++;

    Ff >> tipus;
  }
}
//-llegeix

//+a_dins
bool punt_a_dins(const Punt& p, const TaulaFigures& T) {
  bool interior = false;
  int i = 0;
  while (i < T.numfig && !interior) {
    if (T.fig[i]->a_dins(p)) interior = true;
    else i++;
  }
  return interior;
}
//-a_dins

//+processa
void processa_punts(const TaulaFigures& T) {
  Punt p;
  ifstream Fp("punts.txt");
  Fp >> p.x >> p.y;
  while (!Fp.eof()) {
    if (punt_a_dins(p, T)) {
      cout << p.x << ' ' << p.y << endl;
    }
    Fp >> p.x >> p.y;
  }
}
//-processa

//+main
int main() {
  TaulaFigures F;
  F.numfig = 0;
  llegeix_figures(F);
  processa_punts(F);
}
//-main

// Local variables:
// compile-command: "gcc -o lh teoria_llistes_heterogenies.cc -lstdc++"
// End:
