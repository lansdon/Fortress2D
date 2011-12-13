#include "GOAArrow.h"


GOAArrow::GOAArrow(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	this->setName("Arrow");		// Name
	hpCur = 5;					// current hitpoints
	hpMax = 5;					// max hitpoints
	arCur = 0;					// current armor
	arMax = 0;					// Max Armor
	damage_basic = 1000;		// basic damage (melee)
	damage_range = 1000;		// ranged damage
	setVelocityMax(0);		// max velocity (m/s)
	setCurrentLinearVelocity(b2Vec2(0,0));

	textWidth = 5;				// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 1;				// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	density = 1;
	friction = 5;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = OBJECT_TYPE::BULLET;
	objID = Settings::OBJ_T_ARROW;

	setupB2D(x, y);

//	setTeam(false); // NPC team

	textureID = TextureLoader::LoadGLTextures("archer.jpg");

	HORIZONTAL_ANGLE = 0;
	calculateHorizontalAngle();
}


GOAArrow::~GOAArrow(void)
{
}


bool GOAArrow::attackSpecial(GameObj *enemy, SoundManager &sm) {
	// Arrows attack once and are destroyed
	if(this->getTypeID() == Settings::OBJ_T_ARROW) {
		this->setHP(0);
	}
	return false; 
}


bool GOAArrow::moveSpecial(SoundManager &sm) {
	if(!HORIZONTAL_ANGLE) calculateHorizontalAngle();
	double angleMultiplier =  ( (HORIZONTAL_ANGLE-getInitVecAngle()) / this->getInitLinearVelocity().y );
	double adjustment = body->GetLinearVelocity().y * angleMultiplier;
	double newAngle = HORIZONTAL_ANGLE - adjustment;

	// Accomodate for downward launches
	if(this->getInitLinearVelocity().y < 0) {
		angleMultiplier =  ( (HORIZONTAL_ANGLE-getInitVecAngle()) / body->GetPosition().y );
		adjustment = std::abs(body->GetPosition().y * angleMultiplier);
		newAngle = HORIZONTAL_ANGLE - adjustment;
	}
	
	
	body->SetTransform(body->GetPosition(), Util::deg2Rad(newAngle));
	this->setCurrentVecAngle(newAngle);
	return false;
}


void GOAArrow::calculateHorizontalAngle() {

	// QUADRANT I
	if(initAngle >= 0 && initAngle < 90) {
		HORIZONTAL_ANGLE = 90;
	}
	// QUADRANT II
	else if(initAngle >= 90 && initAngle < 180) {
		HORIZONTAL_ANGLE = 180;
	}
	// QUADRANT III
	else if(initAngle >= 180 && initAngle < 270) {
		HORIZONTAL_ANGLE = 270;
	}
	// QUADRANT IV
	else if(initAngle >= 270 && initAngle < 360) {
		HORIZONTAL_ANGLE = 0;
	}


}


