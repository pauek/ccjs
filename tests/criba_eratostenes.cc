
#include <iostream>
#include <vector>
using namespace std;

void marca_multiples(int n, vector<bool>& primers) {
  const int max = primers.size() / n;
  for (int i = 2; i <= max; i++) {
    primers[i*n] = false;
  }
}

int main() {
  int N, k;
  cin >> N;
  vector<bool> primers(N, true);
  for (k = 2; k < N; k++) {
    marca_multiples(k, primers);
  } 
  for (k = 2; k < primers.size(); k++) {
    if (primers[k]) cout << k << ' ';
  }
  cout << endl;
}
