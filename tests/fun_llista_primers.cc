
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
  int N, i;

  cout << "Fins a quin numero vols mirar? ";
  cin >> N;

  for (i = 2; i <= N; i++) {
    if ( es_primer(i) ) 
      cout << i << ' ';
  }
  cout << endl;
}
