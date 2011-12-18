#include "settings.h"

const b2Vec2 Settings::gravity = b2Vec2(0, -10);

Settings::Settings()  : world(b2Vec2(0, -10))
{
	world.SetAllowSleeping(true);
	FLOOR = 10.0;			// The Y-AXIS of ground level
	COORD_WIDTH = 800.0;	// COORD system dimensions
	COORD_HEIGHT = 600.0;	// COORD system dimensions
	COORD_DEPTH = -755.0;	// COORD system dimensions
	MID = COORD_WIDTH/2.0;				// X-AXIS MIDPOINT where user cannot build past
	
	// Windows handler + Device Context
	//hDC = NULL;		// Private GDI Device Context	
	//hWnd = NULL;		// Holds Our Window Handle

//	DEF_COLOR.setColors(1, 1, 1, 1);

	// Box 2D
	timeStep = 1.0f / 60.0f;			// 60 FPS
	velocityIterations = 8;
	positionIterations = 3;

	// Toggle to turn textures off
	textures = true;

}


Settings::~Settings()
{
}


//Settings::Settings(Settings &settings) {		// copy constructor
//	this->COORD_DEPTH = settings.COORD_DEPTH;
//	this->COORD_HEIGHT = settings.COORD_HEIGHT;
//
//
//}