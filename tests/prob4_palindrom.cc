
#include <list>
#include <iostream>
using namespace std;

list<char> string2list(string s) {
  list<char> res;
  for (int i = 0; i < s.size(); i++) {
    res.push_back(s[i]);
  }
  return res;
}

// versió 1
bool palindrom_v1(const list<char>& L) {
  list<char>::const_iterator it = L.begin();
  list<char>::const_reverse_iterator rit = L.rbegin();
  const int N = L.size() / 2;
  for (int i = 0; i < N; i++) {
    if (*it != *rit) return false;
    it++;
    rit++;
  }
  return true;
}

// versió 2
bool palindrom_v2(const list<char>& L) {
  list<char> Lr = L;
  Lr.reverse();
  return Lr == L;
}

int main() {
  string proves[4] = { "ABBA", "oysyo", "abcde", "12xy" };
  for (int i = 0; i < 4; i++) {
    string s = proves[i];
    list<char> L = string2list(s);
    cout << palindrom_v1(L) << ' ' << palindrom_v2(L) << endl;
  }
}
