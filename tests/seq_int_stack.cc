
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

class Contenidor {
  Element *_ultim;
public:
  Contenidor();
  bool es_buit() const;
  int  ultim() const;
  void posa(int num);
  void treu(); // esborra l'últim
};

Contenidor::Contenidor() {
  _ultim = 0;
}

bool Contenidor::es_buit() {
  return _ultim == 0;
}

int Contenidor::ultim() const {
  return _ultim->num();
}

Contenidor::posa(int num) {
  Element *nou = new Element(num);
  nou->enllasa(_ultim);
  _ultim = nou;
}

void Contenidor::treu() {
  Element *anterior = _ultim->anterior();
  delete _ultim;
  _ultim = anterior;
}

int main() {
  Contenidor C;
  int n;
  
  cin >> n;
  while (n != -1) {
    C.posa(n);
    cin >> n;
  }

  while (!C.es_buit()) {
    cout << C.ultim() << ' ';
    C.treu();
  }
}
