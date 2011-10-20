// Titol: "Creixent" [CERCA]
// Problema: Determinar si una seqüència és creixent
// Sequència: Enters amb sentinella -1

// Exemple:
// - entrada: 1 3 4 10 11 13 15 -1
// - sortida: Creixent

// Problemes equivalents:
// - determinar si una seqüència és decreixent

// Tècniques:
// - Variable especial per a l'element anterior

#include <iostream>
using namespace std;

int main()
{
  bool trobat = false;
  int n, un;

  // Suposem que la seq. té més d'1 element
  cin >> un >> n; 
  
  while (n != -1 && !trobat) 
  {
    if (n <= un) trobat = true;
    else {
      un = n;
      cin >> n;
    }
  }

  if (trobat) 
    cout << "Decreixent" << endl;
  else
    cout << "Creixent" << endl;
}
