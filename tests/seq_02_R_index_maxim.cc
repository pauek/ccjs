// Titol: "Índex de l'element màxim" [RECORREGUT]
// Problema: Mostrar l'índex de l'element màxim.
// Sequència: Enters amb sentinella -1

// Exemple:
// - entrada: 8 1 2 9 0 5 6 3 4 1 -1
// - sortida: 4

#include <iostream>
using namespace std;

int main()
{
  int n, max, idx, imax;
  cin >> n;
  idx = 1;
  max = n;
  while (n != -1) 
  {
    if (n > max) {
      max = n;
      imax = idx;
    }
    cin >> n;
    idx++;
  }
}
