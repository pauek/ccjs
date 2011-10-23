
#include <iostream>
using namespace std;

class A {
  int _x;
public:
  A(int x);
  void f(int x);
};

A::A(int x) { _x = x + 1; }
void A::f(int x) { cout << /*_*/x; }

struct B { 
  int y; 
  B();
  int f();
};

B::B() { y = -4; }
int B::f() { return y + 1; }

A *f(B *b) {
  return new A(b->f());
}

int main() {
  f(new B())->f(-1);
}

// Local variables:
// compile-command: "gcc -o q q1.cc -lstdc++"
// End:
