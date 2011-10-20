// Titol: "Titulitzar" [RECORREGUT]
// Problema: Donada una frase en minúscules, passar a majúscules el
//           primer caracter de cada paraula. 
// Sequència: Caracters en minúscules acabat en '.'

// Exemple:
// - entrada: lo que   el viento  se    llevo.
// - sortida: Lo Que   El Viento  Se    Llevo.

// Aclariments:
// - Fixeu-vos que les paraules poden estar separades més d'un espai.
// - Per poder llegir caracter a caracter (incloent els espais),
//   aquest programa fa servir la crida "cin.get()", que permet
//   obtenir el següent caracter introduït per l'usuari.

#include <iostream>
using namespace std;

int main()
{
  char c;
  char uc = ' '; // La 1a lletra serà majúscula...
  int lpar; // longitud de la paraula
  int npar = 0; // número de paraules

  c = cin.get();
  while (c != '.') 
  {
    if (uc == ' ' && c != ' ') {
      cout << char( int(c) - 32 );
    }
    else {
      cout << c;
    }

    uc = c;
    c = cin.get();
  }
  cout << endl;
}
