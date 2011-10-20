
#include <iostream>
using namespace std;

const int N = 7;
typedef int tTab[N];

void omp(tTab t)
{
  int k;
  for (k = 0; k < N; k++) 
    t[k] = N - k;
}

void shw(tTab a)
{
  int k;

  cout << a[0];
  for (k = 1; k < N; k++)
    cout << ' ' << a[k];
  
  cout << endl;
}

void cosa(tTab m, int& acum)
{
  int n, k, tmp;
  
  for (n = N - 1; n >= 0; n--) 
    {
      shw(m);
      for (k = 0; k < n; k++)
	{
	  if (m[k] > m[k+1])
	    {
	      tmp = m[k];
	      m[k] = m[k+1];
	      m[k+1] = tmp;
	      
	      acum++;
	    }
	}
    }
}

int main()
{
  int n = 0;
  tTab T;

  omp(T);
  cosa(T,n);

  cout << n << endl;
}

