#include "WinParems.h"

const b2Vec2 WinParems::gravity = b2Vec2(0, -10);

WinParems::WinParems()  : world(b2Vec2(0, -10))
{

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


WinParems::~WinParems()
{
}


//WinParems::WinParems(WinParems &parems) {		// copy constructor
//	this->COORD_DEPTH = parems.COORD_DEPTH;
//	this->COORD_HEIGHT = parems.COORD_HEIGHT;
//
//
//}