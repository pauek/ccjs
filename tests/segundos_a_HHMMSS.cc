// 
//  A partir de un entero que sea un número de segundos
//  mostrar por pantalla el equivalente en horas, minutos y segundos
// 
#include <iostream>
using namespace std;

int main() {
  int segundos;
  cin >> segundos;
  cout << "Horas:    " << segundos / 3600 << endl;
  cout << "Minutos:  " << (segundos % 3600) / 60 << endl;
  cout << "Segundos: " << segundos % 60 << endl;
}
