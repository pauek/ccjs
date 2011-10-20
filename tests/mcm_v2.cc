//
//  Calcular el mínimo común múltiple de dos enteros
//

#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  
  int n = 1;
  while ((a * n) % b != 0) {
	 n++;
  }

  cout << a * n << endl;
}
