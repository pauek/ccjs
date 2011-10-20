// 
//  Haz una función que devuelva el valor absoluto
//  de la diferencia de dos enteros (sin usar
//  funciones de librería)
//

#include <iostream>
using namespace std;

int vabs(int a) {
  if (a < 0) a = -a;
  return a;
}

int vabs_diferencia(int a, int b) {
  return vabs(a - b);
}

int main() {
  int i, j;
  cout << "Dos enteros? ";
  cin >> i >> j;
  cout << "Valor absoluto diferencia: " 
       << vabs_diferencia(i, j) << endl;
}
