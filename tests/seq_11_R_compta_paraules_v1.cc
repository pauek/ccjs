// Titol: "Compta paraules" [RECORREGUT]
// Problema: Comptar el número de paraules en una seqüència de caracters.
// Sequència: Doble sequència:
//            - Paraula: Caracters en minúscules amb sentinella ' '
//            - Frase: Paraules amb sentinella '.'

// Exemple:
// - entrada: Los tios  que   fuman puro tienen cara de  canguro .
// - sortida: Hi ha 9 paraules

// Aclariments:
// - Fixeu-vos que l'entrada té paraules separades per més d'un espai.
// - Fixeu-vos que l'entrada té el punt separat de la última paraula.
// - Per poder llegir caracter a caracter (incloent els espais),
//   aquest programa fa servir la crida "cin.get()", que permet
//   obtenir el següent caracter introduït per l'usuari.

#include <iostream>
using namespace std;

int main()
{
  char c;
  int lpar; // longitud de la paraula
  int npar = 0; // número de paraules

  c = cin.get();
  while (c != '.') 
  {
    lpar = 0;
    while (c != ' ') {
      lpar++;
      c = cin.get();
    }
    if (lpar > 0) npar++;
    c = cin.get();
  }
  cout << "Hi ha " << npar << " paraules" << endl;
}
