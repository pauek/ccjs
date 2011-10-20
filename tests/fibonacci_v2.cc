
#include <iostream>
using namespace std;

int main() 
{
  int n, un;
  int aux, c = 0;
  
  un = 0;
  n = 1;
  
  while ( c < 30 ) 
  {
    cout << n << endl;
    
    aux = n + un;
    un = n;
    n = aux;
    
    c++;
  }
}
