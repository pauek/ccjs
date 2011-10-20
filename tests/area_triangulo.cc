// 
//  Haz una función que dada la base y altura de un triangulo, 
//  calcule el área
//

#include <iostream>
using namespace std;

double area_triangulo(double base, double altura) {
  return base * altura / 2.0;
}

int main() {
  int b, h;
  cout << "Base? ";   cin >> b;
  cout << "Altura? "; cin >> h;
  cout << "Area: " << area_triangulo(b, h) << endl;
}
