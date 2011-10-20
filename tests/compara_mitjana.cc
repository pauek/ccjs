//
//  Dada una tabla de enteros de máximo 100 casillas decir cuántos son
//  mayores, menores o iguales que la media.
//

#include <iostream>
using namespace std;

const int MAX = 100;

int main() {
  int T[MAX], i;

  // Aquí leeríamos T...

  // Calculamos la media
  int media = 0;
  for (i = 0; i < MAX; i++) {
    media = media + T[i];
  }
  media = media / MAX; // división entera!

  int mayor = 0, menor = 0, igual = 0;
  for (i = 0; i < MAX; i++) {
    if (T[i] > media) mayor++;
    else if (T[i] < media) menor++;
    else igual++;
  }

  cout << "Mayores " << mayor << endl
       << "Menores " << menor << endl
       << "Iguales " << igual << endl;
}
