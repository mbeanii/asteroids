/*************************************************************************
 * Header File:
 * Asteroids : The main game file for Asteroids
 * Author:
 *    Brandon Hartshorn
 *    Marcus Bean
 * Summary:
 *    This class contains the state of the game. The main() function is
 *    also included in this file.
 ************************************************************************/

#ifndef ASTEROIDS_H
#define ASTEROIDS_H


#include <list>
#include <cassert>
#include <iostream>
#include <sstream>

#include "vector.h"
#include "uiInteract.h"
#include "uiDraw.h"

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300
#define BULLET_LIFE 35
#define SAFE_DISTANCE 100
#define POWERUP_CHANCE 15

#define COL_SHIP 0x4A6A5D// 0x883738
#define COL_ROCK  0x4A6A5D
#define COL_SCORE 0x703C5A
#define COL_PWRUP 0x517335
#define COL_BG    0x342417

enum inertia_t {ROCK, SHIP, BULLET, POWERUP};

class Asteroids;

/************************************************************************
 * SCORE
 * Keep track of my lives and score!
 ***********************************************************************/
class Score
{
public:
   // Constructor
   Score() : lives(3), points(0)
   {
      // Set up colors for score - purple!
      numColor.set(COL_SCORE);
   }

   // Getter for ship respawn
   bool haveLifeLeft() { return lives; }

   // Setters for lives
   void addLife() { ++lives; } // parenthood
   void takeLife() { --lives; } // ooooh... telestial kingdom
   // Setter for shooting an asteroid
   void changePoints(int adjustment) { points += adjustment; }
   void draw() const;
private:
   int lives;
   int points;
   Color numColor;
   Point max;
};

/************************************************************************
 * INERTIA
 * Base class, inherits from Vector
 ***********************************************************************/
class Inertia
{
public:
   virtual void hit(Asteroids & game, Inertia * test);

   // Getters
   const Vector & getVector() const { return v; } 
   inertia_t getType() const { return type; }
   int getOrientation() const { return orientation; }
   int getRadius() const { return radius; }
   bool isDead() const { return v.isDead(); }

   // Pure virtual functions
   virtual void draw() const = 0;
   virtual void advance(const Interface *pUI, Asteroids & game) = 0;
   virtual void kill(Asteroids & game) = 0;
protected:
   Vector v;
   inertia_t type;
   int radius;
   int orientation;
};

// Needed for remove_if.... there must be a prettier way to do this... right?
class isDead
{
public:
   bool operator() (const Inertia * object) { return object->isDead(); }
};

class Asteroids
{
public:
   Asteroids() : numRocks(0), level(0) {}
   Score score;
   void operator+= (Inertia * rhs) { objects.push_back(rhs); }
   void initialize();
   void adjustRocks(int adjustment) { numRocks += adjustment; }
   void advance(const Interface *pUI)
   {
      std::list <Inertia *>::iterator object = objects.begin();
      for (object = objects.begin(); object != objects.end(); ++object)
      {
         // First do hit detection
         std::list <Inertia *>::iterator checkHit = object;
         for (++checkHit; checkHit != objects.end(); ++checkHit)
         {
            // hit() calls kill()
            (*object)->hit(*this,(*checkHit));
         }

         // Then advance each object
         (*object)->advance(pUI, *this);
      }
   }
   void draw()
   {
      // Just loop through and draw
      std::list <Inertia *>::iterator object = objects.begin();
      for (object = objects.begin(); object != objects.end(); ++object)
      {
         (*object)->draw();
      }
      score.draw();
   }
   void clean()
   {
         objects.remove_if(isDead());

         // NEXT LEVEL CAUSE YOU'RE HARDCORE
         if (numRocks == 0)
         {
            level++;
            initialize();
         }
   }
private:
   std::list <Inertia *> objects;
   int numRocks;
   int level;
};
#endif //ASTEROIDS_H
