// 
//  Haz una función que dados dos números reales, 
//  devuelva el mayor de los dos (el máximo).
//

#include <iostream>
using namespace std;

double maximo(double a, double b)  {
  double max;
  if (a > b) max = a;
  else max = b;
  return max;
}

int main() {
  double x, y;
  cout << "Dos reales? "; 
  cin >> x >> y;
  cout << "El máximo de " << x << " y " << y 
       << " es " << maximo(x, y) << endl;
}
