//
//  Dados dos vectores reales de máximo 50 elementos, calcular
//  la suma componente a componente.
//

#include <iostream>
using namespace std;

const int MAX = 50;

int main() {
  int i;
  double v1[MAX], v2[MAX], suma[MAX];
  
  // Aquí leeríamos v1 y v2...

  for (i = 0; i < MAX; i++) {
    suma[i] = v1[i] + v2[i];
  }

  // Aqui escribiríamos suma
}
