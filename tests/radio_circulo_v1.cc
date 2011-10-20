//
//  Haz una función que dado el radio de un
//  círculo calcule su área
//

#include <iostream>
#include <cmath>
using namespace std;

double area_circulo(double radio) {
  return M_PI * radio * radio;
}

int main() {
  double r;
  cout << "Radio? ";
  cin >> r;
  cout << "Area: " << area_circulo(r) << endl;
}
