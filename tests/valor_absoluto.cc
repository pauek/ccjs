// 
// Haz una función que devuelva el valor absoluto de 
// un número real (sin utilizar funciones de librería)
//

#include <iostream>
using namespace std;

double valor_absoluto(double x) {
  if (x < 0.0) x = -x;
  return x;
}

int main() {
  double a;
  cout << "Real? ";
  cin >> a;
  cout << "Valor absoluto: " << valor_absoluto(a) << endl;
}
