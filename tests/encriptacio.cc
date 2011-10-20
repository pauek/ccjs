
#include <iostream>
using namespace std;

char encripta(char c, int a)
{
  int idx = int(c) - 97;
  idx = idx + a;
  return char( idx % 26 + 97 );
}

bool es_minuscula(char c)
{
  int idx = int(c) - 97;
  return idx >= 0 && idx < 26; 
}

int main()
{
  char c;

  c = cin.get();
  while ( c != '.' )
    {
      if ( es_minuscula( c ) )
	c = encripta( c, 1 );

      cout << c;
      c = cin.get();
    }

  cout << '.' << endl;
}
