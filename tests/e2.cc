
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Temperatura {
   double T;
   string pob;
};

int main() {
   Temperatura temp;
   vector<Temperatura> v;

   // Llegir dades
   ifstream F;
   F.open("temperatures.txt");
   F >> temp.T;
   getline(F, temp.pob);
   while (!F.eof()) {
      v.push_back(temp);
      F >> temp.T;
      getline(F, temp.pob);
   }
   F.close();

   // Processar dades
   int imin = 0;
   for (int i = 1; i < v.size(); i++) {
      if (v[i].T < v[imin].T) {
         imin = i;
      }
   }
   cout << v[imin].pob.substr(1) << endl;
}

