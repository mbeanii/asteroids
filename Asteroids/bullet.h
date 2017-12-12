/***********************************************************************
 * Header File:
 *    Bullet : The representation of a position on the screen
 * Author:
 *    Brandon Hartshorn
 * Summary:
 *    A class encapsulating all that is bullet.
 *  Bullet inherits inertia.
 *  Bullet is never called with a default constructor.
 *  Bullet has a framesAlive variable to track how long it's been around.
 *  When this exceeds the BULLET_LIFE (in asteroids.h), we will kill it. 
 *
 *  Bullet's non-default constructor takes a vector as a parameter. We will
 *  call this with the ship's vector. Bullet's velocity is then set to this
 *  velocity. Wrap is set to true, and it is given a radius of 0 for hit
 *  detection calculation.
 *
 *  Draw calls "drawDot" from uiDraw.h.
 *
 *  Advance adds the velocity value to the position. This is how we achieve
 *  movement throughout the game.
 *
 *  Kill simply sets dead to true.
 ************************************************************************/

#ifndef BULLET_H
#define BULLET_H

#include <cassert>
#include <iostream>

#include "asteroids.h"
#include "uiDraw.h"

/************************************************************************
 * BULLET
 *   Pew pew
 ***********************************************************************/
class Bullet : public Inertia
{
public:
   // constructors
   Bullet() {}
   Bullet(const Vector & initVector) : framesAlive(0)
   {
      // Copy the vector to the bullet
      v = initVector;
      v.setWrap(true);
      type = BULLET;
      radius = 0;
   }
   virtual void draw() const
   {
      if ( !v.isDead())
      {
         drawDot(v.getPoint());
      }
   }
   virtual void advance(const Interface *pUI, Asteroids & game)
   {
      // Kill the bullet if it's out of frames, else move it
      if (framesAlive < BULLET_LIFE)
      {
         v++;
         ++framesAlive;
      }
      else
      {
         kill(game);
      }
   }
   virtual void kill(Asteroids & game) { v.kill(); }
private:
   int framesAlive;
};

#endif //BULLET_H
