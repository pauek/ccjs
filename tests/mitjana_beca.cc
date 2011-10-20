
#include <iostream>
using namespace std;

// Suposem nota >= 5.0 && nota <= 10.0

int main()
{
  float nota;
  int acum = 0, total = 0;

  cin >> nota;
  while (nota != -1.0) 
    {
      if (nota < 7.0)       
	acum = acum + 1;
      else if (nota < 9.0)  
	acum = acum + 2;
      else if (nota < 10.0) 
	acum = acum + 3;
      else                  
	acum = acum + 4;

      total++;
      cin >> nota;
    }

  cout << float(acum) / float(total) << endl;
}
