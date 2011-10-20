
#include <iostream>
using namespace std;

const int MAX_ELEM = 10000;

struct tLlistaEnters 
{
  int elem[MAX_ELEM];
  int nelems;
};

int cerca_binaria(const tLlistaEnters& L, int x)
{
  int esq = -1, dre = L.nelems, mig;

  if (L.nelems <= 0 || L.elem[0] > x || L.elem[L.nelems-1] < x)
    return -1;

  while ( dre - esq > 1 )
    {
      mig = ( esq + dre ) / 2;
      cout << esq << ' ' << mig << ' ' << dre << endl;
      if ( L.elem[mig] < x )      esq = mig;
      else if ( L.elem[mig] > x ) dre = mig;
      else {
	esq = mig;
	dre = mig;
      }
    }

  if (L.elem[mig] != x) mig = -1;

  return mig;
}

void llegeix_llista( tLlistaEnters& L )
{
  int k;

  cout << "Entra el tamany de la llista: ";
  cin >> L.nelems;

  for ( k = 0; k < L.nelems; k++ )
    cin >> L.elem[k];
}


int main()
{
  int x;
  tLlistaEnters L;

  llegeix_llista(L);


  cout << "Cerca? ";
  cin >> x;

  int k = cerca_binaria( L, x );
  if (k < 0)
    cout << "Element no trobat" << endl;
  else
    cout << "L'element " << x << " té index " << k << endl;
}
