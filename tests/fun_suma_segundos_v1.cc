
#include <iostream>
using namespace std;

void suma_seg(int& h, int& m, int& s, int num)
{
  int seg = (((h * 60) + m) * 60) + s;
  seg = seg + num;
  h = (seg / 3600) % 24;
  m = (seg % 3600) / 60;
  s = seg % 60;
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
