
#include <iostream>
using namespace std;

struct Data {
  int dia, mes, any;
};

void data_llegeix(Data& d, istream& in) {
  in >> d.dia >> d.mes >> d.any;
}

void data_escriu(const Data& d, ostream& out) {
  out << d.dia << '.' << d.mes << '.' << d.any;
}

int dies_mes(int mes) {
  const int _dies_mes[12] = { 
    31, 28, 31, 30, 31, 30, 
    31, 31, 30, 31, 30, 31 
  };
  return _dies_mes[mes];
}

void data_incrementa(Data& d, int dies) {
  d.dia += dies;
  int max = dies_mes(d.mes);
  while (d.dia > max) {
    d.dia -= max;
    d.mes++;
    max = dies_mes(d.mes);
  }
  if (d.mes > 12) {
    d.any += d.mes / 12;
    d.mes = d.mes % 12;
  }
}

/* Datos de entrada: un fichero con fechas, que provienen
   de las conexiones a un blog (visitantes) */

/* El programa pide una fecha y un intervalo, 
   y muestra el número de conexiones en ese intervalo */

int main() {
  Data desde, fins;
  int dies;
  
  // Determinar interval
  cout << "Data d'inici (dia mes any)? ";
  data_llegeix(desde, cin);
  fins = desde;
  
  cout << "Interval (dies)? ";
  cin >> dies;
  data_incrementa(fins, dies);

  // Processar dades d'entrada
  Data data;
  int cont = 0;
  ifstream fin("visites.txt");

  data_llegeix(data, fin);
  while (fin.eof()) 
  {
    if (data_anterior(desde, data) &&
		  data_anterior(data, fins)) {
		cont++;
    }
    data_llegeix(data, fin);
  }
  
  cout << cont << " visites." << endl;
}
