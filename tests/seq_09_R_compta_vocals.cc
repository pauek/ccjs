// Titol: "Compta vocals" [RECORREGUT]
// Problema: Comptar el número de vocals en una seqüència de caracters.
// Sequència: Caracters en minúscules amb sentinella '.'

// Exemple:
// - entrada: ndfjytnrnweasnxnjhsooaszndf.
// - sortida: Hi ha 5 vocals

#include <iostream>
using namespace std;

int main()
{
  char c;
  int nvocals = 0;

  cin >> c;
  while (c != '.') 
  {
    if (c == 'a' || c == 'e' || c == 'i' || 
	c == 'o' || c == 'u') {
      nvocals++;
    }
    cin >> c;
  }
  cout << "Hi ha " << nvocals << " vocals" << endl;
}
