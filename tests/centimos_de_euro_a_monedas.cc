// 
//  A partir de una cantidad de dinero en Euros (con céntimos)
//  escribe el equivalente en monedas de 1, 2, 5, 10, 20, 50 céntimos
//  y 1 y 2 Euros (100 y 200 céntimos) de forma que haya el menor
//  número posible de monedas de cada valor.
//

#include <iostream>
using namespace std;

const int valores[8] = { 
  200, 100, 50, 20, 10, 5, 2, 1 
};

const string nombres[8] = {
  "2 Euros", "1 Euro", 
  "50 céntimos", "20 céntimos", "10 céntimos", 
  "5 céntimos", "2 céntimos", "1 céntimo" 
};

int main() {
  double euros;
  int monedas[8], i, centimos;
  
  cout << "Euros? ";
  cin >> euros;
  centimos = int(euros * 100);

  for (i = 0; i < 8; i++) {
    monedas[i] = centimos / valores[i];
    centimos = centimos % valores[i];
  }
  
  cout << "Monedas:" << endl;
  for (i = 0; i < 8; i++) {
    if (monedas[i] != 0) {
      cout << monedas[i] << " moneda";
      if (monedas[i] > 1) cout << "s";
      cout << " de " << nombres[i] << endl;
    }
  }
}
