
#include <iostream>
using namespace std;

struct Int {
  int it;
};

Int* the_int(int k) {
  static Int T[10];
  return &T[k];
}

int main() {
  the_int(2)->it = 3;
  cout << the_int(7)->it << endl;
}
