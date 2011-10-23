/*

Sumar las cifras del factorial de N.

 */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class BigInt {
  vector<int> _cifras;

  void _reset(int n);
  void _mult10(int pot);
  void _mult1(int n, BigInt& R) const;
public:
  BigInt();
  BigInt(int n);
  BigInt(const BigInt& E);

  int  ncifras() const;
  int  cifra(int k) const;

  void lee(istream& i);
  void escribe(ostream& o) const;

  BigInt operator+(const BigInt& E) const;
  BigInt operator*(const BigInt& E) const;
};

istream& operator>>(istream& i, BigInt& E) {
  E.lee(i);
  return i;
}

ostream& operator<<(ostream& o, const BigInt& E) {
  E.escribe(o);
  return o;
}

BigInt::BigInt() {}

BigInt::BigInt(int n) {
  _reset(n);
}

BigInt::BigInt(const BigInt& E) : _cifras(E._cifras) {}

void BigInt::_reset(int n) {
  while (n > 0) {
    _cifras.push_back(n % 10);
    n /= 10;
  }
}

int BigInt::cifra(int k) const {
  if (k < _cifras.size()) {
    return _cifras[k];
  } else {
    return 0;
  }
}

int BigInt::ncifras() const { return _cifras.size(); }

void BigInt::lee(istream& i) {
  _cifras.clear();
  char c;
  cin >> c; // salta espacios
  while (isdigit(c)) {
    _cifras.insert(_cifras.begin(), c - '0');
    i.get(c);
  }
  i.putback(c);
  if (_cifras.empty()) {
    i.setstate(ios::failbit);
  }
}

void BigInt::escribe(ostream& o) const {
  int N = _cifras.size();
  if (N == 0) {
    o << '0';
  } else {
    for (int i = N - 1; i >= 0; i--) {
      o << _cifras[i];
    }
  }
}

BigInt BigInt::operator+(const BigInt& E) const {
  BigInt resultado;
  int ncif = max(ncifras(), E.ncifras());
  int i = 0, suma = cifra(i) + E.cifra(i);
  while (suma > 0 || i < ncif) {
    resultado._cifras.push_back(suma % 10);
    i++;
    suma = cifra(i) + E.cifra(i) + suma / 10;
  }
  return resultado;
}

void BigInt::_mult10(int pot) {
  for (int i = 0; i < pot; i++) {
    _cifras.insert(_cifras.begin(), 0);
  }
}

void BigInt::_mult1(int k, BigInt& resultado) const {
  resultado._cifras.clear();
  int ncif = ncifras();
  int i = 0, mult = cifra(i) * k;
  while (mult > 0 || i < ncif) {
    resultado._cifras.push_back(mult % 10);
    i++;
    mult = cifra(i) * k + mult / 10;
  }
}

BigInt BigInt::operator*(const BigInt& E) const {
  BigInt resultado;
  for (int i = 0; i < E.ncifras(); i++) {
    BigInt parcial;
    _mult1(E.cifra(i), parcial);
    parcial._mult10(i);
    resultado = resultado + parcial;
  }
  return resultado;
}

int main() {
  BigInt F(1);
  int N;
  cin >> N;
  for (int i = 2; i <= N; i++) {
    BigInt A(i);
    F = F * A;
  }
  cout << F << endl;
  int suma = 0;
  for (int i = 0; i < F.ncifras(); i++) {
    suma += F.cifra(i);
  }
  cout << suma << endl;
}
