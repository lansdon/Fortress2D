#pragma once

#include <Windows.h>
#include "Box2D\Box2D.h"
//#include "DebugTimers.h"
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


class Settings
{
public:
	Settings(void);
	~Settings(void);
	//Settings(Settings &settings);		// copy constructor


	static const int TOTAL_OBJ_IDS = 17;		// UPDATE THIS NUMBER WHEN ADDING OBJECT_TYPES below!!! 
	enum OBJECT_ID {
		OBJ_ID_NONE,			// 0
		//DEFENDERS
		OBJ_ID_MOTE,			// 1
		OBJ_ID_FENCE,			// 2
		OBJ_ID_WOODWALL,		// 3
		OBJ_ID_STONEWALL,		// 4
		OBJ_ID_ARCHER_TOWER,	// 5
		OBJ_ID_MAGE_TOWER,		// 6
		OBJ_ID_OIL_TOWER,		// 7
		OBJ_ID_CATAPAULT,		// 8
		// ATTACKERS
		OBJ_ID_DOG,				// 9
		OBJ_ID_HORDE,			// 10
		OBJ_ID_SPEARMAN,		// 11
		OBJ_ID_ARCHER,			// 12
		OBJ_ID_MAGE,			// 13
		OBJ_ID_SEIGE_ENGINE,	// 14
		// AMMO
		OBJ_ID_ARROW,			// 15
		OBJ_ID_CANNONBALL		// 16
	};

	enum OBJECT_TYPE {OBJ_T_NONE, OBJ_T_ATTACKER, OBJ_T_DEFENDER, OBJ_T_BULLET, OBJ_T_STATIC };		// General object types
	
	// Collision Categories used by Box2d for Collision BitMasking.  Must be powers of 2!!
	enum COLLISION_CATEGORY { 
		COLLISION_CAT_GROUND=1, 
		COLLISION_CAT_NPC_BULLET=2, 
		COLLISION_CAT_NPC_ATTACKER=4,
		COLLISION_CAT_PC_BULLET=16,
		COLLISION_CAT_PC_DEFENDER=32
	};
	//const uint16 COLLISION_GROUP_GROUND;
	//const uint16 COLLISION_GROUP_NPC_BULLET;
	//const uint16 COLLISION_GROUP_NPC_ATTACKER;
	//const uint16 COLLISION_GROUP_PC_BULLET;
	//const uint16 COLLISION_GROUP_PC_DEFENDER;

	float depth() { return COORD_DEPTH; }
	float height() { return COORD_HEIGHT; }
	float width() { return 800.0; }
	float floor() { return FLOOR; }
	float mid() { return 400; }
	void setFloor(float floor) { FLOOR = floor; }
	void setWidth(float width) { COORD_WIDTH = width; }
	void setHeight(float height) { COORD_HEIGHT = height; }
	void setDepth(float depth) { COORD_DEPTH = depth; }
	void setMid(float mid) { MID = mid; }
	b2World *getWorld() { return &world; }
	void step() { world.Step(timeStep, velocityIterations, positionIterations); }
//	Util::Color DEF_COLOR;
	void setTimeStep(double step) { timeStep = step; }
	double getTimeStep() { return timeStep; }

	void setTextures(bool useTextures = true) { textures = useTextures; }
	bool useTextures() { return textures; }
	void setSound(bool bOn = true) { soundOn = bOn; }
	bool useSound() { return soundOn; }

private:

	float FLOOR;			// The Y-AXIS of ground level
	float COORD_WIDTH;	// COORD system dimensions
	float COORD_HEIGHT;	// COORD system dimensions
	float COORD_DEPTH;	// COORD system dimensions
	float MID;				// X-AXIS MIDPOINT where user cannot build past
	
	
	// Settings
	bool textures;				// toggle textures on/off
	bool soundOn;				// toggle sound on/off

	// Box2d stuff
	float32 timeStep;
	int32 velocityIterations;
	int32 positionIterations;
	const static b2Vec2 gravity;	// gravity vector
	b2World world;					// WORLD main hub for box2d
};

