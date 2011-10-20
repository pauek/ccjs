
#include <iostream>
#include <iomanip>
using namespace std;

int fibonacci( int n )
{
  int i = 1, ui = 1, cont, aux;

  cont = 2;
  while ( cont <= n )
    {
      aux = i;
      i = i + ui;
      ui = aux;
      cont++;
    }
  
  return i;
}

int main()
{
  int n;
  cin >> n;
  cout << fibonacci(n) << endl;
}
