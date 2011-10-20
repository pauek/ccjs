// Titol: "Fibonacci" [RECORREGUT]
// Problema: Generar els números de la seqüència de Fibonacci
//           més petits que 1000.
// Sequència: Els números de Fibonacci

// Exemple:
// - entrada: [no hi ha entrada]
// - sortida: 0 1 1 2 3 5 8 13 21 34 ...

// Tècniques:
// - Variable amb l'element anterior
// - Intercanvi de variables

#include <iostream>
using namespace std;

int main() 
{
  int n, un, aux;
  
  // Obt. 1r
  un = 0;
  n = 1;
  
  while ( n < 1000 ) 
  {
    // Processar element
    cout << n << endl;
    
    // Obt. Seg.
    aux = n + un;
    un = n;
    n = aux;
  }
}
