//  
//  Escribe de mayor a menor tres números entrados 
//  por el teclado
// 

#include <iostream>
using namespace std;

void ordena(int& a, int& b) {
  int tmp;
  if (a < b) {
    tmp = a;
    a = b;
    b = tmp;
  }
}

int main() {
  int a, b, c, tmp;
  cin >> a >> b >> c;
  ordena(a, b);
  ordena(a, c);
  ordena(b, c);
  cout << a << ' ' << b << ' ' << c << endl;
}
