#pragma once
#include "gameobj.h"
#include "WinParems.h"
#include "AmmoTypes.h"

#include <vector>

class Launcher :
	public GameObj
{

public:
	Launcher(WinParems parems, int x, int y);
	~Launcher(void);
	AmmoTypes &getAmmoTypes() { return ammo; }



private:

	// Launch Settings
	float MIN_VEL;			// Lower bounds of launch velocity meters/sec
	float MAX_VEL;			// Upper bounds of launch velocity meters/sec
	bool LEFT_ORIENTATION; // true = facing left    false = facing right
	int MIN_ANGLE;			// MIN angle allowed (0 = horizontal plane. POS = up, neg = down.
	int MAX_ANGLE;

	// Variables
	int launchAngle;		// User defined current launch angle
	int launchVelocity;		// Speed the ammo is launched at

	// Timer
	Performance_Counter launchTimer;			// Rate of Fire in seconds

	// Ammo Types
	AmmoTypes ammo;
	

};

