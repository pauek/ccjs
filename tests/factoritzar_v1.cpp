
#include <iostream>
using namespace std;

int main()
{
  int n,d;

  cin >> n;

  while (n > 1) 
    {
      d = 2;
      while (n % d != 0) d++;
      
      cout << d << ' ';
      n = n / d;
    }

  cout << endl;
}
