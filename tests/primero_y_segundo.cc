//
//  Determinar el máximo y el segundo más grande en una secuencia de
//  enteros acabada en 0 (con almenos dos elementos)
// 

#include <iostream>
using namespace std;

int main() {
  int n, pri, seg;
  
  cin >> n;
  pri = n;
  seg = 0; // ***
  while (n != 0) {
    if (n >= pri) {
      seg = pri;
      pri = n;
    } else if (n > seg) {
      seg = n;
    }
    cin >> n;
  }
  cout << pri << ' ' << seg << endl;
}

// ***: inicializamos el segundo al centinela, 
//      que además es más pequeño que todos los otros
