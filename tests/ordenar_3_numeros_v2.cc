//  
//  Escribe de mayor a menor tres números entrados 
//  por el teclado
// 

#include <iostream>
using namespace std;

int main() {
  int a, b, c;
  cin >> a >> b >> c;
  // Todas las posibilidades: abc, acb, bac, bca, cab, cba
  if (a >= b && b >= c) {
    cout << a << ' ' << b << ' ' << c << endl;
  } else if (a >= c && c >= b) {
    cout << a << ' ' << c << ' ' << b << endl;
  } else if (b >= a && a >= c) {
    cout << b << ' ' << a << ' ' << c << endl;
  } else if (b >= c && c >= a) {
    cout << b << ' ' << c << ' ' << a << endl; 
  } else if (c >= a && a >= b) {
    cout << c << ' ' << a << ' ' << b << endl;
  } else {
    cout << c << ' ' << b << ' ' << a << endl;
  }
  cout << endl;
}
