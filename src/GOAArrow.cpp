#include "GOAArrow.h"


GOAArrow::GOAArrow(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("arrow.dat", x, y);

	HORIZONTAL_ANGLE = 0;
	calculateHorizontalAngle();
}


GOAArrow::~GOAArrow(void)
{
}


bool GOAArrow::attackSpecial(GameObj *enemy, SoundManager &sm) {
	// Arrows attack once and are destroyed
	if(this->getTypeID() == Settings::OBJ_ID_ARROW) {
		this->setHP(0);
	}
	return false; 
}


bool GOAArrow::moveSpecial(SoundManager &sm) {
	calculateHorizontalAngle();
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
	if(goSettings._initAngle >= 0 && goSettings._initAngle < 90) {
		HORIZONTAL_ANGLE = 90;
	}
	// QUADRANT II
	else if(goSettings._initAngle >= 90 && goSettings._initAngle < 180) {
		HORIZONTAL_ANGLE = 180;
	}
	// QUADRANT III
	else if(goSettings._initAngle >= 180 && goSettings._initAngle < 270) {
		HORIZONTAL_ANGLE = 270;
	}
	// QUADRANT IV
	else if(goSettings._initAngle >= 270 && goSettings._initAngle < 360) {
		HORIZONTAL_ANGLE = 0;
	}


}


