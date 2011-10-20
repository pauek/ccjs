
#include <iostream>
using namespace std;

int main()
{
  int a,b,res;
  char op;

  cout << "Entra dos nombres i una operació: ";
  cin >> a >> b >> op;

  switch (op) {
  case '+':
    res = a + b;
    break;

  case '-':
    res = a - b;
    break;

  case '*':
    res = a * b;
    break;

  case '/':
    res = a / b;
    break;
  }

  cout << "El resultat és: " << res << endl;
}
