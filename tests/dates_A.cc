
#include <iostream>
#include <fstream>
using namespace std;

struct Data {
  int dia, mes, any;
};

void data_llegeix(Data& d, istream& in) {
  char barra;
  in >> d.dia >> barra >> d.mes >> barra >> d.any;
}

bool data_igual(const Data& d1, const Data& d2) {
  return d1.dia == d2.dia && d1.mes == d2.mes && d1.any == d2.any;
}

/* Datos de entrada: un fichero con fechas, que provienen
   de las conexiones a un blog (visitantes) */

/* 1. El programa pide una fecha, y muestra 
      el número de conexiones en esa fecha */

int main() {
  Data data;
  
  // Determinar interval
  cout << "Data (dia/mes/any)? ";
  data_llegeix(data, cin);
  
  // Processar dades d'entrada
  Data d;
  int cont = 0;
  ifstream fin("connexions.txt");

  data_llegeix(d, fin);
  while (!fin.eof()) {
    if (data_igual(d, data)) {
      cont++;
    }
    data_llegeix(d, fin);
  }
  
  cout << cont << " visites." << endl;
}

// Local variables:
// compile-command: "gcc -o dA dates_A.cc -lstdc++"
// End:
