#include <iostream>
#include <map.h>
#include <fstream>
#include <string>

using namespace std;
string ordenar (const string & paraula){  
       string par=paraula;                
       int L=par.length();                
       int i=1,j;
       char aux;
       while (i<L){
             aux=par[i];
             j=i;
             while (j!=0&&aux<par[j-1]){
                  par[j]=par[j-1];
                  j--;
             }
             par[j]=aux;
             i++;
             }
       return par;
}  
bool continua(){                  
          string opcio;
          cin>>opcio;
          if (opcio=="s"||opcio=="S")
             return true;
          else if (opcio=="n"||opcio=="N")
               return false;
          else{
              cout<<"ERROR!!!"<<endl<<"(S/N)"<<endl;
              bool b = continua();
              return b;
              }
}         

int main () {
    
    string a;
    cout << "Escriu el nom del teu fitxer de lemari: ";
    cin >>a;
    ifstream i(a.c_str() );
    multimap <string,string> lemari;
    string paraula,ordenada;
    while (!(i.eof()) ){
          i >> paraula;
          ordenada = ordenar(paraula);
          lemari.insert(make_pair(ordenada,paraula)); 
          }
    multimap <string, string >::iterator it;
    bool continuar = true;
    while(continuar){
          cout << "Escriu la paraula de la que vols saber els anagrames: ";
          cin >> paraula;
          ordenada=ordenar(paraula);
          if(lemari.find(ordenada)==lemari.end()||(lemari.find(ordenada)->second==paraula )&& (lemari.count(ordenada)==1))
               cout<<"No hi ha anagrames de "<<paraula<<endl;
          else{
               cout<<endl<<"Els anagrames de "<<paraula<<" son:"<<endl<<endl;
               for(it=lemari.lower_bound(ordenada);it!=lemari.upper_bound(ordenada);it++){
                    if (it->second!=paraula)                                       
                         cout<<(*it).second<<endl;
               }
          }
          cout<<endl<<"Buscar mes paraules? (S/N)"<<endl;
          continuar=continua();
          cout<<endl;
    }
    system ("pause");
    return 0;
}
