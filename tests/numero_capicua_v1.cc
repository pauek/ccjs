
#include <iostream>
using namespace std;

// Retorna el número de xifres d'un enter
int num_xifres( int num )
{
  int k = 0;
  while ( num > 0 ) {
    k++;
    num = num / 10;
  }
  return k;
}

// Retorna 10 elevat a x
int pot10( int x )
{
  int p = 1;
  for (; x > 0; x--) p = p * 10;
  return p;
}

// Obté una xifra d'un número
int xifra( int num, int x )
{
  return ( ( num / pot10(x) ) % 10 );
}

int main()
{
  int x, n, k;
  bool trobat = false;

  cin >> x;
  n = num_xifres(x);

  k = 0;
  while ( k < n/2 && !trobat ) {
    if ( xifra( x, k ) != xifra( x, n-1-k ) )
      trobat = true;
    else
      k++;
  }

  if (trobat) 
    cout << "El nombre NO és capicua" << endl;
  else
    cout << "El nombre és capicua" << endl;
}
