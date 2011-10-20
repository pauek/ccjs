
#include <iostream>
using namespace std;

int fact(int n)
{
  int fn = 1;
  while ( n > 1 ) {
    fn = fn * n;
    n--;
  }
  return fn;
}

int main()
{
  int a, b;

  cout << "Entra a i b: "; 
  cin >> a >> b;
  
  cout << fact(a) / ( fact(b) * fact(a - b) ) 
       << endl;
}
