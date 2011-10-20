//
//  Calcular el mínimo común múltiple de dos enteros
//

#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  
  int m = a;
  if (m < b) {
	 m = b;
  }

  while (m % a != 0 || m % b != 0) {
	 m++;
  }

  cout << m << endl;
}
