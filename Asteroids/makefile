###############################################################
# Program:
#     Project 4, Asteroids
#     Brother Helfrich, CS165
# Author:
#     Brandon Hartshorn - about 60%
#     Marcus Bean - about 40%
# Summary:
#     The classic asteroids game, with an ambient hippy flare. We added levels,
#     lives, points, and extra life powerups. The level increments when you've
#     successfuly destroyed all the current asteroids.
#
#     This is the color scheme used:
#     https://www.colorcodehex.com/color-scheme/1000044.html
#
#     Estimated:  10.0 hrs
#     Actual:     20.0 hrs
#       Marcus mispelled asteriods and broke it
###############################################################

###############################################################
# Programs:
#    Asteroids/a.out:  The playable game
###############################################################
a.out : asteroids.o vector.o uiDraw.o uiInteract.o point.o
	g++ -o a.out asteroids.o vector.o uiDraw.o uiInteract.o point.o -lglut -lGLU -lGL

asteroids : asteroids.o vector.o uiDraw.o uiInteract.o point.o
	g++ -o asteroids asteroids.o vector.o uiDraw.o uiInteract.o point.o -lglut -lGLU -lGL

###############################################################
# Individual files
#    asteroids.o	 Code for the main game
#    uiDraw.o      Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o  Handles input events
#    point.o       The position on the screen
#    vector.o      A class to represent a vector
#    uiTest.o      Driver program for uiDraw and uiTest
###############################################################
asteroids.o : asteroids.cpp asteroids.h vector.h ship.h rocks.h bullet.h
	g++ -c asteroids.cpp

uiInteract.o : uiInteract.cpp uiInteract.h point.h
	g++ -c uiInteract.cpp

uiDraw.o : uiDraw.cpp uiDraw.h point.h
	g++ -c uiDraw.cpp

point.o : point.cpp point.h
	g++ -c point.cpp

vector.o : vector.cpp vector.h
	g++ -c vector.cpp

###############################################################
# General rules
###############################################################
clean :
	rm uiTest asteroids a.out *.o *.tar

turnin:
	tar -cf asteroids.tar *.cpp *.h makefile


