#include "GOAArrow.h"


GOAArrow::GOAArrow(WinParems *parems, double x, double y) : GameObj(parems, x, y)
{

	hpCur = 5;			// current hitpoints
	hpMax = 5;			// max hitpoints
	arCur = 0;			// current armor
	arMax = 0;			// Max Armor
	damage_basic = 1000;	// basic damage (melee)
	damage_range = 1000;	// ranged damage
	setVelocity(0);		// max velocity (m/s)

	textWidth = 3;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 5;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	density = 0.4;
	friction = .03;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = OBJECT_TYPE::BULLET;
	objID = WinParems::OBJ_T_ARROW;

	setupB2D(x, y);

//	setTeam(false); // NPC team

	textureID = TextureLoader::LoadGLTextures("archer.jpg");



}


GOAArrow::~GOAArrow(void)
{
}
