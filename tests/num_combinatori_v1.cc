
#include <iostream>
using namespace std;

int main()
{
  int a,b,amb; // amb = a menys b
  int fa,fb,famb;

  cout << "Entra a i b: "; 
  cin >> a >> b;
  
  amb = a - b; // suposem a > b
  
  int fa = 1;
  while ( a > 1 ) {
    fa = fa * a;
    a--;
  }

  int fb = 1;
  while ( b > 1 ) {
    fb = fb * b;
    b--;
  }

  int famb = 1;
  while ( amb > 1 ) {
    famb = famb * amb;
    amb--;
  }

  cout << fa / ( fb * famb ) << endl;
}
