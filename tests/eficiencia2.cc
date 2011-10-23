
#include <iostream>
#include <ctime>
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

int main()
{
  Cronometre C;
  long a;
  
  C.comensa();
  a = 0;
  for (int i = 0; i < 20000; i++) {
    for (int j = 0; j < 20000; j++) {
      a = a + (i - j);
    }
  }
  C.acaba();

  cout << "Temps emprat: " << C.resultat() << endl;
}

// Local variables:
// compile-command: "gcc -o ef2 eficiencia2.cc -lstdc++"
// End:
