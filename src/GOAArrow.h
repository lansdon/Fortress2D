#pragma once
#include "GameObj.h"
#include "settings.h"

class GOAArrow :
	public GameObj
{
public:
	GOAArrow(Settings *settings, double x, double y);
	~GOAArrow(void);

	bool activate(b2Vec2 mouse) { return false;	}	// dummy stub - override for launcher objects.
	bool isActivated(bool reset) { return false; }	// dummy stub - override for launcher objects.
	virtual bool attackSpecial(GameObj *enemy, SoundManager &sm);						// automatic attack function
	//virtual void deathSpecial(SoundManager &sm) { return; };						// death sequnce
	//virtual void damageSpecial(int amount, SoundManager &sm) { return; };			// damage taken function
	virtual bool moveSpecial(SoundManager &sm);						// automatic move function (using vector quantities)
	//virtual void updateSpecial(SoundManager &sm) { return; };					// Main update function


private:
	int HORIZONTAL_ANGLE;		// Used for rotational calculations
	void calculateHorizontalAngle();

};

