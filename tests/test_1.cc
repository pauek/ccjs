
#include <iostream>
using namespace std;

int main() {
  int taula[5] = { 10, 15 };
  int *p;
  p = taula;
  cout << p[0] << ' ' << p[1] << endl;
}

// Local variables:
// compile-command: "gcc -o t1 test_1.cc -lstdc++"
// End:
