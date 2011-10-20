// 
//  Haz una función que calcula la suma de los primeros N
//  números naturales
//

#include <iostream>
using namespace std;

// Alicamos la igualdad:
//
//    1 + 2 + ... + N = N * (N-1) / 2
//
int suma_1_hasta_N(int N) {
  return N * (N - 1) / 2;
}

int main() {
  int n;
  cout << "Numero? ";
  cin >> n;
  cout << "La suma [1.." << n << "] es " 
       << suma_1_hasta_N(n) << endl;
}
