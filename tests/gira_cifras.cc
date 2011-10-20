// 
//  Haz una función que dado un entero (como 7125) devuelva otro
//  entero con las mismas cifras en el orden inverso (5217)
//


#include <iostream>
using namespace std;

int invierte_cifras(int n) {
  int m = 0;
  while (n > 0) {
    m = 10 * m + n % 10;
    n = n / 10;
  }
  return m;
}

int main() {
  int k;
  cout << "Entero? ";
  cin >> k;
  cout << k << " con las cifras al revés es " 
       << invierte_cifras(k) << endl;
}
