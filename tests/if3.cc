
#include <iostream>
using namespace std;

int main() {
   string color;
   cin >> color;
   if (color == "blanco") {
      cout << 1 << endl;
   } else if (color == "amarillo") {
      cout << 2 << endl;
   } else if (color == "verde") {
      cout << 3 << endl;
   } else if (color == "rojo") {
      cout << 4 << endl;
   } else if (color == "azul") {
      cout << 5 << endl;
   } else if (color == "negro") {
      cout << 6 << endl;
   } else {
      cout << -1 << endl;
   }
}
