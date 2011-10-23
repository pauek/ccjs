/*

  Dado un número N, encontrar las subsecuencias más largas en el
  genoma de E. coli que salgan repetidas almenos N veces.

*/

#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
using namespace std;

class Cronometre {
  clock_t t1, t2;
public:
  void comensa() { t1 = clock(); }
  void acaba()   { t2 = clock(); }
  float resultat() const {
	 return float(t2 - t1) / float(CLOCKS_PER_SEC) ;
  }
};

bool busca_subseqs(const string& ecoli, int tam, int rep, map<string, int>& subseqs, bool fast) {
  subseqs.clear();
  map<string, int> llocs;
  for (int i = 0; i < ecoli.size() - tam + 1; i++) {
    string sub = ecoli.substr(i, tam);
	 int& N = llocs[sub];
    if (++N >= rep) {
		if (fast) return true;
		subseqs[sub] = N;
    }
  }
  return !subseqs.empty();
}

bool tam_siguiente(bool trobat, int& tam, int& inf, int& sup) {
  if (!trobat) {
	 sup = tam;
	 tam = (sup + inf) / 2;
  } else if (sup == -1) {
	 inf = tam;
	 tam *= 2;
  } else {
	 inf = tam;
	 tam = (sup + inf) / 2;
  }
  return (sup == -1) || (sup - inf > 1);
}

int main(int argc, char *argv[]) {
  Cronometre C;
  if (argc < 2) {
    cout << "usage: subrep <data.txt>" << endl;
    return 1;
  }

  string ecoli;
  {
    char base;
    ifstream F(argv[1]);
    while (F >> base) ecoli += base;
  }

  int repmin;
  cout << "Número de repeticions? ";
  cin >> repmin;

  C.comensa();

  int tam = 2, tam_inf = 1, tam_sup = -1;
  bool found = false, continua = true;
  map<string, int> subs;
  while (continua) {
	 found = busca_subseqs(ecoli, tam, repmin, subs, true);
	 cout << '.' << flush;
    continua = tam_siguiente(found, tam, tam_inf, tam_sup);
  }
  cout << endl;

  found = busca_subseqs(ecoli, tam, repmin, subs, false);

  C.acaba();

  if (!found) {
    cout << "No hi ha cap subseqüència que es repeteixi " << repmin << " cops" << endl;
  } else {
	 map<string, int>::iterator i = subs.begin();
	 for (; i != subs.end(); i++) {
		cout << i->first << ' ' << i->second << endl;
	 }
	 cout << endl;
  }
  cout << "Temps emprat: " << C.resultat() << " segons" << endl;
}
