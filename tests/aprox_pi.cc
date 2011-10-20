
#include <iostream>
using namespace std;

// Pi és ~ 4 * 2/3 * 4/3 * 4/5 * 6/5 * 6/7 * ...

int main()
{
  double pi = 4.0;
  int nmax, i = 1;
  int num = 2, den = 3;

  cin >> nmax; // assumim nmax > 1

  while ( i < nmax )
  {
    pi *= float(num) / float(den);
    if ( i % 2 == 0 )
      den += 2;
    else
      num += 2;

    i++;
  }

  cout.precision(10);
  cout << pi << endl;
}
