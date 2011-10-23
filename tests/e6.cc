
#include <iostream>
#include <vector>

struct Atleta { 
   string nom, cognom;
   double marca;
};

int main() {
   vector<Atleta> A;
   Atleta a;
   
   // Llegir les dades
   ifstream F;
   F.open("Atletes.txt");
   F >> a.nom >> a.cognom >> a.marca;
   while (!F.eof()) {
      A.push_back(a);
      F >> a.nom >> a.cognom >> a.marca;
   }
   F.close();

   // Calcula percentils
   for (int i = 0; i < A.size(); i++) {
      double marca = A[i].marca;
      int cont = 0;
      for (int j = 0; j < A.size(); j++) {
         if (marca >= A[i].marca) cont++;
      }
      cout << A[i].nom << ' ' << A[i].cognom << ' '
           << double(cont) / double(A.size()) << endl;
   }
}
