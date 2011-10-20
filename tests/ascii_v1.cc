
#include <iostream>
using namespace std;

int main()
{
  int i,j,c;

   for (i = 0; i < 32; i++) 
     {
       for(j = 1; j < 4; j++) 
	 {
	   c = i + j * 32;
	   cout << c << " -- '" 
		<< char(c) << "'     ";
	 }
       cout << endl;
     }
}
