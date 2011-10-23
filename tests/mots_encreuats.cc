
#include <iostream>
#include <vector>
using namespace std;

void enumera(int& k, string p) {
  cout << k << ". ";
  for (int i = 0; i < p.size(); i++) {
    if (p[i] == '*') {
      k++;
      cout << endl << k << ". ";
    } else {
      cout << p[i];
    }
  }
  cout << endl;
  k++;
}

void enumera(const vector<string>& V) {
  int k = 1;
  vector<string>::const_iterator p;
  for (p = V.begin(); p != V.end(); p++) {
    enumera(k, *p);
  }
}

int main() {
  int a, b, i, j;
  char c;
  cin >> a >> b;
  vector<string> H(b), V(a);
  for (i = 0; i < b; i++) {
    for (j = 0; j < a; j++) {
      cin >> c;
      H[i] += c;
      V[j] += c;
    }
  }
  int cont = 1;
  cout << "Horitzontals: " << endl;
  enumera(H);
  cout << endl;
  cout << "Verticals: " << endl;
  enumera(V);
  cout << endl;
}
