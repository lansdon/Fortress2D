#pragma once
#include "gameobj.h"
class GOWoodWall :
	public GameObj
{
public:
	GOWoodWall(Settings *settings, double x, double y);
	~GOWoodWall();
};

