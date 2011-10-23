
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
   vector<int> v;
   ifstream F;
   F.open("nombres.txt");
   F >> n;
   while (!F.eof()) {
      v.push_back(n);
      F >> n;
   }
  
   for (int i = v.size() - 1; i >= 0; i--) {
      cout << v[i] << ' ';
   }
   cout << endl;
}
