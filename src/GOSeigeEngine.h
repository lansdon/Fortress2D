#pragma once
#include "gameobj.h"
class GOSeigeEngine :
	public GameObj
{
public:
	GOSeigeEngine(Settings *settings, double x, double y);
	~GOSeigeEngine();
};

