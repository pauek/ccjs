// Titol: "És primer" [CERCA]
// Problema: Determinar si un enter 'n' és primer
// Sequència: Divisors desde 2 fins a n-1

// Exemple:
// - entrada: 151
// - sortida: 151 és primer

#include <iostream>
using namespace std;

int main()
{
  bool trobat = false;
  int N,d;

  cin >> N; // Inici tractament
  d = 2;    // Obtenir 1r element

  while (d < N && !trobat) 
    {
      if (N % d == 0) trobat = true;
      else {
	d++; // Obtenir el següent
      }
    }

  cout << N;
  if (trobat) {
    cout << " NO";
  }
  cout << " és primer" << endl;
}
