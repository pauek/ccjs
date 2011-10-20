//
//  Dada una tabla de enteros de 200 casillas invertir el orden
//  de las casillas
//

#include <iostream>
using namespace std;

const int MAX = 100;

int main() {
  int T[MAX], i;

  // Aquí leeríamos T...

  for (i = 0; i < MAX/2; i++) {
    int tmp = T[i];
    T[i] = T[MAX-1-i];
    T[MAX-1-i] = tmp;
  }

  // Aquí escribiríamos T...  
}
