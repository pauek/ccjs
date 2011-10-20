// 
//  Calcular la suma de los N primeros números naturales
//

#include <iostream>
using namespace std;

int main() {
  int N, suma = 0, i;
  cout << "Numero? ";
  cin >> N;
  for (i = 1; i <= N; i++) {
    suma = suma + i;
  }
  cout << suma << endl;
}
