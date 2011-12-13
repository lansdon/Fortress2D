#include "GOOilTower.h"


GOOilTower::GOOilTower(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	hpCur = 50;			// current hitpoints
	hpMax = 50;			// max hitpoints
	arCur = 2;			// current armor
	arMax = 2;			// Max Armor
	damage_basic = 30;	// basic damage (melee)
	damage_range = 0;	// ranged damage
//	setVelocity(0);		// max velocity (m/s)

	textWidth = 3;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 5;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = OBJECT_TYPE::DEFENDER;
	setupB2D(x, y);

	setTeam(false); // NPC team
}


GOOilTower::~GOOilTower(void)
{
}
