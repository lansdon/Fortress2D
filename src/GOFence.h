#pragma once
#include "gameobj.h"
class GOFence :
	public GameObj
{
public:
	GOFence(WinParems *parems, double x, double y);
	~GOFence(void);
};

