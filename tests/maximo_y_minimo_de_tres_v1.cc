// 
//  Dados tres números reales, hacer una función que devuelva 
//  el máximo y otra que devuelva el mínimo.
//

#include <iostream>
using namespace std;

double maximo(double a, double b, double c) {
  if (a < b) a = b;
  if (a < c) a = c;
  return a;
}

double minimo(double a, double b, double c) {
  if (a > b) a = b;
  if (a > c) a = c;
  return a;
}

int main() {
  double x, y, z;
  cout << "Tres reales? ";
  cin >> x >> y >> z;
  cout << "Maximo: " << maximo(x, y, z) << endl;
  cout << "Mínimo: " << minimo(x, y, z) << endl;
}
