
// No fa servir l'esquema

#include <iostream>
using namespace std;

int main()
{
  int n, un;
  cin >> un >> n;
  
  while (n != 0 && n != un) 
  {
    un = n;
    cin >> n;
  }
  
  if (n == 0)
    cout << "No hi ha repetits" << endl;
  else
    cout << "Hi ha algun repetit" << endl;
}
