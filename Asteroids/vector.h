/***********************************************************************
 * Header File:
 *    Vector : A point and a direction
 * Author:
 *    Brandon Hartshorn
 * Summary:
 *    The vector class takes a point and gives it a velocity as well.
 * The velocity is stored using dy and dx components. It can then advance
 * itself. 
 ************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>
#include "point.h"

/************************************************************************
 * VECTOR
 * Extends the point class to add dx and dy!
 * This class SAVES THE DAY. It is so much easier to just inherit all
 * this wonderful work!
 ***********************************************************************/
class Vector: public Point
{
public:
   // constructors
   Vector() : Point(), dx(0.0), dy(0.0) {}
   Vector(Vector & rhs) : Point((Point)rhs), dx(rhs.dx), dy(rhs.dy) {}
   Vector(float dx, float dy, float x, float y) : Point(x, y)
   {
      // just need to initialize dx and dy,
      // these functions would have error checking if I could think of what
      // to check for
      setDx(dx);
      setDy(dy);
   }

   // getters
   float getDx() const { return dx;}
   float getDy() const { return dy;}
   Point getPoint() const { return (Point)(*this); }

   // setters
   void setDx(float dx);
   void setDy(float dy);
   void addDx(float dx)    { setDx(this->dx + dx);}
   void addDy(float dy)    { setDy(this->dy + dy);}

   // Move the vector by dx and dy, using the error checking in setX/Y
   void advance()
   {
      setX(x += dx);
      setY(y += dy);
   }

   float operator - (const Vector & rhs) const { return getDistance(rhs); }
   Vector & operator++ (int rhs)
   {
      advance();
      return *this;
   };
   Vector & operator++ () 
   {
      advance();
      return *this;
   };
   // This is very helpful in our advance functions. It just adds the current
   // velocity to the position and does so for both x and y.
   Vector & operator+= (const Vector & rhs)
   {
      dx += rhs.dx;
      dy += rhs.dy;
      return *this;
   }
   const Vector & operator= (const Vector & rhs);

   float getDistance(const Vector & rhs) const;


protected:
   // variables
   float dx;
   float dy;
};
#endif // VECTOR_H
