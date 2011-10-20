//
//  Calcular el mínimo común múltiple de dos enteros
//

#include <iostream>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  
  int n = 2, mcm = 1;
  while (a > 1 || b > 1) {
	 bool div = false;
	 if (a % n == 0) {
		a = a / n;
		div = true;
	 }
	 if (b % n == 0) {
		b = b / n;
		div = true;
	 }
	 if (div) {
		mcm = mcm * n;
	 } else {
		n++;
	 }
  }

  cout << mcm << endl;
}
