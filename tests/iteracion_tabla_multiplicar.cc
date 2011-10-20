// 
//  Dado un entero positivo, mostrar su tabla de multiplicar
// 

#include <iostream>
using namespace std;

int main() {
  int N, i;
  cout << "Número? ";
  cin >> N;
  for (i = 1; i <= 10; i++) {
    cout << i << " * " << N << " = " << i*N << endl;
  }
}
