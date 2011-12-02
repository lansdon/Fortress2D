#include "GOWoodWall.h"


GOWoodWall::GOWoodWall(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{
				
	hpCur = 10;			// current hitpoints
	hpMax = 10;			// max hitpoints
	arCur = 100;			// current armor
	arMax = 100;			// Max Armor
	damage_basic = 0;	// basic damage (melee)
	damage_range = 0;	// ranged damage
	setVelocity(0);		// max velocity (m/s)

	textWidth = 5;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 0.25;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = OBJECT_TYPE::DEFENDER;
	setupB2D(x, y);

	setTeam(false); // NPC team
}


GOWoodWall::~GOWoodWall()
{
}
