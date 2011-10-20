
#include <iostream>
using namespace std;

int main()
{
  int a,b,aux;
  cin >> a >> b;

  while ( b != 0 ) {
    aux = b;
    b = a % b;
    a = aux;
  }

  cout << a << endl;
}

// Local variables:
// compile-command: "gcc -o eu euclides.cpp -lstdc++"
// End:
