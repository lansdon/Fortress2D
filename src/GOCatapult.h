#pragma once
#include "gameobj.h"
class GOCatapult :
	public GameObj
{
public:
	GOCatapult(WinParems *parems, double x, double y);
	~GOCatapult();
};

