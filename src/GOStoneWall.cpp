#include "GOStoneWall.h"


GOStoneWall::GOStoneWall(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{

	hpCur = 500;			// current hitpoints
	hpMax = 500;			// max hitpoints
	arCur = 10;			// current armor
	arMax = 10;			// Max Armor
	damage_basic = 1;	// basic damage (melee)
	damage_range = 0;	// ranged damage
//	setVelocity(1);		// max velocity (m/s)
	density = 50.0;
	friction = 1.0;
	velocityMax = 0;

	textWidth = 3;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 10;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = OBJECT_TYPE::DEFENDER;
	setupB2D(x, y);

	setTeam(false); // NPC team

	textureID = TextureLoader::LoadGLTextures("stonewall.jpg");

}


GOStoneWall::~GOStoneWall(void)
{
}

