#pragma once
#include "gameobj.h"
class GOWoodWall :
	public GameObj
{
public:
	GOWoodWall(Settings *settings, double x, double y);
	~GOWoodWall();
	bool activate(b2Vec2 mouse) { return false; }	// dummy stub - override for launcher objects.
	bool isActivated(bool reset) { return false; }	// dummy stub - override for launcher objects.

};

