// atzar.cc
// SR, febrer/06
// Implementacio d'una classe per treballar amb nombres aleatoris.


#include <algorithm>
#include "atzar.h"


atzar::atzar(int llavor) : llavor(llavor) { }


void atzar::seguent() {
  int x1, x0, z, z1, z0, w, w1, w0;
  x1 = llavor/65536L; x0 = llavor&65535L;
  z = 1894L*x0; z1 = z/65536L; z0 = z&65535L;
  w = 27319L*x1; w1 = w/32768L; w0 = w&32767L;
  llavor = 453816693L + 1894L*x1 + z1 + w1 - 2147483647L;
  llavor += 27319L*x0;
  if (llavor >= 0L) llavor -= 2147483647L;
  llavor += 32768L*z0;
  if (llavor >= 0L) llavor -= 2147483647L;
  llavor += 65536L*w0;
  if (llavor < 0L) llavor += 2147483647L;
}


double atzar::uniforme() {
  seguent();
  return (double)llavor/(double)2147483647L;
}


int atzar::uniforme(int esquerra, int dreta) {
  return esquerra + (int)(((double)(dreta - esquerra + 1))*uniforme());
}


double atzar::uniforme(int esquerra, int dreta, int dig) {
  int pow = 1;
  while (dig--) pow *= 10;
  return ((double)uniforme(esquerra*pow, dreta*pow))/(double)pow;
}


bool atzar::probabilitat(double p) {
  return uniforme() < p;
}


vector<int> atzar::permutacio(int n) {
  vector<int> V(n);
  for (int i = 0; i < n; ++i) V[i] = i;
  for (int i = n - 1; i > 0; --i) swap(V[i], V[uniforme(0, i)]);
  return V;
}
