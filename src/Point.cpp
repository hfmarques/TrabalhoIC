#include <iostream>
#include <cmath>
#include "Point.hpp"

using namespace std;
using namespace ctop;

bool Point::$READ_3D = false;
bool Point::$WRITE_3D = false;

Point::Point() : _x(0), _y(0), _z(0) {}
Point::Point(float x, float y, float z) : _x(x), _y(y), _z(z) {}
Point::Point(const Point& p) {
   (*this) = p;
}
Point::~Point() {}

float Point::distance(const Point& p) {
   return ( sqrt( pow(_x-p.x(),2) + pow(_y-p.y(),2) + pow(_z-p.z(),2) ) );
}

// Sobrecarga de Operadores Aritméticos
Point& Point::operator + (const Point& p) const {
   Point* pt = new Point(this->_x+p.x(), this->_y+p.y(), this->_z+p.z());
   return *pt;
}

Point& Point::operator - (const Point& p) const {
   Point* pt = new Point(this->_x-p.x(), this->_y-p.y(), this->_z-p.z());
   return *pt;
}

Point& Point::operator + () const {
   float x = (this->_x < 0) ? -this->_x : this->_x;
   float y = (this->_y < 0) ? -this->_y : this->_y;
   float z = (this->_z < 0) ? -this->_z : this->_z;
   return *(new Point(x, y, z));
}

Point& Point::operator - () const {
   Point* pt = new Point(-this->_x, -this->_y, -this->_z);
   return *pt;
}

// Sobrecarga de Operadores de Atribuição
Point& Point::operator = (const Point& p) {
   this->_x = p.x();
   this->_y = p.y();
   this->_z = p.z();
   return *this;
}

Point& Point::operator += (const Point& p) {
   this->_x += p.x();
   this->_y += p.y();
   this->_z += p.z();
   return (*this);
}

Point& Point::operator -= (const Point& p) {
   this->_x -= p.x();
   this->_y -= p.y();
   this->_z -= p.z();
   return (*this);
}

Point& Point::operator () (float x, float y, float z) {
   this->_x = x;
   this->_y = y;
   this->_z = z;
   return (*this);
}

Point& Point::operator () (float x, float y) {
   this->_x = x;
   this->_y = y;
   return (*this);
}

// Sobrecarga de Operadores Lógicos
bool Point::operator == (const Point& p) const {
   return (this->_x == p.x() && this->_y == p.y() && this->_z == p.z());
}

bool Point::operator != (const Point& p) const {
   return !((*this) == p);
}
