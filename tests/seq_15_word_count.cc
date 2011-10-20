
/* Ens demanen fer un programa per comptar els caracters, paraules i
 * línies d'un text. El text és una seqüència de caracters que pot
 * contenir espais i salts de línia (marcats amb el caracter ASCII
 * 10), i s'acaba quan es troben dos salts de línia seguits (una línia
 * buida). Es tracta de comptar: 
 *  
 *   - Els caracters que no siguin espais ni salts de línia.
 *   - Les paraules (tant al mig d'una línia com al final).
 *   - El número de línies (sense comptar la última).
 *
 * Suposant un text com:
 *
 *   asdf qwer zxcv
 *   a b c
 *
 * Un cop fet el comptatge, el programa ha de mostrar el resultat
 * exactament com:
 *  
 *   c: 15, p: 6, l: 2
 */

#include <iostream>
using namespace std;

const char eol = char(10); // End of Line (Linux?)

int main()
{
  int caracters = 0, paraules = 0, linies = 0;
  char c, uc = char(0);
  
  c = cin.get();
  while ( !(c == eol && uc == eol) )
  {
    if ( c != ' ' && c != eol ) {
      caracters++;
    }
    if ( (c == ' ' || c == eol) && uc != ' ' ) {
      paraules++;
    }
    if ( c == eol ) {
      linies++;
    }
    
    uc = c;
    c = cin.get();
  }

  cout << "c: " << caracters 
       << " p: " << paraules 
       << " l: " << linies << endl;
}
