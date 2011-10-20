//
//  Calcular el mínimo común múltiple de dos enteros
//

#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  int n = 2, mcm = a * b;
  while (n < a || n < b) {
    if (a % n == 0 && b % n == 0) {
      a = a / n;
      b = b / n;
      mcm = mcm / n;
    }
    else n++;
  }

  cout << mcm << endl;
}
