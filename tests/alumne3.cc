#include<iostream>
using namespace std;

#include"Vector2D.h"

Vector2D::Vector2D(double x, double y) {
	_x = x;
	_y = y;
	}
Vector2D::get_x() const { return _x; }
Vector2D::get_y() const { return _y; }


Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
double x = v1.get_x() + v2.get_x();
double y = v1.get_y() + v2.get_y();
Vector2D res(x, y);
return res;
}

istream &operator>>(istream &is, Vector2D &obj){
 is >> obj.x;
 is >> obj.y;
 return is;
}

ostream &operator<<(ostream &os, const Vector2D &obj){
	  os <<obj.v1;
 return os;
}

