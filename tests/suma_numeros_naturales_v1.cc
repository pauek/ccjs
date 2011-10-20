// 
//  Haz una función que calcula la suma de los primeros N
//  números naturales
//

#include <iostream>
using namespace std;

int suma_1_hasta_N(int N) {
  int i, suma = 0;
  for (i = 1; i <= N; i++) {
    suma = suma + i;
  }
  return suma;
}

int main() {
  int n;
  cout << "Numero? ";
  cin >> n;
  cout << "La suma [1.." << n << "] es " 
       << suma_1_hasta_N(n) << endl;
}
