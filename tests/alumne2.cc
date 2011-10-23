
//Xavier Tauleria Sierra DNI-53033754-D
//Bernat Perez Costa DNI-77747533-N


#include <iostream>
#include <string>
using namespace std;


const int caselles_codi=6;

const int caselles_procedencia=15;

const int caselles_hora=2;

const int files=10;

const int columnes=26;



typedef int tVector_codi[caselles_codi];

typedef int tVector_procedencia[caselles_procedencia];

typedef int tVector_hora[caselles_hora];



typedef int tMatriu_enters[files][columnes];



typedef int tMatriu_long[files][2];



int caracter_a_enter(char caracter);

int refresc_casella(char caracter, int caracter_ant);

char enter_a_caracter(int enter);



int main (){
    
    string codi, procedencia, hora, minut;
    
    int estat, enter_estat_ant, posicions_estat, fil, col, i, j, col_canviestat, fil_canviestat, cont_iguals;
    
    char a, canviestat;
    
    bool trobat;
    
    tVector_codi enters_codi_ant, posicions_codi, codi_a_buscar;
    
    tVector_procedencia enters_procedencia_ant, posicions_procedencia;
    
    tVector_hora enters_hora_ant, posicions_hora;
    
    tVector_hora enters_minut_ant, posicions_minut;
    
    tMatriu_enters mat_enters;
    
    tMatriu_long mat_long;
    

    
    cin >> canviestat;

    
        
    fil=0;
    
    while (fil<files && canviestat!='.'){            
        
          if (canviestat=='e'){
           
              cin >> codi >> estat;
              
              for (i=0;i<codi.size();i++){
                   
                   codi_a_buscar[i]=caracter_a_enter(codi[i]); }
                   
              
              trobat=false;
              
              cont_iguals=0;
              
              for (i=0;i<=fil && !trobat;i++){
                  
                  for (j=0;j<codi.size();j++){
                      
                      if (codi_a_buscar[j]==mat_enters[i][j]) {
                                                              
                             cont_iguals++;}}
                             
                  if (cont_iguals==codi.size()){
                  
                      trobat=true;
                      
                      fil_canviestat=i;}
                  
                  else {cont_iguals=0;}
              }
              
              if (trobat){
              
                  posicions_estat=0;
               
                  while(estat!=mat_enters[fil_canviestat][25]){
                      
                      mat_enters[fil_canviestat][25]++;
                      
                      while (mat_enters[fil_canviestat][25]>4){
                      
                            mat_enters[fil_canviestat][25]=mat_enters[fil_canviestat][25]-5;
                      }
                      
                      posicions_estat++;
               
                  }                           
                                          
                 cout << fil_canviestat << " " << col << " " << posicions_estat << " ";
               }       
                      
                                 
        }
        
        else {
             
             cin >> codi >> procedencia >> hora >> minut >> estat;

     
        
        col=0;
        
        for(i=0;i<codi.size();i++){
              
              a=codi[i];
              
              enters_codi_ant[i]=caracter_a_enter(a);
              
              posicions_codi[i]=enters_codi_ant[i];
              
              cout << fil << " " << col << " " << posicions_codi[i] << " " ;
              
              mat_enters[fil][col]=posicions_codi[i];
              
              col++;
        }
        
        if (codi.size() < caselles_codi){
                           
              col=codi.size();
              
              for (i=codi.size();i<caselles_codi;i++){
                   
                   posicions_codi[i]=0;
                   
                   enters_codi_ant[i]=0;
                   
                   cout << fil << " " << col << " " << posicions_codi[i] << " " ;
                   
                   mat_enters[fil][col]=posicions_codi[i];
                   
                   col++;          
              }
        }
    
        mat_long[fil][0]=codi.size();
        
    /* Aqui representem la primera procedència de vol, de la mateixa manera que
    el codi de vol */  
        
        col=6;
        
        for(i=0;i<procedencia.size();i++){
              
              a=procedencia[i];
              
              enters_procedencia_ant[i]=caracter_a_enter(a);
              
              posicions_procedencia[i]=enters_procedencia_ant[i];
              
              cout << fil << " " << col << " " << posicions_procedencia[i] << " " ;
              
              mat_enters[fil][col]=posicions_procedencia[i];
              
              col++;
        }
              
        if (procedencia.size()<caselles_procedencia){
                           
              col=procedencia.size()+caselles_codi;
              
              for (i=procedencia.size();i<caselles_procedencia;i++){
                   
                   posicions_procedencia[i]=0;
                   
                   enters_procedencia_ant[i]=0;
                   
                   cout << fil << " " << col << " " << posicions_procedencia[i] << " " ;
                   
                   mat_enters[fil][col]=posicions_procedencia[i];
                   
                   col++;          
              }
        }
        
        mat_long[fil][1]=procedencia.size();
    
    /* Aqui representem la primera hora de vol, de la mateixa manera que el codi 
    de vol */  
        
        col=21;
        
        for(i=0;i<hora.size();i++){
              
              a=hora[i];
              
              enters_hora_ant[i]=caracter_a_enter(a);
              
              posicions_hora[i]=enters_hora_ant[i];
              
              cout << fil << " " << col << " " << posicions_hora[i] << " " ;
              
              mat_enters[fil][col]=posicions_hora[i];
              
              col++;
        }
    
    /* Aqui representem el primer minut de vol, de la mateixa manera que el codi 
    de vol */  
        
        col=23;
        
        for(i=0;i<minut.size();i++){
              
              a=minut[i];
              
              enters_minut_ant[i]=caracter_a_enter(a);
              
              posicions_minut[i]=enters_minut_ant[i];
              
              cout << fil << " " << col << " " << posicions_minut[i] << " " ;
              
              mat_enters[fil][col]=posicions_minut[i];
              
              col++;
        }  
        
    /* Aqui representem el primer estat de vol, de la mateixa manera que el codi 
    de vol */  
        
        col=25;
        
        enter_estat_ant=estat;
         
        cout << fil << " " << col << " " << estat << " ";
        
        mat_enters[fil][col]=estat;
        
    /* Llegim els elements del següent vol */  
     
                
     fil++;
     
     }
     
         
     cin >> canviestat; 
      
     }
     
     
      cout << endl;
            
 /* Iniciem el bucle per llegir la resta de vols, posant en la condició del
    while tots els centinelles */

    while (canviestat!='.') {
           
/* Amb aquest bucle que ve a continuació traspassem el vol d'una fila a la
fila anterior, de manera que desapareix el vol de la fila més superior.  En cas
que trobem un vol que només cal canviar l'estat, fem el mateix que abans i
canviem l'estat del vol corresponent.  En cas que el vol sigui nou, situem
tots els vols a una fila superior i a la ultima fila hi situem el nou vol*/

            if (canviestat=='e'){
           
              cin >> codi >> estat;
              
              for (i=0;i<codi.size();i++){
                   
                   codi_a_buscar[i]=caracter_a_enter(codi[i]); }
                   
              
              trobat=false;
              
              cont_iguals=0;
              
              for (i=0;i<=fil && !trobat;i++){
                  
                  for (j=0;j<codi.size();j++){
                      
                      if (codi_a_buscar[j]==mat_enters[i][j]) {
                                                              
                             cont_iguals++;}
                  }            
                             
                  if(cont_iguals==codi.size()){
                  
                        trobat=true;
                  
                        fil_canviestat=i;}
                        
                  else {cont_iguals=0;}
              }
                  
              
              if (trobat){
              
                  posicions_estat=0;
               
                  while(estat!=mat_enters[fil_canviestat][25]){
                      
                      mat_enters[fil_canviestat][25]++;
                      
                      while (mat_enters[fil_canviestat][25]>4){
                      
                            mat_enters[fil_canviestat][25]=mat_enters[fil_canviestat][25]-5;
                      }
                      
                      posicions_estat++;
               
                  }                           
                                          
                 cout << fil_canviestat << " " << col << " " << posicions_estat << " ";
               }       
                      
                                 
        }
        
        else {
             
           cin >> codi >> procedencia >> hora >> minut >> estat;
           
           for(fil=0;fil<files-1;fil++){
           
           /* Refresquem el codi del vol en funció del codi anterior que hi havia al
           panell */
               
               col=0;
               
               for (i=0; i<mat_long[fil+1][0]; i++){
                   
                   posicions_codi[i]=refresc_casella(enter_a_caracter(mat_enters[fil+1][col]),mat_enters[fil][col]);
                   
                   mat_enters[fil][col]=mat_enters[fil][col]+posicions_codi[i];
                   
                   while (mat_enters[fil][col]>37){
                         
                         mat_enters[fil][col]=mat_enters[fil][col]-38;
                   }
                   
                   cout << fil << " " << col << " " << posicions_codi[i] << " " ;
                   
                   col++;
               }
               
               if (mat_long[fil+1][0]<caselles_codi){
    
                   col=mat_long[fil+1][0];
                   
                   for (i=mat_long[fil+1][0];i<caselles_codi;i++){
                       
                       posicions_codi[i]=38-mat_enters[fil][col];
                       
                       mat_enters[fil][col]=mat_enters[fil][col]+posicions_codi[i];
                       
                             while (mat_enters[fil][col]>37){
                                   
                                   mat_enters[fil][col]=mat_enters[fil][col]-38;
                             }
                             
                       cout << fil << " " << col << " " << posicions_codi[i] << " " ;
                   
                       col++;
                   
                   }
               }
               
               mat_long[fil][0]=mat_long[fil+1][0];
               
    /* Refresquem el la procedencia del vol en funció de la procedència anterior
    que hi havia al panell */
    
               col=6;
               
               for (i=0; i<mat_long[fil+1][1]; i++){
                   
                   posicions_procedencia[i]=
                   refresc_casella(enter_a_caracter(mat_enters[fil+1][col]),mat_enters[fil][col]);
                   
                   mat_enters[fil][col]=mat_enters[fil][col]+posicions_procedencia[i];
                   
                   while (mat_enters[fil][col]>37){
                         
                         mat_enters[fil][col]=mat_enters[fil][col]-38;
                   }
                   
                   cout << fil << " " << col << " " << posicions_procedencia[i] 
                   << " " ;
                   
                   col++;
               }
                  
               if (mat_long[fil+1][1]<caselles_procedencia){
    
                   col=mat_long[fil+1][1]+caselles_codi;
                   
                   for (i=mat_long[fil+1][1];i<caselles_procedencia;i++){
                       
                       posicions_procedencia[i]=38-mat_enters[fil][col];
                       
                       mat_enters[fil][col]=mat_enters[fil][col]+posicions_procedencia[i];
                       
                             while (mat_enters[fil][col]>37){
                                   
                                   mat_enters[fil][col]=mat_enters[fil][col]-38;
                             }
                             
                       cout << fil << " " << col << " " << posicions_procedencia[i] 
                       << " " ;
                   
                       col++;
                   }
               }    
    
               mat_long[fil][1]=mat_long[fil+1][1];
    
    /* Refresquem l'hora del vol en funció de l'hora anterior que hi havia al
    panell */
    
               col=21;
               
               for (i=0; i<2; i++){
                   
                   posicions_hora[i]=refresc_casella(enter_a_caracter(mat_enters[fil+1][col]),mat_enters[fil][col]);
                   
                   mat_enters[fil][col]=mat_enters[fil][col]+posicions_hora[i];
                   
                   while (mat_enters[fil][col]>37){
                         
                         mat_enters[fil][col]=mat_enters[fil][col]-38;
                   }
                   
                   cout << fil << " " << col << " " << posicions_hora[i] << " " ;
                   
                   col++;
               }
    
    /* Refresquem el minut del vol en funció del minut anterior que hi havia al
    panell */
    
               col=23;
               
               for (i=0; i<2; i++){
                   
                   posicions_minut[i]=refresc_casella(enter_a_caracter(mat_enters[fil+1][col]),mat_enters[fil][col]);
                   
                   mat_enters[fil][col]=mat_enters[fil][col]+posicions_minut[i];
                   
                   while (mat_enters[fil][col]>37){
                         
                         mat_enters[fil][col]=mat_enters[fil][col]-38;
                   }
                   
                   cout << fil << " " << col << " " << posicions_minut[i] << " " ;
                   
                   col++;
               }
        
    /* Refresquem el l'estat del vol en funció de l'estat anterior que hi havia al
    panell */
    
               col=25;
               
               posicions_estat=0;
               
               while(mat_enters[fil+1][col]!=mat_enters[fil][col]){
                      
                      mat_enters[fil][col]++;
                      
                      while (mat_enters[fil][col]>4){
                      
                            mat_enters[fil][col]=mat_enters[fil][col]-5;
                      }
                      
               posicions_estat++;
               
               }                           
                                          
               cout << fil << " " << col << " " << posicions_estat << " " ;
                              
               mat_enters[fil][col]=mat_enters[fil+1][col];        
        
        }
           
       
       /* A partir d'aquí, representem el nou vol a la fila 10 */               
           
           
           col=0;
           
           for (i=0; i<codi.size(); i++){
               
               posicions_codi[i]=refresc_casella(codi[i],mat_enters[fil][col]);
               
               mat_enters[fil][col]=mat_enters[fil][col]+posicions_codi[i];
               
               while (mat_enters[fil][col]>37){
                     
                     mat_enters[fil][col]=mat_enters[fil][col]-38;
               }
               
               cout << fil << " " << col << " " << posicions_codi[i] << " " ;
               
               col++;
           }
           
           if (codi.size()<caselles_codi){

               col=codi.size();
               
               for (i=codi.size();i<caselles_codi;i++){
                   
                   posicions_codi[i]=38-mat_enters[fil][col];
                   
                   mat_enters[fil][col]=mat_enters[fil][col]+posicions_codi[i];
                   
                         while (mat_enters[fil][col]>37){
                               
                               mat_enters[fil][col]=mat_enters[fil][col]-38;
                         }
                         
                   cout << fil << " " << col << " " << posicions_codi[i] << " " ;
               
                   col++;
               
               }
           }
           
           mat_long[fil][0]=codi.size();
           
/* Refresquem el la procedencia del vol en funció de la procedència anterior
que hi havia al panell */

           col=6;
           
           for (i=0; i<procedencia.size(); i++){
               
               posicions_procedencia[i]=
               refresc_casella(procedencia[i],mat_enters[fil][col]);
               
               mat_enters[fil][col]=
               mat_enters[fil][col]+posicions_procedencia[i];
               
               while (mat_enters[fil][col]>37){
                     
                     mat_enters[fil][col]=mat_enters[fil][col]-38;
               }
               
               cout << fil << " " << col << " " << posicions_procedencia[i] 
               << " " ;
               
               col++;
           }
              
           if (procedencia.size()<caselles_procedencia){

               col=procedencia.size()+caselles_codi;
               
               for (i=procedencia.size();i<caselles_procedencia;i++){
                   
                   posicions_procedencia[i]=38-mat_enters[fil][col];
                   
                   mat_enters[fil][col]=mat_enters[fil][col]+
                   posicions_procedencia[i];
                   
                         while (mat_enters[fil][col]>37){
                               
                               mat_enters[fil][col]=mat_enters[fil][col]-38;
                         }
                         
                   cout << fil << " " << col << " " << posicions_procedencia[i] 
                   << " " ;
               
                   col++;
               }
           }    

           mat_long[fil][1]=procedencia.size();
           
/* Refresquem l'hora del vol en funció de l'hora anterior que hi havia al
panell */

           col=21;
           
           for (i=0; i<hora.size(); i++){
               
               posicions_hora[i]=refresc_casella(hora[i],mat_enters[fil][col]);
               
               mat_enters[fil][col]=mat_enters[fil][col]+posicions_hora[i];
               
               while (mat_enters[fil][col]>37){
                     
                     mat_enters[fil][col]=mat_enters[fil][col]-38;
               }
               
               cout << fil << " " << col << " " << posicions_hora[i] << " " ;
               
               col++;
           }

/* Refresquem el minut del vol en funció del minut anterior que hi havia al
panell */

           col=23;
           
           for (i=0; i<minut.size(); i++){
               
               posicions_minut[i]=refresc_casella(minut[i],mat_enters[fil][col]);
               
               mat_enters[fil][col]=mat_enters[fil][col]+posicions_minut[i];
               
               while (mat_enters[fil][col]>37){
                     
                     mat_enters[fil][col]=mat_enters[fil][col]-38;
               }
               
               cout << fil << " " << col << " " << posicions_minut[i] << " " ;
               
               col++;
           }
    
/* Refresquem el l'estat del vol en funció de l'estat anterior que hi havia al
panell */

           col=25;
           
           posicions_estat=0;
               
               while(estat!=mat_enters[fil][col]){
                      
                      mat_enters[fil][col]++;
                      
                      while (mat_enters[fil][col]>4){
                      
                            mat_enters[fil][col]=mat_enters[fil][col]-5;
                      }
                      
               posicions_estat++;
               
               }                           
                                          
               cout << fil << " " << col << " " << posicions_estat << " ";
                              
               mat_enters[fil][col]=estat;
    
    }
    
    cout << endl;
    
    cin >> canviestat;
    
    }           
     
    system("pause");
    
}
    
    


/* Aquesta funció transforma un caràcter a enter.  A partir de qualsevol 
caràcter entrat, la funció retorna l'enter associat segons les plaques
del panell. */

int caracter_a_enter(char caracter){
    
    int enter;
    
    enter=int(caracter);
    
    if(enter>=48 && enter<=57){   /*En cas que sigui número*/
          
          enter=enter-20;
    }     
    else if (enter==45){    /*En cas que sigui el guió*/
          
          enter=1;
    }      
    else {     /*En cas que sigui una lletra*/
          
          enter=enter-63;
    }
    
    return enter;
}




char enter_a_caracter(int enter){
     
     char caracter;
     
     if(enter>=28 && enter<=37){
                  
           enter=enter+20;
     }
     
     else if (enter==1){
          enter=45;
     }
     else if (enter>=2 && enter<=27){
          enter=enter+63;}             
     
     caracter=char(enter);
     
     return caracter;
     
}


/* Aquesta funció refresca una casella del panell en funció del caràcter que hi
havia a la casella i en nou caracter entrant. El nou caracter entrant es 
la variable caracter i el transformem a l'enter associat mitjançant la funció
enter_a_caracter.  El caracter anterior ja està representat amb l'enter
associat i, per tant, la funció ens retorna la quantitat de posicions que ha
d'avançar la casella del panell */ 

int refresc_casella(char caracter, int caracter_ant){
    
    int enter, posicions;
    
    enter=caracter_a_enter(caracter);  /*Transformem el caracter a l'enter */
    
    posicions=0;
    
    while (enter!=caracter_ant){   /* Comptem el número de posicions */    
          
          caracter_ant++;
          
          posicions++;
          
          if(caracter_ant>37){
                   
                   caracter_ant=0;
          }
    }
    
    return posicions;
}       
