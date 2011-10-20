
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  double x,y,r,a;

  cout << "Entra (x,y) en cartesianes: " << endl;
  cin >> x >> y;
  
  r = sqrt( x * x + y * y );
  a = atan( y / x );  // No és correcte 100%

  cout << r << ' ' << a << endl;
}
