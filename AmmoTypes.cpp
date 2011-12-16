#include "AmmoTypes.h"


AmmoTypes::AmmoTypes(void)
{
	_arrow_fire = false;
	_arrow_normal = false;
	_cannonball_normal = false;
	_cannonball_fire = false;

}


AmmoTypes::~AmmoTypes(void)
{
}


void AmmoTypes::reset() {
	_arrow_fire = false;
	_arrow_normal = false;
	_cannonball_normal = false;
	_cannonball_fire = false;
}