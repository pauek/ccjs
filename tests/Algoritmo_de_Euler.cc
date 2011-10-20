// 
//  Haz una función que calcule el Máximo Común Divisor
//  de dos números naturales _a_ y _b_ por el algoritmo de Euler:
//
//    1. Si _a_ es igual a _b_, da como resultado _a_.
//
//    2. Si son distintos, cambia el mayor de los dos por la
//       diferencia entre ambos y vuelve al paso 1.
//

#include <iostream>
using namespace std;

int mcd(int a, int b) {
  while (a != b) {
    if (a > b) a = a - b;
    else b = b - a;
  }
  return a;
}

int main() {
  int n, m;
  cout << "Dos enteros? ";
  cin >> n >> m;
  cout << "MCD(" << n << ", " << m << ") = " 
       << mcd(n, m) << endl;
}
