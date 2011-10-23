/*

  Dado un número N, encontrar las subsecuencias (de longitud mínimo 3)
  más largas en el genoma de E. coli que salgan repetidas almenos N veces.

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
  void comensa();
  void acaba();
  float resultat() const;
};

void Cronometre::comensa() { t1 = clock(); }
void Cronometre::acaba()   { t2 = clock(); }

float Cronometre::resultat() const {
  return float(t2 - t1) / float(CLOCKS_PER_SEC) ;
}

void mostra_posicions(const string& ecoli, string subseq) {
  list<int> posicions;
  int pos = ecoli.find(subseq, 0);
  while (pos != -1) {
	 posicions.push_back(pos);
	 pos = ecoli.find(subseq, pos + 1);
  }
  cout << "'" << subseq << "' [" << posicions.size() << "]:";
  list<int>::const_iterator i = posicions.begin();
  for (; i != posicions.end(); i++) cout << ' ' << *i;
  cout << endl;
}

// Busca las subsecuencias de longitud 'tam' que salen repetidas el
// máximo número de veces. Retorna el número de repeticiones.
//
int busca_subseqs(const string& ecoli, int tam, vector<string>& subseqs) {
  int max = 0;
  map<string, int> llocs;
  for (int i = 0; i < ecoli.size() - tam + 1; i++) {
    string sub = ecoli.substr(i, tam);
	 int& N = llocs[sub];
    N++;
    if (N > max) {
      subseqs.clear();
      max = N;
      subseqs.push_back(sub);
    } else if (N == max) {
      subseqs.push_back(sub);
    }
  }
  return max;
}

int main(int argc, char *argv[]) {
  Cronometre C;
  if (argc < 2) {
    cout << "usage: subrep <data.txt>" << endl;
    return 1;
  }

  // Leemos el genoma de E. coli
  string ecoli;
  {
    char base;
    ifstream F(argv[1]);
    while (F >> base) ecoli += base;
  }

  // Pedimos el número de repeticiones
  int repmin;
  cout << "Número de repeticions? ";
  cin >> repmin;
  cout << repmin << endl;

  C.comensa();

  int tam = 1, r = 0, rep = 0;
  vector<string> subs, usubs;
  r = busca_subseqs(ecoli, tam * 2, subs);
  // Ajustamos multiplicando por 2
  while (r >= repmin) {
    rep = r;
    usubs = subs;
    cerr << tam * 2 << ' ' << r << ' ' << subs.size() << endl;
    tam *= 2;
    r = busca_subseqs(ecoli, tam * 2, subs);
  }
  // Ajustamos sumando 1
  r = busca_subseqs(ecoli, tam + 1, subs);
  while (r >= repmin) {
    rep = r;
    usubs = subs;
    cerr << tam + 1 << ' ' << r << ' ' << subs.size() << endl;
    tam++;
    r = busca_subseqs(ecoli, tam + 1, subs);
  }

  C.acaba();
  
  if (rep >= repmin) {
    for (int i = 0; i < usubs.size(); i++) {
		mostra_posicions(ecoli, usubs[i]);
    }
  } else {
    cout << "No hi ha cap subseqüència que es repeteixi " << repmin << " cops" << endl;
  }
  cout << "Temps emprat: " << C.resultat() << " segons" << endl;
}
