
#include<iostream>
using namespace std;

int sumaDivisors(int n)
{
  int d = 1, suma = 0;
  while (d < n)  
  {
    if (n % d == 0) suma += d;
    d++;
  }
  return suma;
}

int main()
{
  int i, amic_i, limit;
  cout << "Limit? ";
  cin >> limit;
  
  i = 1;
  while (i <= limit)
  {
    amic_i = sumaDivisors(i);
    
    if ( i == sumaDivisors(amic_i) && i < amic_i ) 
      cout << "els nombres "<< i <<" i "
	   << amic_i <<" son amics"<<endl;
    
    i++;
  }   
  
  system("pause");
}
