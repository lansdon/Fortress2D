#include "GOMageTower.h"


GOMageTower::GOMageTower(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{
	hpCur = 60;			// current hitpoints
	hpMax = 60;			// max hitpoints
	arCur = 3;			// current armor
	arMax = 3;			// Max Armor
	damage_basic = 10;	// basic damage (melee)
	damage_range = 35;	// ranged damage
	setVelocity(0);		// max velocity (m/s)

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


GOMageTower::~GOMageTower()
{
}
