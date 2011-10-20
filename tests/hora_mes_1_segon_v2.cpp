
#include <iostream>
using namespace std;

int main()
{
  int h, m, s;
  int segons;

  cin >> h >> m >> s;
  
  segons = (((h * 60) + m) * 60 + s);
  segons = segons + 1;
  h = (segons / 3600) % 24;
  m = (segons % 3600) / 60;
  s = segons % 60;

  cout << h << ':' 
       << m << ':' 
       << s << endl;
}
