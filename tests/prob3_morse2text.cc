
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

void llegeix_taula(map<string, char>& dict) {
  ifstream F("morse.csv");
  string linia;
  getline(F, linia);
  while (!F.eof()) {
    char C = linia[0];
    string morse = linia.substr(2);
    dict[morse] = C;
    getline(F, linia);
  }
}

int main() {
  map<string, char> dict;
  llegeix_taula(dict);
  
  ifstream F("morse.txt");
  string paraula;
  F >> paraula;
  while (!F.eof()) {
    cout << dict[paraula];
    F >> paraula;
  }
}
