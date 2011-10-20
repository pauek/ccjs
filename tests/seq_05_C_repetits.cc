// Titol: "Repetits" [CERCA]
// Problema: Determinar si en una seqüència hi ha elements 
//           consecutius repetits. 
// Sequència: Enters amb sentinella 0.

// Exemple:
// - entrada: 5 2 9 -1 -5 -2 8 3 -5 1 12 9 0
// - sortida: No hi ha elements consecutius repetits

// Tècniques:
// - Variable amb l'element anterior
// - Inicialitzar aquesta variable amb el sentinella
//   (que mai forma part de la seqüència mateixa)

#include <iostream>
using namespace std;

int main()
{
  int n, un = 0;
  bool trobat = false;

  cin >> n;
  while (n != 0 && !trobat)
  {
    if (un == n) trobat = true;
    else {
      un = n;
      cin >> n;
    }
  }
  
  if (trobat) 
    cout << "Hi ha elements consecutius repetits" << endl;
  else        
    cout << "NO hi ha elements consecutius repetits" << endl;
}
