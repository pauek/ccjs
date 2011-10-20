
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  double x,y,r,a;

  cout << "Entra (r,a) en polars: " << endl;
  cin >> r >> a;

  x = r * cos(a);
  y = r * sin(a);

  cout << x << ' ' << y << endl;
}
