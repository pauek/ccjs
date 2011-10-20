
#include <iostream>
using namespace std;

int main() {
  int a;
  cin >> a;
  if (a < 0) {
	 cout << "-" << endl;
  } else if (a > 0) {
	 cout << "+" << endl;
  } else {
	 cout << "0" << endl;
  }
}
