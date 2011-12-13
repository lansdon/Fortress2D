#include "GOSeigeEngine.h"


GOSeigeEngine::GOSeigeEngine(Settings *settings, double x, double y) : GameObj(settings, x, y)
{

	
	hpCur = 50;			// current hitpoints
	hpMax = 50;			// max hitpoints
	arCur = 5;			// current armor
	arMax = 5;			// Max Armor
	damage_basic = 0;	// basic damage (melee)
	damage_range = 20;	// ranged damage
	setVelocityMax(1);		// max velocity (m/s)

	textWidth = 10;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 7;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = ATTACKER;
	setupB2D(x, y);

	setTeam(true); // NPC team

}


GOSeigeEngine::~GOSeigeEngine(void)
{
}
