
#include "asteroids.h"
#include "ship.h"
#include "bullet.h"
#include "rocks.h"

/***********************************************************************
 * Returns the number of digits in a number to
 * align left or right as needed.
 ************************************************************************/
int numDigits(int x)
{
    //if (x == MIN_INT) return 10 + 1;
    if (x < 0) return numDigits(-x) + 1;

    if (x >= 10000) {
        if (x >= 10000000) {
            if (x >= 100000000) {
                if (x >= 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if (x >= 100000) {
            if (x >= 1000000)
                return 7;
            return 6;
        }
        return 5;
    }
    if (x >= 100) {
        if (x >= 1000)
            return 4;
        return 3;
    }
    if (x >= 10)
        return 2;
    return 1;
}

/***********************************************************************
 * Score : Draw
 *   calls drawNumber from uiDraw to print the number.
 ************************************************************************/
void Score :: draw() const
{
   assert( lives >= 0 && points >= 0);

   Point pointPos(max.getXMin() + 5, max.getYMax() - 15);

   std::stringstream pointStream;
   pointStream << "POINTS: ";
   pointStream << points;

   std::string pointString = pointStream.str();
   char const * pointChar = pointString.c_str();

   Point livesPos(max.getXMax() - 64, max.getYMax() - 15);

   std::stringstream livesStream;
   livesStream << "LIVES: ";
   livesStream << lives;

   std::string livesString = livesStream.str();
   char const * livesChar = livesString.c_str();

   drawText(pointPos, pointChar, numColor);
   drawText(livesPos, livesChar, numColor);
}

void Inertia :: hit(Asteroids & game, Inertia * test)
{
   if (type == POWERUP)
   {
      if ((test->getType() == SHIP)
          && (v - test->getVector() < radius + test->getRadius()))
      {
         kill(game);
      }
   }
   else if (test->getType() == POWERUP)
   {
      if ((type == SHIP)
         && (v - test->getVector() < radius + test->getRadius()))
      {
         test->kill(game);
      }
   }
   else if (type != test->getType() && !isDead() && !test->isDead())
   {
      if (v - test->getVector() < radius + test->getRadius())
      {
         kill(game);
         test->kill(game);
      }
   }
}

void Asteroids :: initialize()
{
   for (int i = 0; i < level; ++i)
   {
      (*this)+= new BigRock;
      numRocks++;
   }
}

// MAIN GAME FUNCTIONS

float Point::xMin = -WINDOW_WIDTH/2;
float Point::xMax =  WINDOW_WIDTH/2;
float Point::yMin = -WINDOW_HEIGHT/2;
float Point::yMax =  WINDOW_HEIGHT/2;

void callBack( const Interface *pUI, void * p)
{
   Asteroids *pAsteroids = (Asteroids *)p;
   pAsteroids->clean();
   pAsteroids->advance(pUI);
   pAsteroids->draw();
}

int main(int argc, char ** argv)
{
   Color bgColor(COL_BG);
   Interface ui(argc, argv, "ASTEROIDS", bgColor);
   Asteroids game;
   /*
   for (int i = 0; i < 6; ++i)
   {
      Rock * newRock = new BigRock();
      game += newRock;
   }
   */
   Ship * newShip = new Ship();
   game += newShip;
   ui.run(callBack, &game);
}
