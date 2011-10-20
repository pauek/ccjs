// 
//  Dados tres números reales, hacer una función que devuelva 
//  el máximo y otra que devuelva el mínimo.
//

#include <iostream>
using namespace std;

double max(double a, double b) {
  if (a < b) a = b;
  return a;
}

double min(double a, double b) {
  if (a > b) a = b;
  return a;
}

double maximo(double a, double b, double c) {
  return max(a, max(b, c)); // también max(max(a, b), c)
}

double minimo(double a, double b, double c) {
  return min(a, min(b, c)); // también min(min(a, b), c)
}

int main() {
  double x, y, z;
  cout << "Tres reales? ";
  cin >> x >> y >> z;
  cout << "Maximo: " << maximo(x, y, z) << endl;
  cout << "Mínimo: " << minimo(x, y, z) << endl;
}
