
#include <iostream>
using namespace std;

int main()
{
  int n, max;

  cin >> n;
  max = n;

  while (n != 0) 
    {
      if (n > max) 
	max = n;

      cin >> n;
    }

  cout << max << endl;
}
