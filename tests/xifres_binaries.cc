
#include <iostream>
using namespace std;

int pow2(int n)
{
    int k = 1, pot = 1;
    for (k = 0; k < n; k++) 
       pot *= 2;
       
    return pot;
}

int num_xifres_bin(int i)
{
   int x = 0;
   while ( i != 0 )
   { 
      x++;
      i/=2;
   }
   return x;   
}


int main()
{
    int i, n, X;
    
    cin >> n;
    X = num_xifres_bin(n);
    for ( i = X-1; i >= 0; i-- ) 
    {
        cout << ((n / pow2(i)) % 2);
    }
    cout << endl;
}
