
#include <iostream>
using namespace std;

int main()
{
  int n, max = -1; // Inicialización dudosa...

  cin >> n;

  while (n != 0) 
    {
      if (n > max) 
	max = n;

      cin >> n;
    }

  cout << max << endl;
}
