
#include <iostream>
using namespace std;

bool de_traspas( int any )
{
  return (any % 4 == 0 && any % 100 != 0) || any % 400 == 0; 
}

int dies_mes( int mes, int any )
{
  int dies;
  switch (mes)
    {
    case 4: case 6: case 9: case 11:
      dies = 30;
      break;

    case 2:
      if ( de_traspas( any ) )
	dies = 29;
      else
	dies = 28;
      break;

    default: 
      dies = 31;
      break;
    }

  return dies;
}

int main()
{
  int d, m, a;
  
  cin >> d >> m >> a;
  
  ++d;
  if ( d > dies_mes( m, a ) )
    {
      d = 1;
      m++;
      if ( m > 12 )
	{
	  m = 1;
	  a++;
	}
    }

  cout << d << '/' << m << '/' << a << endl;
}
