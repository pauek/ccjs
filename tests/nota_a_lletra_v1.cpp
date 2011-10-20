
#include <iostream>
using namespace std;

int main()
{
  float nota;
  string snota;

  cin >> nota;

  // Suposem: nota >= 0.0 && nota < 10.0
  if (nota < 3.0)
    cout << "Molt deficient" << endl;
  else if (nota < 5.0)
    cout << "Suspès" << endl;
  else if (nota < 7.0)
    cout << "Aprovat" << endl;
  else if (nota < 9.0)
    cout << "Notable" << endl;
  else if (nota < 10.0)
    cout << "Excel·lent" << endl;
  else 
    cout << "Matrícula d'Honor" << endl;
}
