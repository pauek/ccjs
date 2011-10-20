
#include <iostream>
using namespace std;

int main()
{
  int N,x;

  cin >> N;
  x = N % 10; // 1r
  while (N > 0) // Últim
    {
      cout << x << endl;
      N = N / 10;  //
      x = N % 10;  // Següent
    }
}
