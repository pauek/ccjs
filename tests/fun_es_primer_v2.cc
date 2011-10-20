
#include <iostream>
using namespace std;

bool es_primer(int N)
{
  int d = 2;

  while (d < N) 
    {
      if (N % d == 0) return true;
      else 
	d++;
    }

  return false;
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
