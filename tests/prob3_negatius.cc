
#include <list>
#include <iostream>
using namespace std;

void esborra_negatius(list<int>& L) {
  list<int>::iterator it = L.begin();
  while (it != L.end()) {
    if (*it < 0) {
      it = L.erase(it);
    } else {
      it++;
    }
  }
}

int main() {
  int nombres[10] = { -1, 3, 5, -2, 0, -6, 9, 10, -3, 2 };
  list<int> L;
  for (int i = 0; i < 10; i++) {
    L.push_back(nombres[i]);
  }
  esborra_negatius(L);
  list<int>::iterator it = L.begin();
  for (; it != L.end(); it++) {
    cout << *it << ' ';
  }
}
