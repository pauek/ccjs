// Titol: "Longitud de les paraules" [RECORREGUT]
// Problema: Calcular la longitud mínima i màxima de les paraules
//           d'una frase
// Sequència: Doble sequència:
//            - Paraula: Caracters en minúscules amb sentinella ' '
//            - Frase: Paraules amb sentinella '.'

// Exemple:
// - entrada: el constructivisme mou muntanyes .
// - sortida: Màxima 15, mínima 2.

// Aclariments:
// - Fixeu-vos que l'entrada té el punt separat de la última paraula.
// - Per poder llegir caracter a caracter (incloent els espais),
//   aquest programa fa servir la crida "cin.get()", que permet
//   obtenir el següent caracter introduït per l'usuari.
// - Evitem les paraules amb longitud 0, que apareixen quan trobem
//   2 espais seguits).

// Tècniques:
// - Per calcular la longitud mínima, inicialitzem el mínim a -1
//   i l'actualitzem tant si és -1 (la primera vegada) com si és 
//   menor que el que hi havia. Es pot veure el -1 com un "precinte".

#include <iostream>
using namespace std;

int main()
{
  char c;
  int lpar; // longitud de la paraula
  int max = 0, min = -1; // número de paraules

  c = cin.get();
  while (c != '.') 
  {
    lpar = 0;
    while (c != ' ') {
      lpar++;
      c = cin.get();
    }
    if (lpar > 0) {
      if (lpar > max) max = lpar;
      if (lpar < min || min == -1) min = lpar;
    }
    c = cin.get();
  }
  cout << "Màxima " << max 
       << ", mínima " << min 
       << '.' << endl;
}
