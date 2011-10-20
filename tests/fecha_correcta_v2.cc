//
//  Haz una función Booleana que indique si una fecha es correcta
//  a partir del dia, mes y año. Una fecha incorrecta seria:
//
//     35/-1/1090
//

#include <iostream>
using namespace std;

bool es_bisiesto(int anyo) {
  return (anyo % 4 == 0 && anyo % 100 != 0) || anyo % 400 == 0;
}

int dias_mes(int mes, int anyo) {
  int dias = 31; // Suponemos la mayoría
  if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    dias = 30;
  } else if (mes == 2) {
    dias = 28;
    if (es_bisiesto(anyo)) dias = 29; 
  }
  return dias;
}

bool fecha_correcta(int dia, int mes, int anyo) {
  return 
    mes >= 1 && mes <= 12 && 
    dia >= 1 && dia <= dias_mes(mes, anyo);
}

int main() {
  int dia, mes, anyo;
  char c;
  cout << "Entra una fecha (dd/mm/aaaa): ";
  cin >> dia >> c >> mes >> c >> anyo;
  if (fecha_correcta(dia, mes, anyo)) {
    cout << "Correcta";
  } else {
    cout << "Incorrecta";
  }
  cout << endl;
}
