#include "GOFence.h"


GOFence::GOFence(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{
		
	hpCur = 20;			// current hitpoints
	hpMax = 20;			// max hitpoints
	arCur = 1;			// current armor
	arMax = 1;			// Max Armor
	damage_basic = 0;	// basic damage (melee)
	damage_range = 0;	// ranged damage
	setVelocity(0);		// max velocity (m/s)

	textWidth = 1;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 2;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = OBJECT_TYPE::DEFENDER;
	setupB2D(x, y);

	setTeam(false); // NPC team

}


GOFence::~GOFence(void)
{
}
