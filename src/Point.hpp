#ifndef _POINT_HPP_
#define _POINT_HPP_

namespace ctop {

/** \brief Implementa o objeto cartesiano Ponto (2D e 3D)
*	 \class Point Point.hpp "Point.hpp"
*/
class Point {
private:
   //coordenadas cartesianas
   float _x, _y, _z;

public:
   /** \param $READ_3D flag para definir se a leitura será das três coordenadas ou de duas
   *		Antes de realizar leitura pela istream deve-se setar o flag
   *			true para três coordenadas
   *			false para duas coordenadas (default)
   */
   static bool $READ_3D;

   /** \param $WRITE_3D flag para definir se a escrita será das três coordenadas ou de duas
   *		Antes de realizar escrita pela ostream deve-se setar o flag
   *			true para três coordenadas
   *			false para duas coordenadas (default)
   */
   static bool $WRITE_3D;

   Point();					// default
   Point(const Point&);	// copy
   Point(float x, float y, float z = 0);
   virtual ~Point();

   // Gets
   inline float x() const {
      return this->_x;
   }
   inline float y() const {
      return this->_y;
   }
   inline float z() const {
      return this->_z;
   }

   //! Retorna a distância entre os pontos
   float distance(const Point&);

   // Sobrecarga de Operadores Aritméticos
   Point& operator + (const Point& p) const;
   Point& operator - (const Point& p) const;
   Point& operator + () const;	// module 	p(-1, 3, -2) => +p = (1, 3, 2)
   Point& operator - () const;	// negation	p(-1, 3, -2) => -p = (1, -3, 2)

   // Sobrecarga de Operadores de Atribuição
   Point& operator = (const Point& p);
   Point& operator += (const Point& p);
   Point& operator -= (const Point& p);
   Point& operator () (float x, float y, float z); // Set
   Point& operator () (float x, float y);				// Set

   // Sobrecarga de Operadores Lógicos
   bool operator == (const Point& p) const;
   bool operator != (const Point& p) const;

   // Sobrecarga de Operadores IO
   friend std::ostream& operator << (std::ostream& out, const Point& p) {
      out << "(" << p._x << ", " << p._y;
      if($WRITE_3D)
         out << ", " << p._z;
      out << ")";
      return out;
   }

   friend std::istream& operator >> (std::istream& in, Point& p) {
      in >> p._x >> p._y;
      if($READ_3D)
         in >> p._z;
      return in;
   }
};

} // namespace ctop

#endif // _POINT_HPP_
