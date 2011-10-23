
const int N = 30000;
typedef int TaulaEnters[N];

void omplirTaulaAscendent(TaulaEnters& T) {
  for (int i = 0; i < N; i++) {
    T[i] = i;
  }
}

void ordenaSeleccio(TaulaEnters& T) {
  int j = 0, k, menor, aux;
  while (j < N-1) {
    menor = j;
    k = j + 1;
    while (k < N) {
      if (T[k] < T[menor]) menor = k;
      k = k + 1;
    }
    aux = T[j];
    T[j] = T[menor];
    T[menor] = aux;
    j = j + 1;
  }
}

int main () {
  TaulaEnters T;
  omplirTaulaAscendent(T);
  ordenarSeleccio(T);
}

// Local variables:
// compile-command: "gcc -o efs eficiencia_seleccio.cc -lstdc++"
// End:
