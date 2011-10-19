
#include <iostream>
using namespace std;

int main() {
   int n, min;
   cin >> n;
   min = n;
   while (n != -1) {
      if (n < min) {
         min = n;
      }
      cin >> n;
   }
   cout << min << endl;
}
