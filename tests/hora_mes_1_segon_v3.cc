#include <iostream>
using namespace std;

int main()
{
  int h, m, s;

  cin >> h >> m >> s;

  if (s == 59) 
    {
      s = 0;
      if (m == 59)
	{
	  m = 0;
	  if (h == 23) 
	    h = 0; 
	  else 
	    h = h + 1;
	}
      else 
	m = m + 1;
    }
  else 
    s = s + 1;

  cout << h << ':'
       << m << ':'
       << s << endl;
}
