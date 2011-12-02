#include "GOArcher.h"



GOArcher::GOArcher(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{

	hpCur = 30;			// current hitpoints
	hpMax = 30;			// max hitpoints
	arCur = 2;			// current armor
	arMax = 2;			// Max Armor
	damage_basic = 11;	// basic damage (melee)
	damage_range = 20;	// ranged damage
//	setVelocity(1);		// max velocity (m/s)
	density = 1.0;
	friction = 0.03;
	velocityMax = 5;

	textWidth = Util::pixel2Meter(36);	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight =  Util::pixel2Meter(144);	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = ATTACKER;
	setupB2D(x, y);

	setTeam(true); // NPC team

	textureID = TextureLoader::LoadGLTextures("archer.jpg");

}

GOArcher::~GOArcher(void)
{
}
