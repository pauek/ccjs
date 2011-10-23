
#include <iostream>
using namespace std;

class Element {
  int _num;
  Element *_anterior;
public:
  Element(int n);
  int num() const;
  Element *anterior() const;
  void enllasa(Element *p);
};

Element::Element(int n) {
  _num = n;
  _anterior = 0;
}

void Element::num() const {
  return _num;
}

Element *Element::anterior() const {
  return _anterior;
}

void Element::enllasa(Element *p) {
  _anterior = p;
}

int main() {
  Element *actual = 0;
  int n;

  // Llegim la seqüència
  cin >> n;
  while (n != -1) {
    Element *nou = new Element(n);
    nou->enllasa(actual);
    actual = nou;
    cin >> n;
  }

  // Mostrem la seqüència
  while (actual != 0) {
    cout << actual->num() << ' ';
    actual = actual->anterior();
  }
  cout << endl;
}
