/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 *    Marcus Bean - added "drawBigShip" AND COLORS TO EVERYTHING
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#ifndef UI_DRAW_H
#define UI_DRAW_H

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include "point.h"    // Where things are drawn

using std::string;

class Color
{
public:
   Color() { set(0x000000); }
   Color(int hex) { set(hex); }
   void set(int hex)
   {
      rint = (hex >> 16) & 0xff;
      gint = (hex >> 8) & 0xff;
      bint = hex & 0xff;
      rfloat = (rint / 255.0);
      gfloat = (gint / 255.0);
      bfloat = (bint / 255.0);
   }

   int getInt(char color)
   {
      switch (color)
      {
         case 'r':
            return rint;
         case 'g':
            return gint;
         case 'b':
            return bint;
      }
      return -1;
   }
   float getFloat(char color)
   {
      switch (color)
      {
         case 'r':
            return rfloat;
         case 'g':
            return gfloat;
         case 'b':
            return bfloat;
      }
      return -1;
   }

private:
   int rint;
   int gint;
   int bint;
   float rfloat;
   float gfloat;
   float bfloat;
};

/************************************************************************
 * DRAW DIGIT
 * Draw a single digit in the old school line drawing style.  The
 * size of the glyph is 8x11 or x+(0..7), y+(0..10)
 *************************************************************************/
void drawDigit(const Point & topLeft, char digit, Color color);

/*************************************************************************
 * DRAW NUMBER
 * Display an positive integer on the screen using the 7-segment method
 *************************************************************************/
void drawNumber(const Point & topLeft, unsigned int number, Color color);

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 ************************************************************************/
void drawText(const Point & topLeft, const char * text, Color color);

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen centered on a given point (center) of
 * a given size (width, height), and at a given orientation (rotation)
 * measured in degrees (0 - 360)
 *************************************************************************/
void drawRect(const Point & center, int width, int height, int rotation);

/************************************************************************
 * DRAW CIRCLE
 * Draw a circle from a given location (center) of a given size (radius).
 *************************************************************************/
void drawCircle(const Point & center, int radius);

/************************************************************************
 * DRAW POLYGON
 * Draw a polygon from a given location (center) of a given size (radius).
 *************************************************************************/
void drawPolygon(const Point & center, int radius, int points, int rotation, Color color);

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Point & begin, const Point & end, Color color);

/************************************************************************
 * DRAW DOT
 * Draw a single point on the screen, 2 pixels by 2 pixels
 *************************************************************************/
void drawDot(const Point & point);

/************************************************************************
 * DRAW Ship
 * Draw the spaceship on the screen
 *************************************************************************/
void drawShip(const Point & point, int rotation, Color color);

/************************************************************************
 * DRAW Ship
 * Draws a bigger spaceship on the screen
 *************************************************************************/
void drawBigShip(const Point & point, int rotation, Color color);

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters 
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);

#define deg2rad(value) ((M_PI / 180) * (value))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))


#endif // UI_DRAW_H
