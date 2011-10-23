
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

void data_escriu(const Data& d, ostream& out) {
  cout << d.dia << '/' << d.mes << '/' << d.any;
}

bool data_igual(const Data& d1, const Data& d2) {
  return d1.dia == d2.dia && d1.mes == d2.mes && d1.any == d2.any;
}

bool data_anterior(const Data& d1, const Data& d2) {
  if (d1.any != d2.any) {
    return d1.any < d2.any;
  } else if (d1.mes != d2.mes) {
    return d1.mes < d2.mes;
  } else {
    return d1.dia < d2.dia;
  }
}

int ultim_dia(int mes) {
  const int _dies_mes[13] = {
    -1, // el mes 0 no es farà servir
    31, 28, 31, 30, 31, 30, 
    31, 31, 30, 31, 30, 31 
  };
  return _dies_mes[mes];
}

void data_incrementa(Data& d, int dies) {
  d.dia += dies;
  int ultim = ultim_dia(d.mes);
  while (d.dia > ultim) {
    d.dia -= ultim;
    d.mes++;
    if (d.mes > 12) {
      d.mes = 1;
      d.any++;
    }
    ultim = ultim_dia(d.mes);
  }
}

/* Datos de entrada: un fichero con fechas, que provienen
   de las conexiones a un blog (visitantes) */

/* 2. El programa pide una fecha y un intervalo
      y muestra el número de conexiones en ese intervalo */

int main() {
  int dies;
  Data inici, fi;
  
  // Determinar interval
  cout << "Data inici (dia/mes/any)? ";
  data_llegeix(inici, cin);
  fi = inici;

  cout << "Interval (dies)? ";
  cin >> dies;
  data_incrementa(fi, dies);
  data_escriu(fi, cout);
  cout << endl;
  
  // Processar dades d'entrada
  Data d;
  int cont = 0;
  ifstream fin("connexions.txt");

  data_llegeix(d, fin);
  while (!fin.eof()) {
    if (data_igual(inici, d) || 
	(data_anterior(inici, d) && 
	 data_anterior(d, fi))) {
      cont++;
    }
    data_llegeix(d, fin);
  }
  
  cout << cont << " visites." << endl;
}

// Local variables:
// compile-command: "gcc -o dB dates_B.cc -lstdc++"
// End:
