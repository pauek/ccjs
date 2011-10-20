
#include <iostream>
using namespace std;

// Càlcul directe: li donem la volta a l'enter acumulant
// les xifres en ordre invers i comparem amb l'original.
int main()
{
  int N, Norig, acum = 0;
  cin >> N;
  Norig = N; // ens guardem el original
  
  while (N > 0) {
    acum = acum*10 + N % 10; 
    N = N / 10;
  }
  
  if ( acum == Norig ) {
    cout << "El nombre és capicua" << endl;
  }
  else {
    cout << "El nombre NO és capicua" << endl;
  }
}
