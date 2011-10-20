#include<iostream>
using namespace std;

int main(void)

{
    int n,i,num,tam=0,c=1,xif=1;
    
    cout << "introdueix un nomre POSITIU per veure les seves xifres en ordre" << endl << endl;
    cin >> n;
    cout << endl;               
    num = n;                /*guardo el numero llegit en la variable num per no perdre'l*/
   
    while(n > 9){           /*calculo el tamany del numero (nombre de xifres-1) i el guardo a la variable tam*/
       n=n/10;
       tam++;
    }
    
    for(i = 0 ; i < tam ; i++)      /*aconsegueixo la potència de 10 [10^(tam)] per a que el nombre pugui
                                    reduir-se a la primera xifra (dividint-lo)*/
       c=10*c;
      
    
    for(i = c*10 ; i > 1 ; i = i/10){        //Per aconseguir la xifra d' una possició n hem de dividir 
                                             //entre 10 el numero fins arribar a n i restar-li 10 
       xif =(num/c)-(num/i)*10;              //vegades el nomre que hi ha a la seva esquerra
       c = c/10;                             //p.ex: si volem el 3 de 84321 es 84321/100 - 84*10 = 3 (Només vàlid a programació!!)
       cout << xif << endl << endl;                                 
    }                         
    
    cout << endl;
    
    system("pause");
    
    return 0;
}
