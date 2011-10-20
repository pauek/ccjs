// Titol: "Longitud polilinia" [RECORREGUT]
// Problema: Calcular la longitud d'una línia contínua
//           feta de molts segments rectes (una polilínia)
// Sequència: *Parelles* de reals. Sentinella: la primera parella
//            (la polilínia acaba on ha començat)

// Exemple:
// - entrada: 1.0 0.0  0.9 0.9  0.0 1.0  0.0 0.0  1.0 0.0
// - sortida: Longitud: 3.81108

// Tècniques:
// - Llegir 2 valors per a cada element de la seq.
// - Guardar l'últim element (per a la distància)
// - Acumulador per a la suma.

#include <iostream>
#include <cmath> // per a sqrt
using namespace std;

int main()
{
  float x, y, ux, uy, x0, y0;
  float L = 0.0;

  cin >> ux >> uy; // Llegim primer
  x0 = ux; y0 = uy; // Punt inicial

  cin >> x >> y; // Suposem + d'1 element
  while (!(x == x0 && y == y0))
  {
    L = L + sqrt((x - ux) * (x - ux) +
		 (y - uy) * (y - uy));
    
    ux = x; uy = y;
    cin >> x >> y;
  }
  // Com que l'últim punt tanca la polilínea, hem
  // d'afegir aquest tros...
  L = L + sqrt((x - ux) * (x - ux) +
	       (y - uy) * (y - uy));

  cout << "Longitud: " << L << endl;
}
