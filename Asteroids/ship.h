/***********************************************************************
 * Header File:
 *    Ship : Shoot everything!
 * Author:
 *    Brandon Hartshorn
 * Summary:
 *    But watch out for the rocks....
 ************************************************************************/

#ifndef SHIP_H
#define SHIP_H

#include <cassert>
#include <cmath>
#include <iostream>

#include "asteroids.h"
#include "bullet.h"
#include "asteroids.h"
#include "uiDraw.h"
#include "uiInteract.h"

/************************************************************************
 * SHIP
 * Base class, inherits from Vector
 ***********************************************************************/
class Ship : public Inertia
{
public:
   // constructors
   Ship()
   {
      // Set position and speed to 0
      v.setX(0);
      v.setY(0);
      v.setDx(0);
      v.setDy(0);
      // Facing up please
      orientation = -90;
      radius = 5;
      v.setWrap(true);
      type = SHIP;
      // Set color... 
      shipColor.set(COL_SHIP);
   }

   virtual void draw() const
   {
      // Just draws the ship with a given color
      drawShip(v.getPoint(), orientation, shipColor);
   }

   virtual void advance(const Interface *pUI, Asteroids & game)
   {
      // Perform rotation
      if (pUI->isRight())
      {
         orientation += -10;
      }
      if (pUI->isLeft())
      {
         orientation += 10;
      }
      // TAKEOFF
      if (pUI->isUp())
      {
         // Create a "thrust" vector, then add it to the ships vector
         // 0.2 pixels per frame per frame in the direction of the ship
         Vector thrust;
         thrust.setDx(0.2 * std::cos(deg2rad(orientation - 180)));
         thrust.setDy(0.2 * std::sin(deg2rad(orientation - 180)));
         v += thrust;
      }
      // FIRE!
      if (pUI->isSpace())
      {
         // Probably a cleaner way.. calculate the bullets vector alone
         float bulletDx = (std::cos(deg2rad(orientation - 180)) * 5);
         float bulletDy = (std::sin(deg2rad(orientation - 180)) * 5);
         Vector bulletVector(bulletDx, bulletDy, v.getX(), v.getY());
         //
         // Then add the ships vector
         bulletVector += v;

         // Create a new bullet with the above vector and add it to the game
         Bullet * newBullet = new Bullet(bulletVector);
         // Move one step so we don't shoot ourselves
         newBullet->advance(pUI, game);
         game += newBullet;
      }
      v++;
   }

   virtual void kill(Asteroids & game) 
   { 
      // You died.. so you lose a life
      game.score.takeLife();

      // If we have more lives, spawn a new ship
      if (game.score.haveLifeLeft())
      {
         game += new Ship();
      }

      // And set this ship to dead
      v.kill();
   }
private:
   Color shipColor;
};

#endif //SHIP_H
