// Titol: "Mitjana" [RECORREGUT]
// Problema: Calcular la mitjana d'una sequència de nombres
// Sequència: Enters amb sentinella 0

// Exemple:
// - entrada: 5 3 9 4 2 10 8 1
// - sortida: 5.25

// Tècniques:
// - Acumulador per a la suma
// - Comptar els elements
// - Conversió a float prèvia a fer la divisió.

#include <iostream>
using namespace std;

int main()
{
  int n, suma = 0, total = 0;
  
  cin >> n;
  while (n != 0) 
  {
    suma = suma + n;
    total++;
    
    cin >> n;
  }

  cout << float(suma)/float(total) << endl;
}
