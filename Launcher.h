#pragma once
#include "gameobj.h"
#include "settings.h"
#include "AmmoTypes.h"

#include <vector>
//
//
//struct LaunchSettings {
//
//	b2Vec2 launchVelocity;
//	double launchAngle;
//
//}


class Launcher :
	public GameObj
{

public:
	Launcher(Settings *settings, int x, int y);
	~Launcher(void);
	AmmoTypes &getAmmoTypes() { return goSettings.getAmmoTypes(); }

	void draw(b2Vec2 mouse);					// Overloaded draw function
	void setActivated(bool bActive);			// set item to be active (true) or inactive (false)
	bool activate(b2Vec2 mouse);	// dummy stub - override for launcher objects.
	bool isActivated(bool reset);	// dummy stub - override for launcher objects.
//	void launch(void *go);
	float getLaunchVelocity() { return launchVelocity; }				// meters per second
	float getLaunchAngle() { return launchAngle; }						// degrees
	void setLaunchVelocity(float vel) { launchVelocity = vel; }			// meters per second
	void setLaunchAngle(float theta) { launchAngle = theta; }			// degrees

protected:
	// Launch Settings
	//float MIN_VEL;			// Lower bounds of launch velocity meters/sec
	//float MAX_VEL;			// Upper bounds of launch velocity meters/sec
	//bool LEFT_ORIENTATION; // true = facing left    false = facing right
	//int MIN_ANGLE;			// MIN angle allowed (0 = horizontal plane. POS = up, neg = down.
	//int MAX_ANGLE;
	//int MAX_PULL_LENGTH;		// (max length a user can pull on launcher to achieve max launch velocity. (pixels)

	//// Variables
	float launchAngle;		// User defined current launch angle
	float launchVelocity;		// Speed the ammo is launched at
	bool activated;			// true if user is currently clicking on the launcher

	// Timer
	Performance_Counter launchTimer;			// Rate of Fire in seconds

	// Ammo Types
//	AmmoTypes ammo;
	
	double calculateMouseAngle(b2Vec2 mouse);
	double Launcher::getLauncherDrawLength(b2Vec2 mouse);


private:


};

