
#include <iostream>
using namespace std;

int main()
{
  float nota;
  string snota;

  cin >> nota;

  switch ( int(nota) ) 
    {
    case 0:
    case 1:
    case 2: snota = "Molt deficient"; break;
    case 3:
    case 4: snota = "Suspès"; break;
    case 5:
    case 6: snota = "Aprovat"; break;
    case 7:
    case 8: snota = "Notable"; break;
    case 9: snota = "Excel·lent"; break;
    case 10: snota = "Matrícula d'Honor"; break;
    }
  
  cout << snota << endl;
  
}
