
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

void llegeix_taula(map<char, string>& dict) {
  ifstream F("morse.csv");
  string linia;
  getline(F, linia);
  while (!F.eof()) {
    char C = linia[0];
    string morse = linia.substr(2);
    dict[C] = morse;
    if (C >= 'A' && C <= 'Z') {
      char c = char(int(C) + 32);
      dict[c] = morse;
    }
    getline(F, linia);
  }
}

int main() {
  map<char, string> dict;
  llegeix_taula(dict);
  
  ifstream F("missatge.txt");
  string linia;
  getline(F, linia);
  while (!F.eof()) {
    string::iterator it = linia.begin();
    for (; it != linia.end(); it++) {
      map<char, string>::iterator dit = dict.find(*it);
      if (dit != dict.end()) {
        cout << dit->second << ' ';
      }
    }
    getline(F, linia);
  }
}
