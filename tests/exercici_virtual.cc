
#include <iostream>
using namespace std;

// <<<
class Prst {
public:
  virtual void f() const;
  void g(char c);
};

void Prst::f() const {
  cout << "$$";
}

void Prst::g(char c) {
  cout << "{" << c << "}";
}

class Bgts : public Prst {
public:
  void f() const;
};

void Bgts::f() const {
  cout << "##";
}

class Qvzo : public Prst {
public:
  void g(char c);       
};

void Qvzo::g(char c) {
  cout << "[" << c << "]";
}

int main() {
  Prst *p = new Prst;
  Prst *q = new Bgts;
  Prst *r = new Qvzo;
  p->f();
  q->f();
  r->f();
  p->g('x');
  p->g('y');
  p->g('z');
}
// >>>

// Local variables:
// compile-command: "gcc -o e1 exercici_1.cc -lstdc++"
// End:
