//
//  Escribir por pantalla todos los números de 3 cifras tales
//  que la suma de las centenas y las decenas sea igual a las 
//  unidades
//

#include <iostream>
using namespace std;

int main() {
  int u, d;
  for (u = 0; u < 10; u++) {
    for (d = 0; d <= u; d++) {
      if (u - d > 0) {
	cout << (u - d) << d << u << ' ';
      }
    }
  }
  cout << endl;
}
