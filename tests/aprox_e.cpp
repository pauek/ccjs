
#include <iostream>
using namespace std;

// e^x: 1 + x + x^2/2! + x^3/3! + x^4/4! + ...

// en nmax = 35 --> inf...

int main()
{
  int nmax, fact = 1, i = 1;
  double e = 1.0;

  cin >> nmax;
  
  while ( i < nmax )
  {
    e += 1.0 / float(fact);
    i++;
    fact *= i;
  }

  cout.precision(15);
  cout << e << endl;
}
