#pragma once

#include <Windows.h>
#include "Box2D\Box2D.h"
//#include <math.h>			// Header File For Windows Math Library
//#include <stdio.h>			// Header File For Standard Input/Output
//#include <stdarg.h>			// Header File For Variable Argument Routines
//#include <gl\gl.h>			// Header File For The OpenGL32 Library
//#include <gl\glu.h>			// Header File For The GLu32 Library


//
//struct buttonState {
//	buttonState() { pressed = false; } // held = false; }
//	bool pressed;
////		bool held;
//	int x, y;
//};


class WinParems
{
public:
	WinParems(void);
	~WinParems(void);
	//WinParems(WinParems &parems);		// copy constructor

	float depth() { return COORD_DEPTH; }
	float height() { return COORD_HEIGHT; }
	float width() { return 800.0; }
	float floor() { return FLOOR; }
	float mid() { return 400; }
	//HDC hdc() { return *hDC; }
	//HWND hwnd() { return *hWnd; }
	void setFloor(float floor) { FLOOR = floor; }
	void setWidth(float width) { COORD_WIDTH = width; }
	void setHeight(float height) { COORD_HEIGHT = height; }
	void setDepth(float depth) { COORD_DEPTH = depth; }
	void setMid(float mid) { MID = mid; }
	//void setHDC(HDC *hdc) { hDC = hdc; }
	//void setHWND(HWND *hwnd) { hWnd = hwnd; }
	b2World *getWorld() { return &world; }
	void step() { world.Step(timeStep, velocityIterations, positionIterations); }
//	Util::Color DEF_COLOR;
	void setTimeStep(double step) { timeStep = step; }
	double getTimeStep() { return timeStep; }

	void setTextures(bool useTextures = true) { textures = useTextures; }

	bool useTextures() { return textures; }

private:

	float FLOOR;			// The Y-AXIS of ground level
	float COORD_WIDTH;	// COORD system dimensions
	float COORD_HEIGHT;	// COORD system dimensions
	float COORD_DEPTH;	// COORD system dimensions
	float MID;				// X-AXIS MIDPOINT where user cannot build past
	
	
	// Settings
	bool textures;

	// Windows Handlers
	//HDC			*hDC;		// Private GDI Device Context	
	//HWND		*hWnd;		// Holds Our Window Handle

	// Box2d stuff
	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	const static b2Vec2 gravity;	// gravity vector
	b2World world;					// WORLD main hub for box2d
};

