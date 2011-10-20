
#include <iostream>
using namespace std;

int main() { 
  int codi, soroll, track;
  int sumasoroll;
  int ult_bona, ult_soroll;
  bool cd_malament;
  
  cin >> codi;
  while (codi != -99) {
    ult_bona = -1;
    sumasoroll = 0;
    track = 1;
    cd_malament = false;

    cin >> soroll;
    while (soroll != -99) {
      sumasoroll = sumasoroll + soroll;
      if (sumasoroll > 10 && !cd_malament) {
	ult_bona = track;
	ult_soroll = sumasoroll; 
	cd_malament = true;
      }
      cin >> soroll;
    }

    if (cd_malament) {
      cout << "El CD amb codi " << codi 
	   << " té un soroll del " << ult_soroll 
	   << "% en les " << ult_bona << " primeres pistes" 
	   << endl;
    }
    
    cin >> codi;
  }
}
