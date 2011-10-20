
#include <iostream>
using namespace std;

bool es_primer(int N)
{
  bool trobat = false;
  int d = 2;

  while (d < N && !trobat) 
    {
      if (N % d == 0) trobat = true;
      else 
	d++;
    }

  return !trobat;
}

int main()
{
  int N;

  cin >> N;

  if ( es_primer(N) ) 
    cout << N << " NO és primer" << endl;
  else
    cout << N << " és primer" << endl;
}
