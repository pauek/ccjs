
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Traduccio {
   string cat, eng;
};

int cerca_paraula(string p, const vector<Traduccio>& D) {
   for (int i = 0; i < D.size(); i++) {
      if (D[i].cat == p) return i;
   }
   return -1;
}

int main() {
   vector<Traduccio> D; // el diccionari
   
   // Llegim diccionari
   ifstream F;
   F.open("diccionari.txt");
   Traduccio t;
   F >> t.cat >> t.eng;
   while (!F.eof()) {
      D.push_back(t);
      F >> t.cat >> t.eng;
   }
   F.close();

   string paraula;
   cin >> paraula;
   while (paraula != ".") {
      int pos = cerca_paraula(paraula, D);
      if (pos != -1) {
	 cout << D[pos].eng;
      } else {
	 cout << paraula;
      }
      cout << ' ';
      cin >> paraula;
   }
   cout << endl;
}
