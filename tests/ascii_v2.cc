
#include <iostream>
using namespace std;

int main()
{
  int i,j,c;

   for (i = 32; i < 64; i++) 
     {
       cout << i    << " -- '" << char(i   ) << "'     "
	    << i+32 << " -- '" << char(i+32) << "'     "
	    << i+64 << " -- '" << char(i+64) << "'     "
	    << endl;
     }
}
