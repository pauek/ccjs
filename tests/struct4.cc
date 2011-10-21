
#include <iostream>
using namespace std;

struct A {
   int c;
};

struct Blah {
   int a[7];
   A t;
};

int main() {
   Blah b;
   b.a[3] = 2;
   b.t.c = 1;
}
