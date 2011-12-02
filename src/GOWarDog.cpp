#include "GOWarDog.h"


GOWarDog::GOWarDog(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{


	this->winParems = parems;
	text.setWinParems(parems);

	//posX = posY = 0;
	//velocity = 50;		// pixels per second
	//angle = 0;		// 0 = right   180 = left   90 = up
	//velX = (velocity * std::cos(Util::deg2Rad(angle))) * elapsedTime;
	//velY = (velocity * std::sin(Util::deg2Rad(angle))) * elapsedTime;

	hpCur = 20;			// current hitpoints
	hpMax = 20;			// max hitpoints
	arCur = 1;			// current armor
	arMax = 1;			// Max Armor
	damage_basic = 2;	// basic damage (melee)
	damage_range = 0;	// ranged damage
	setVelocity(3);		// max velocity (m/s)

	textWidth = 2;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = .5;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = ATTACKER;
	setupB2D(x, y);

	setTeam(true); // NPC team


}


GOWarDog::~GOWarDog(void)
{
}
