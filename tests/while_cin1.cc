
#include <iostream>
using namespace std;

int main() {
   int a, max;
   cin >> a;
   max = a;
   while (cin >> a) {
      if (a > max) {
         max = a;
      }
   }
   cout << max << endl;
}
