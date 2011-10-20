//
//  Haz una función que dado el radio de un
//  círculo calcule su área
//

#include <iostream>
using namespace std;

const double Pi = 3.1415926535;

double area_circulo(double radio) {
  return Pi * radio * radio;
}

int main() {
  double r;
  cout << "Radio? ";
  cin >> r;
  cout << "Area: " << area_circulo(r) << endl;
}
