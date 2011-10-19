
#include <iostream>
using namespace std;

void f() {
   cout << "f" << endl;
}

void g(int a) {
   cout << "g" << a << endl;
}

int main() {
   f();
   g(2);
}

