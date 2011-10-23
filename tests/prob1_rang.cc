
#include <iostream>
#include <list>
using namespace std;

list<int> rang(int inici, int fi, int salt) {
  list<int> res;
  for (int i = inici; i < fi; i += salt) {
    res.push_back(i);
  }
  return res;
}

int main() {
  list<int> L = rang(5, 16, 3);
  list<int>::iterator it = L.begin();
  for (; it != L.end(); it++) {
    cout << *it << ' ';
  }
}
