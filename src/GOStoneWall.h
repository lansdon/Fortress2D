#pragma once
#include "gameobj.h"
class GOStoneWall :
	public GameObj
{
public:
	GOStoneWall(WinParems *parems, double x, double y);
	~GOStoneWall(void);
};

