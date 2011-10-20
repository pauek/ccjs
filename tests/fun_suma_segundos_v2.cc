
#include <iostream>
using namespace std;

void suma_seg(int& h, int& m, int& s, int num)
{
  s = s + num;
  if ( s >= 60 )
    {
      m = m + s / 60;
      s = s % 60;

      if ( m >= 60 )
	{
	  h = h + m / 60;
	  m = m % 60;

	  if ( h >= 24 )
	    {
	      h = h % 24;
	    }
	}
    }
}

int main()
{
  int h, m, s;
  int n;

  cin >> h >> m >> s;
  cin >> n;

  suma_seg(h, m, s, n);

  cout << h << ':' 
       << m << ':' 
       << s << endl;
}
