#include "GOBarbarian.h"


GOBarbarian::GOBarbarian(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{

	hpCur = 30;			// current hitpoints
	hpMax = 30;			// max hitpoints
	arCur = 3;			// current armor
	arMax = 3;			// Max Armor
	damage_basic = 5;	// basic damage (melee)
	damage_range = 0;	// ranged damage
	setVelocity(2);		// max velocity (m/s)

	textWidth = .5;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 3;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = ATTACKER;
	setupB2D(x, y);

	setTeam(true); // NPC team

}


GOBarbarian::~GOBarbarian(void)
{
}
