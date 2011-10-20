//
//  Dado un número natural, escribir los números naturales en orden
//  descendente.
//

#include <iostream>
using namespace std;

int main() {
  int N, i;
  cout << "Número? ";
  cin >> N;
  for (i = N; i > 0; i--) {
    cout << i << ' ';
  }
  cout << endl;
}
