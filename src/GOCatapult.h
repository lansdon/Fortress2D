#pragma once
#include "gameobj.h"
class GOCatapult :
	public GameObj
{
public:
	GOCatapult(Settings *settings, double x, double y);
	~GOCatapult();
};

