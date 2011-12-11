#pragma once
#include "GameObj.h"
#include "WinParems.h"

class GOAArrow :
	public GameObj
{
public:
	GOAArrow(WinParems *parems, double x, double y);
	~GOAArrow(void);

	bool activate(b2Vec2 mouse) { return false;	}	// dummy stub - override for launcher objects.
	bool isActivated(bool reset) { return false; }	// dummy stub - override for launcher objects.


private:



};

