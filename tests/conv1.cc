
#include <iostream>
using namespace std;

int main() {
  int x;
  cin >> x;
  cout << char(int('a') + x) << endl;
  cout << int(char(97) + x) << endl;
}
