#include <iostream>
using namespace std;

#include "Vector2D.h"

Vector2D::Vector2D(){
                     _x = 0;
                     _y = 0;
                     }
Vector2D::Vector2D(float a, float b){
                     _x = a;
                     _y = b;
                     }




void Vector2D::set(float a, float b){
     _x = a;
     _y = b;
     }
void Vector2D::seta(float a){
     _x = a;
     }
void Vector2D::setb(float b){
     _y = b;
     }



void Vector2D::operator+=(const Vector2D& v) {
         float a = _x, b = _y, c = v._x, d = v._y;
         _x = a + c;
         _y = b + d;
         }
void Vector2D::operator*=(const Vector2D& v) {
     float a = _x, b = _y, c = v._x, d = v._y, real;
     _x = a * c;
     _y = b * d;
     real = _x + _y;
     }
     
Vector2D Vector2D::operator+(const Vector2D& v) {
         Vector2D suma(_x, _y);
         suma += v;
         return suma;
         }
Vector2D Vector2D::operator*(const Vector2D& v) {
         Vector2D suma(_x, _y);
         suma *= v;
         return suma;
         }
         
istream& operator>>(istream& i, Vector2D& r) {
  float a, b;
  char coma;
  i >> a >> coma >> b;
  v.set(a, b);
}

ostream& operator<<(ostream& o, const Vector2D& r) {
  o << v.a<< ',' << v.b();
}

       
         


int main (){
    Vector2D v(1.0, 0.0), w(0.0, 1.0);
    
    cout << "El producte escalar de " << v << " i " << w << " es " << v * w << endl;
    
    cout <<"Entra un vector (x,y): ";
    cin >> v;
    
    cout << "La suma de " << v << " i " << w << " es " << v + w << endl;
    
    system ("pause");
    return 0;
}
