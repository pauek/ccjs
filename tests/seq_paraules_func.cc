
// Calcular la longitud de la paraula 
// més llarga i la més curta
// "hola, com estas ." -> max: 5 min: 3

#include <iostream>
#include <string>
using namespace std;

bool es_lletra( char c )
{
  int asc = int(c);
  bool minusc = asc >= 97 && asc < 123;
  bool majusc = asc >= 65 && asc < 91;

  return majusc || minusc;
}

void llegeix_paraula( string& paraula, int& llarg )
{
  char c;
  llarg = 0;
  paraula = "";

  // Saltem les no lletres
  c = cin.get();
  while ( ! es_lletra(c) && c != '.' ) 
    c = cin.get();

  // Llegim les lletres
  while ( es_lletra(c) && c != '.')
    {
      paraula = paraula + c;
      llarg++;
      c = cin.get();
    }
}

int main()
{
  string paraula;
  int l, max = -1, min;
  
  llegeix_paraula( paraula, l );
  if ( paraula != "" )
    min = l;

  while ( paraula != "" )
    {
      if ( l > max ) max = l;
      if ( l < min ) min = l;

      llegeix_paraula( paraula, l );
    }

  if ( max > 0 )
    {
      cout << "Màxim: " << max << endl
	   << "Mínim: " << min << endl;
    }
}
