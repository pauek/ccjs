// Titol: "Dins Esfera" [CERCA]
// Problema: Dir si dos punts seguits en una seq. de punts
//           3D estan dins de l'esfera unitat.
// Sequència: *Tripletes* de reals. Sentinella: (0.0, 0.0, 0.0)

// Exemple:
// - entrada: 1.0 1.0 1.0  -1.9 5.9 8.0  2.0 1.0 2.0  0.0 0.0 0.0
// - sortida: NO hi ha 2 punts seguits a dins l'esfera

// Tècniques:
// - Llegir 3 valors per a cada element de la seq.
// - Apuntar en un Booleà si l'últim punt estava dins
//   (en comptes d'apuntar-se l'últim punt sencer)

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  float x, y, z, dist = 0.0;
  bool trobat = false, udins = false;

  cin >> x >> y >> z;
  
  while ((x != 0.0 || y != 0.0 || z != 0.0) && 
	 !trobat)
    {
      dist = sqrt(x * x + y * y + z * z);
      if (dist < 1.0 && udins) trobat = true;
      else 
	{
	  udins = dist < 1.0;
	  cin >> x >> y >> z;
	}
    }

  if (trobat)
    cout << "Hi ha"; 
  else
    cout << "NO hi ha"; 

  cout << " 2 punts seguits a dins l'esfera" << endl;
}
