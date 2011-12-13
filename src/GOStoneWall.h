#pragma once
#include "gameobj.h"
class GOStoneWall :
	public GameObj
{
public:
	GOStoneWall(Settings *settings, double x, double y);
	~GOStoneWall(void);
	bool activate(b2Vec2 mouse) { return false; }	// dummy stub - override for launcher objects.
	bool isActivated(bool reset) { return false; }	// dummy stub - override for launcher objects.
};

