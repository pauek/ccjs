//
//  Dada una tabla de enteros de 100 casillas hacer una rotación (es
//  decir, mover el elemento 1 a la posición 2, el 2 al 3, el 3 al 4,
//  etc. y el último al primero) y mostrar el resultado.
//

#include <iostream>
using namespace std;

const int MAX = 100;

int main() {
  int T[MAX], i;

  // Aquí leeríamos T...

  int ultimo = T[MAX-1];
  for (i = 1; i < MAX; i++) {
    T[i] = T[i-1];
  }
  T[0] = ultimo;

  // Aquí escribiríamos T...  
}
