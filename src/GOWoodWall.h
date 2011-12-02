#pragma once
#include "gameobj.h"
class GOWoodWall :
	public GameObj
{
public:
	GOWoodWall(WinParems *parems, double x, double y);
	~GOWoodWall();
};

