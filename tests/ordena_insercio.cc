
void ordenaInsercio(TaulaEnters& T) {
  int x, i, j;
  i = 1; 
  while (i < N) {
    x = T[i];
    j = i;
    while (j != 0 && x < T[j-1]) {
      T[j] = T[j-1];
      j = j-1;
    }
    T[j] = x;
    i = i+1;
  }
}
