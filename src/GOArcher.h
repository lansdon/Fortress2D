#pragma once
#include "gameobj.h"

class GOArcher :
	public GameObj
{
public:
	GOArcher(Settings *settings, double x, double y);
	~GOArcher(void);

	bool activate(b2Vec2 mouse) { return false; }	// dummy stub - override for launcher objects.
	bool isActivated(bool reset) { return false; }	// dummy stub - override for launcher objects.

};

