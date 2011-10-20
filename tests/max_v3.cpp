
#include <iostream>
using namespace std;

int main()
{
  int n, max;
  bool start = true;

  cin >> n;

  while (n != 0) 
    {
      if (n > max || start) 
	{
	  max = n;
	  start = false;
	}

      cin >> n;
    }

  // Imprime sólo si hay secuencia...
  if (start) cout << max << endl;
}
