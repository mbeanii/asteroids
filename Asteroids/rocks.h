/***********************************************************************
 * Header File:
 *    Rocks : The representation of a position on the screen
 * Author:
 *    Brandon Hartshorn
 *    Marcus Bean
 * Summary:
 *    The rock classes, large, medium, and small. But wait, there's more!
 * Order today and we'll throw in a PowerUp class free of charge. So that's
 * The large rock class, the medium rock class, and the small rock class,
 * AND your free PowerUp class - your gift for ordering today!
 ************************************************************************/

#ifndef ROCKS_H
#define ROCKS_H

#include <cassert>
#include <iostream>
#include <cmath>    // for the absolute value function "fabs"

#include "asteroids.h"
#include "uiDraw.h"
//#include "powerup.h"

/************************************************************************
 * POWERUP
 * Bonus Class
 *   These drop every so often when you kill an asteroid. Get one and get
 * an extra life. Go team.
 ***********************************************************************/
class PowerUp : public Inertia
{
public:
   PowerUp(const Vector & initiVector)
   {
      v = initiVector;
      // powerups don't move, but they need to be inertias so we can include
      // them in our list of inertia objects.
      v.setDx(0);
      v.setDy(0);
      // vertical please
      orientation = 270;
      // for hit detection
      radius = 10;
      type = POWERUP;
      // green
      powerupColor.set(COL_PWRUP);
   }
   void draw()const
   {
      drawBigShip(v.getPoint(), orientation, powerupColor);
   }
   //just need advance() so PowerUp can be in the inertia class club.
   void advance(const Interface *pUI, Asteroids & game) {}
   virtual void kill(Asteroids & game) 
   {
      game.score.addLife();
      v.kill();
   }
private:
   Color powerupColor;
};

/************************************************************************
 * ROCKS
 * Base class, inherits from Vector
 ***********************************************************************/
class Rock : public Inertia
{
public:
   // constructors
   Rock()
   {
      // blue
      rockColor.set(COL_ROCK);
      orientation = random(0, 360);
      v.setWrap(true);
   }

   virtual void draw() const
   {
      drawPolygon(v.getPoint(), radius, sides, orientation, rockColor);
   }

   // keep moving forward
   virtual void advance(const Interface *pUI, Asteroids & game)
   {
      v++;
      orientation += rotateSpeed;
   }

   virtual void kill(Asteroids & game) = 0;
protected:
   int sides;
   int rotateSpeed;
   int points;
   Color rockColor;
};

class SmallRock : public Rock
{
public:
   SmallRock()
   {
      // These guys are just in here in case we accidentally create a rock
      // with a default constructor.
      assert(false);
   }
   SmallRock(const Vector & initVector) : Rock()
   {
      v = initVector;
      radius = 7;
      sides = 3;
      rotateSpeed = 6;
      points = 19;
      type = ROCK;
   }
   // No new rocks, but maybe make a powerup :)
   virtual void kill(Asteroids & game)
   {
      if (random(0, POWERUP_CHANCE) == 1)
      {
         PowerUp * newPowerUp = new PowerUp(v);
         game += newPowerUp;
      }
      // gimme points!
      game.score.changePoints(points);
      game.adjustRocks(-1);
      v.kill(); 
   }
};


class MedRock : public Rock
{
public:
   MedRock()
   {
      // These guys are just in here in case we accidentally create a rock
      // with a default constructor.
      assert(false);
   }
   MedRock(const Vector & initVector) : Rock()
   {
      v = initVector;
      radius = 12;
      sides = 4;
      points = 7;
      rotateSpeed = 4;
      type = ROCK;
   }
   // make 2 baby rocks and maybe a powerup
   virtual void kill(Asteroids & game)
   { 
      Vector smallRockVector(v);
      smallRockVector.addDx(3);
      game += new SmallRock(smallRockVector);
      smallRockVector.addDx(-6);
      game += new SmallRock(smallRockVector);
      if (random(0, POWERUP_CHANCE) == 1)
      {
         PowerUp * newPowerUp = new PowerUp(v);
         game += newPowerUp;
      }
      // scoring handled here.
      game.score.changePoints(points);
      game.adjustRocks(1);
      v.kill(); 
   }
};

class BigRock : public Rock
{
public:
   BigRock() : Rock()
   {
      int x = 0;
      int y = 0;
      // Okay, so here, we don't want to spawn any asteroids right on top of
      // the ship. We want to make sure when we spawn a papa bear, it's far
      // enough away that we can manuever/shoot the rock before it gets to
      // us. Because spawn killing isn't fun for anyone.
      while ( (fabs(x) < SAFE_DISTANCE) )
         x = (random(v.getPoint().getXMin(), v.getPoint().getXMax()));
      while ( (fabs(y) < SAFE_DISTANCE) )
         y = (random(v.getPoint().getYMin(), v.getPoint().getYMax()));
      v.setX(x);
      v.setY(y);
      v.setDx(random(-2, 2));
      v.setDy(random(-2, 2));
      orientation = random(0, 360);
      radius = 20;
      sides = 5;
      points = 5;
      rotateSpeed = 2;
      v.setWrap(true);
      type = ROCK;
   }
   // Make a medium rock, a baby rock, and maybe a powerup
   virtual void kill(Asteroids & game)
   { 
      Vector smallRockVector(v);
      smallRockVector.addDx(2);
      game += new SmallRock(smallRockVector);
      Vector medRockVector(v);
      medRockVector.addDy(1);
      game += new MedRock(medRockVector);
      medRockVector.addDy(-2);
      game += new MedRock(medRockVector);
      if (random(0, POWERUP_CHANCE) == 1)
      {
         PowerUp * newPowerUp = new PowerUp(v);
         game += newPowerUp;
      }
      //Don't forget the points
      game.score.changePoints(points);
      game.adjustRocks(2);
      v.kill(); 
   }
};

#endif //ROCKS_H
