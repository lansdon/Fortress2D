#pragma once
#include "gameobj.h"
#include "Launcher.h"


class GOArcherTower :
	public Launcher
{
public:
	GOArcherTower(WinParems *parems, double x, double y);
	~GOArcherTower();
	bool activate(Vector3 coord);			// activates the button if mouse coords match button location
	bool isActivated(bool reset = false);	// check if activated
//	void draw(b2Vec2 mouse);					// Overloaded draw function
	void setActivated(bool bActive);			// set item to be active (true) or inactive (false)
};

