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

#include <cmath>
#include <cassert>

#include "vector.h"
#include "uiInteract.h"
#include "uiDraw.h"
#include <iostream>


using std::cout;
using std::abs;
using std::pow;

/******************************************
 * SETDX & SETDY
 * Simply sets the dx and dy of the vector
 *****************************************/
void Vector :: setDx(float dx)
{
   // There should basically be something to error check in here, but...
   // I can't think of anything that could go wrong (yet.)
   this->dx = dx;
}

void Vector :: setDy(float dy)
{
   // There should basically be something to error check in here, but...
   // I can't think of anything that could go wrong (yet.)
   this->dy = dy;
}

/******************************************
 * GETDISTANCE
 * Returns the minimum distance between two
 * vectors. Note that it's not a perfectly
 * precise algorithm, but relatively fast
 *****************************************/
float Vector :: getDistance(const Vector & rhs) const
{
   float slicePercent = 0.0;
   float dMax = 0.0;

   dMax = MAX(abs(dx), abs(dy));
   dMax = MAX(dMax, abs(rhs.dx));
   dMax = MAX(dMax, abs(rhs.dy));
   slicePercent = 1.0 / dMax;

   assert(slicePercent > 0);
   // what if it's over 1... bogus answer?

   // Huge value so we get a real distance back even if it's huge
   float minDistance = 1000000.0;

   for (float i = 0.1; i < 1.0; i += slicePercent )
   {
      float distanceSquared = pow((x + dx * i) - (rhs.x + rhs.dx * i),2) +
                              pow((y + dy * i) - (rhs.y + rhs.dy * i),2);
      minDistance = MIN(distanceSquared, minDistance);
   }

   // something would have to be reallly broken
   assert(minDistance >= 0);

   // only sqrt once, 'cause it's sloooow and we use this function a lot
   return sqrt(minDistance);
}

/********************************************
 * VECTOR : Assignmenet
 *******************************************/
const Vector & Vector :: operator = (const Vector & rhs)
{
   x        = rhs.x;
   y        = rhs.y;
   dx       = rhs.dx;
   dy       = rhs.dy;
   check    = rhs.check;
   dead     = rhs.dead;
   wrap     = rhs.wrap;

   return *this;
}

#ifdef TEST_VECTOR
/****************************************************
 * Callback and Main are test functions to implement
 * bird by itself. #ifdef ensures that we only use this
 * code when needed. See our makefile.
 ****************************************************/
float Point::xMin = -200.0;
float Point::xMax =  200.0;
float Point::yMin = -200.0;
float Point::yMax =  200.0;

void callBack(const Interface *pUI, void * p)
{
   Vector * pVector = (Vector *)p;
   if (pVector->isDead())
   {
      float randomAngle = deg2rad(random(0, 360));
      pVector->setX(random(pVector->getXMin(), pVector->getXMax()));
      pVector->setY(random(pVector->getYMin(), pVector->getYMax()));
      pVector->setDx(cos(randomAngle) * 5);
      pVector->setDy(sin(randomAngle) * 5);
      pVector->resurrect();
      cout << "Vector resurrected\n";
   }

   Vector testVector(0.0, 0.0, 1.0, 1.0);
   //cout << pVector->getDistance(testVector) << "\n";
   pVector->getDistance(testVector);
   pVector->advance();
   Point testPos(testVector.getX(), testVector.getY());
   Point pos(pVector->getX(), pVector->getY());
   drawDot(pos);
   drawDot(testPos);

}
int main(int argc, char ** argv)
{
   Interface ui(argc, argv, "Test Vector");
   Vector vector;
   vector.setCheck(true);
   vector.kill();
   ui.run(callBack, &vector);
}
#endif
