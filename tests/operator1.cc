
#include <iostream>
using namespace std;

struct A { 
  int a; 
  void operator+=(const A& a);
};

void A::operator+=(const A& x) {
  a += x.a;
}

int main() {}
