#pragma once

#include <vector>
#include "GameObj.h"
#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "GLText.h"
#include <sstream>
#include "WinParems.h"
#include "Util.h"
#include "Vector3.h"
#include <Box2D\Box2D.h>
#include "Performance_Counter.h"
#include "GameObjectManager.h"

class Fort
{
public:
	Fort(WinParems *parems=NULL);
	~Fort(void);

	struct FortParems {
		FortParems(float heightMeters = 1, float widthMeters=1, std::string sName="fodder", float x=50, float y=0, int hp=1, int ar=1) {
			hMeters = heightMeters; wMeters = widthMeters; name = sName; posX = x; posY = y; hitpoints=hp; armor=ar;
		}
		float hMeters;
		float wMeters;
		std::string name;
		float posX;
		float posY;
		int hitpoints;
		int armor;
	};


	static enum PLACEMENT_TYPE { NONE, WALL_WOOD, WALL_STONE, MOTE, TOWER_ARCHER, TOWER_MAGE, TOWER_OIL, CATAPULT, FENCE};
	void setWinParems(WinParems *parems) { winParems = parems; text.setWinParems(parems); }
	void draw(Vector3 mouse);
	void drawPlacementGuide(Vector3 &mouse);
	unsigned int getSectorWidth() { return SECTOR_WIDTH; }
	unsigned int getSectorTotal() { return SECTOR_TOTAL; }
	bool validPlacement(float posX);		// Validate if x coord is valid place to build a fort object
	bool isFortObjSelected();
	bool makeObj(float posX, GameObjectManager &go);
	void start(); // do we need to initialize this object post-constructor?
	void setSelectedType(PLACEMENT_TYPE type);

private:

	unsigned int SECTOR_WIDTH; // Column size of object grid
	unsigned int SECTOR_TOTAL; // Column size of object grid

	std::vector<bool> activeSectors;

	unsigned int getPlacementCol(double mouseX);
	unsigned int getPlacementX(double mouseX);

	std::vector<GameObj*> obj;		// Vector of fortress objects (walls, towers, etc)

	WinParems *winParems;

	GLText text;
	bool addObj(GameObj *newObj);

	FortParems *getObjParems(enum PLACEMENT_TYPE type);
	PLACEMENT_TYPE selectedType;

	// Object Paremeters
	FortParems *pNone;
	FortParems *pWoodWall;
	FortParems *pStoneWall;
	FortParems *pMote;
	FortParems *pTowerArcher;
	FortParems *pTowerMage;
	FortParems *pTowerOil;
	FortParems *pCatapult;
	FortParems *pFence;

	Performance_Counter Timer;	// timer object for restricting rapid placement of objects
	double elapsedTime;
	double PLACEMENT_TIMER; // amount of time between placing objects
};

