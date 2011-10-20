
#include <iostream>
using namespace std;

int main() { 
  int codi, soroll, track;
  int sumasoroll;
  bool trobat;
  
  cin >> codi;
  while (codi != -99) {
    ult_bona = -1;
    sumasoroll = 0;
    track = 1;
    trobat = false;

    cin >> soroll;
    while (soroll != -99 && !trobat) {
      sumasoroll = sumasoroll + soroll;
      if (sumasoroll > 10) trobat = true;
      else {
	cin >> soroll;
      }
    }
    
    if (trobat) {
      cout << "El CD amb codi " << codi 
	   << " té un soroll del " << sumasoroll
	   << "% en les " << track << " primeres pistes" 
	   << endl;

      // Llegim les mostres de soroll que queden
      while (soroll != -99) {
	cin >> soroll;
      }
    }

    cin >> codi;
  }
}
