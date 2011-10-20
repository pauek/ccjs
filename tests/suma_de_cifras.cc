// 
//  Haz una función que reciba un entero y calcule
//  la suma de sus cifras
//

#include <iostream>
using namespace std;

int suma_cifras(int n) {
  int suma = 0;
  while (n > 0) {
    suma += n % 10;
    n = n / 10;
  }
  return suma;
}

int main() {
  int k;
  cout << "Entero? ";
  cin >> k;
  cout << "Las cifras de " << k << " suman " 
       << suma_cifras(k) << endl;
}
