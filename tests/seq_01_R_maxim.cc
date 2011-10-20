// Titol: "Element màxim" [RECORREGUT]
// Problema: Mostrar l'element màxim.
// Sequència: Enters amb sentinella -1

// Exemple:
// - entrada: 5 4 3 12 7 -3 -6 2 0 -1
// - sortida: 12

// Problemes equivalents:
// - calcular el mínim.

#include <iostream>
using namespace std;

int main()
{
  int n, max;
  cin >> n;
  max = n;
  while (n != -1) 
  {
    if (n > max) {
      max = n;
    }
    cin >> n;
  }
  cout << max;
}
