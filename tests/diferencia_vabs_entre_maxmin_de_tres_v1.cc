// 
//  Haz una función que obtenga la diferencia en valor
//  absoluto entre el mayor y el menor de tres reales
//

#include <iostream>
using namespace std;

double vabs(double x) {
  if (x < 0.0) x = -x;
  return x;
}

void ordena(double& a, double& b) {
  if (a > b) {
    double tmp = a;
    a = b;
    b = tmp;
  }
}

double vabs_diferencia(double a, double b, double c) {
  // a -> max / c -> min
  ordena(a, b);
  ordena(a, c);
  ordena(b, c);
  return vabs(a - c);
}

int main() {
  double x, y, z;
  cout << "Tres reales? ";
  cin >> x >> y >> z;
  cout << "Dif. en valor absoluto entre mayor y menor: " 
       << vabs_diferencia(x, y, z) << endl;
}
