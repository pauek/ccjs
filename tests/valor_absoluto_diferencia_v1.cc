// 
//  Haz una función que devuelva el valor absoluto
//  de la diferencia de dos enteros (sin usar
//  funciones de librería)
//

#include <iostream>
using namespace std;

int vabs_diferencia(int a, int b) {
  int d = a - b;
  if (d < 0) d = -d;
  return d;
}

int main() {
  int i, j;
  cout << "Dos enteros? ";
  cin >> i >> j;
  cout << "Valor absoluto diferencia: " 
       << vabs_diferencia(i, j) << endl;
}
