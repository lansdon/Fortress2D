#pragma once
#include "gameobj.h"
class GOFence :
	public GameObj
{
public:
	GOFence(Settings *settings, double x, double y);
	~GOFence(void);
};

