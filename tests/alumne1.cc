
// Laura Garcia Fernandez

#include<fstream>
#include<vector>
#include<iostream>
#include<iterator>
using namespace std;

string lletres_juntes( vector <char> & caracters){

    vector <char> ::iterator et = caracters.begin();
    string paraula;

    for (; et < caracters.end()-1 ; et++){

        paraula += *et;


    }

    return paraula;

}

vector <string> paraules_separades (string & frase){

    ofstream F;
    F.open("frases.txt");
    F << frase;
    F.close();

    ifstream G;
    G.open("frases.txt");
    string paraula;
    G >> paraula;
    vector <string> resultat;
    resultat.push_back(paraula);

    while(!G.eof()){

        G >> paraula;
        resultat.push_back(paraula);
    }

    return resultat;





}

vector <char> alterna (vector <char> serie, vector <char> serie2){

    vector <char> res;
    vector <char> ::iterator ut = serie.begin();
    vector <char> ::iterator at = serie2.begin();

    res.push_back(*ut) ;
    res.push_back(*at) ;

    while ( ut != serie.end() & at != serie2.end() ){

        at++;
        ut++;

        if ( ut == serie.end() and at != serie2.end() ){

            for(; at < serie2.end(); at++){

                res.push_back(*at);

            }
        }
        if ( ut != serie.end() and at == serie2.end() ){

            for( ut ; ut< serie.end() ; ut++){

                res.push_back(*ut);

            }
        }

        res.push_back(*ut) ;
        res.push_back(*at) ;
    }

    return res;


}

int main(){

    /////PRIMERA FUNCIÓ////////////////////////////////////

    string frase;
    cout << "introdueix una frase"<<endl;
    getline (cin , frase);

    vector < string > separacio = paraules_separades(frase);
    vector < string > ::iterator it = separacio.begin();

    cout << "[";

        for (; it < separacio.end(); it++){

            cout << "''" << *it << "'',";
        }

    cout << "]"<<endl<<endl;

    /////SEGONA FUNCIÓ//////////////////////////////////////

    vector <char> serie;
    vector <char> serie2;

    cout<<"Introdueix la primera serie, presiona 5 per acabar la serie"<<endl;
    char a;
    cin >> a;
    serie.push_back(a);

    while ( int (char(a) ) != 53){  //tenim que el enter 53 per codi ascii és igual que l'enter 5 per char

        cin >> a;
        serie.push_back(a);

    }

    cout << "Introdueix la segona serie, presiona 5 per acabar la serie" << endl;

    cin >> a;
    serie2.push_back(a);

    while ( int ( char(a) ) != 53){

        cin >> a;
        serie.push_back(a);

    }

    //L'únic que no he aconseguit és treure el 5 i dos espais més que m'agafen els vectors als omplirlos per teclat//

    vector <char> resultant = alterna(serie,serie2);
    vector <char> ::iterator ot = resultant.begin();

    cout << "[";
    for (; ot < resultant.end(); ot++){

            cout << "'" << *ot << "'";
        }
    cout << "]"<<endl<<endl;

    /////TERCERA FUNCIÓ//////////////////////////////////////

    vector <char> caracters;

    cout << "Introdueix la serie de caracters, per acabar d'escriure polsa 5 " << endl;
    char b;
    cin >> b;
    caracters.push_back(b);
    while( int ( char(b) ) != 53){

        cin >> b;
        caracters.push_back(b);
    }

    string nom = lletres_juntes(caracters);
    cout << " " << nom << endl;


}





