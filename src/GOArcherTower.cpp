#include "GOArcherTower.h"


GOArcherTower::GOArcherTower(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{
	hpCur = 80;			// current hitpoints
	hpMax = 80;			// max hitpoints
	arCur = 5;			// current armor
	arMax = 5;			// Max Armor
	damage_basic = 0;	// basic damage (melee)
	damage_range = 0;	// ranged damage
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

	objID = WinParems::OBJ_T_ARCHER_TOWER;
}


GOArcherTower::~GOArcherTower()
{
}
