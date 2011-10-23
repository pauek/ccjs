
#include <iostream>
#include <list>
using namespace std;

void resta_conjunts(list<int>& A, const list<int>& B) {
  list<int>::const_iterator Bit = B.begin();
  for (; Bit != B.end(); Bit++) {
    list<int>::iterator it = A.begin();
    while (it != A.end()) {
      if (*it == *Bit) {
        it = A.erase(it);
      } else {
        it++;
      }
    }
  }
}

int main() {
  int C1[13] = { 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 8, 9, 10 };
  int C2[4]  = { 5, 3, 9, 8 };
  list<int> A, B;
  for (int i = 0; i < 13; i++) A.push_back(C1[i]);
  for (int i = 0; i < 4; i++)  B.push_back(C2[i]);

  resta_conjunts(A, B);
  list<int>::iterator it = A.begin();
  for (; it != A.end(); it++) {
    cout << *it << ' ';
  }
}
