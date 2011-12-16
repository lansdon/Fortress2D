#include "GOSettings.h"


GOSettings::GOSettings(void)
{
	// Initialize with default arguments
	this->setBasicSettings();
	this->setDefColors();
	this->setLauncherSettings();
	this->setObjectTypes();
	this->setPhysicalSettings();
	this->setSoundTimers();
	this->_textureFilename = "default.jpg";
}


GOSettings::~GOSettings(void)
{
}



bool GOSettings::loadFromFile(std::string file) {
	std::string fLoc = "GO/" + file;
	std::fstream data(fLoc);

	// ERROR!
	if(!data) {
		return false;
	}

	while(!data.eof()) {
		std::stringstream value;
		std::string temp;
		std::getline(data, temp);
		std::stringstream parameter(temp);
		if(isValidParameter(parameter)) {
			std::getline(data, temp);
			std::stringstream value(temp);
//			value.str() = temp;
			parseFileData(parameter, value);
		}
	}
	return true;
}



void GOSettings::saveExampleFile() {


}

bool GOSettings::isValidParameter(std::stringstream &parameter) {
	if(parameter.str() == "NAME:" ||
		parameter.str() == "OBJECT TYPE:" ||
		parameter.str() == "OBJECT TYPE ID:" ||
		parameter.str() == "HP CURRENT:" ||
		parameter.str() == "HP MAX:" ||
		parameter.str() == "AR CURRENT:" ||
		parameter.str() == "AR MAX:" ||
		parameter.str() == "DAMAGE MELEE:" ||
		parameter.str() == "DAMAGE RANGED:" ||
		parameter.str() == "NPC TEAM:" ||
		parameter.str() == "POS X:" ||
		parameter.str() == "POS Y:" ||
		parameter.str() == "VEL X:" ||
		parameter.str() == "VEL Y:" ||
		parameter.str() == "MAX VELOCITY:" ||
		parameter.str() == "INIT ANGLE:" ||
		parameter.str() == "DENSITY:" ||
		parameter.str() == "FRICTION:" ||
		parameter.str() == "TEXTURE WIDTH:" ||
		parameter.str() == "TEXTURE HEIGHT:" ||
		parameter.str() == "SOUND TIMER MOVE:" ||
		parameter.str() == "SOUND TIMER MELEE:" ||
		parameter.str() == "SOUND TIMER RANGED:" ||
		parameter.str() == "SOUND TIMER DAMAGED:" ||
		parameter.str() == "SOUND TIMER DEATH:" ||
		parameter.str() == "SOUND TIMER IDLE:" ||
		parameter.str() == "LAUNCH MIN VEL:" ||
		parameter.str() == "LAUNCH MAX VEL:" ||
		parameter.str() == "LAUNCH MIN ANGLE:" ||
		parameter.str() == "LAUNCH MAX ANGLE:" ||
		parameter.str() == "RATE OF FIRE:" ||
		parameter.str() == "ORIENTATION:" ||
		parameter.str() == "PULL LENGTH:" ||
		parameter.str() == "AMMO ARROW:" ||
		parameter.str() == "AMMO CANNONBALL:" ||
		parameter.str() == "TEXTURE FILENAME:"
	) {
		return true;
	} else {
		return false;
	}
}

void GOSettings::parseFileData(std::stringstream &parameter, std::stringstream &value) {
	if(parameter.str() == "NAME:") {
		value >> _name;
	} else if(parameter.str() == "OBJECT TYPE:") {
		int tempid;
		value >> tempid;
		this->_objType = (Settings::OBJECT_TYPE)tempid;
	} else if(parameter.str() == "OBJECT TYPE ID:") {
		int tempid;
		value >> tempid;
		this->_objTypeID = (Settings::OBJECT_ID)tempid;
	} else if(parameter.str() == "HP CURRENT:") {
		value >> this->_hpCur;
	} else if(parameter.str() == "HP MAX:") {
		value >> this->_hpMax;
	} else if(parameter.str() == "AR CURRENT:") {
		value >> this->_arCur;
	} else if(parameter.str() == "AR MAX:") {
		value >> this->_arMax;
	} else if(parameter.str() == "DAMAGE MELEE:") {
		value >> this->_damage_melee;
	} else if(parameter.str() == "DAMAGE RANGED:") {
		value >> this->_damage_ranged;
	} else if(parameter.str() == "NPC TEAM:") {
		value >> this->_npcTeam;
	} else if(parameter.str() == "POS X:") {
		value >> this->_initPosition.x;
	} else if(parameter.str() == "POS Y:") {
		value >> this->_initPosition.y;
	} else if(parameter.str() == "VEL X:") {
		value >> this->_initLinearVelocity.x;
	} else if(parameter.str() == "VEL Y:") {
		value >> this->_initLinearVelocity.y;
	} else if(parameter.str() == "MAX VELOCITY:") {
		value >> this->_velocityMax;
	} else if(parameter.str() == "INIT ANGLE:") {
		value >> this->_initAngle;
		this->_angle = _initAngle;
	} else if(parameter.str() == "DENSITY:") {
		value >> this->_density;
	} else if(parameter.str() == "FRICTION:") {
		value >> this->_friction;
	} else if(parameter.str() == "TEXTURE WIDTH:") {
		value >> this->_textWidth;
	} else if(parameter.str() == "TEXTURE HEIGHT:") {
		value >> this->_textHeight;
	} else if(parameter.str() == "TEXTURE FILENAME:") {
		value >> this->_textureFilename;
	} else if(parameter.str() == "SOUND TIMER MOVE:") {
		value >> this->_TIMER_SOUND_MOVE;
	} else if(parameter.str() == "SOUND TIMER MELEE:") {
		value >> this->_TIMER_SOUND_MELEE;
	} else if(parameter.str() == "SOUND TIMER RANGED:") {
		value >> this->_TIMER_SOUND_RANGED;
	} else if(parameter.str() == "SOUND TIMER DAMAGED:") {
		value >> this->_TIMER_SOUND_DAMAGED;
	} else if(parameter.str() == "SOUND TIMER DEATH:") {
		value >> this->_TIMER_SOUND_DEATH;
	} else if(parameter.str() == "SOUND TIMER IDLE:") {
		value >> this->_TIMER_SOUND_IDLE;
	} else if(parameter.str() == "LAUNCH MIN VEL:") {
		value >> this->_LAUNCH_MIN_VEL;
	} else if(parameter.str() == "LAUNCH MAX VEL:") {
		value >> this->_LAUNCH_MAX_VEL;
	} else if(parameter.str() == "LAUNCH MIN ANGLE:") {
		value >> this->_LAUNCH_MIN_ANGLE;
	} else if(parameter.str() == "LAUNCH MAX ANGLE:") {
		value >> this->_LAUNCH_MAX_ANGLE;
	} else if(parameter.str() == "RATE OF FIRE:") {
		value >> this->_RoF;
	} else if(parameter.str() == "ORIENTATION:") {
		if(value == "LEFT") _LAUNCH_LEFT_ORIENTATION = true;
		else _LAUNCH_LEFT_ORIENTATION = false;
	} else if(parameter.str() == "PULL LENGTH:") {
		value >> this->_LAUNCH_MAX_PULL_LENGTH;
	} else if(parameter.str() == "AMMO ARROW:") {
		bool use;
		value >> use;
		if(use) this->ammo.setArrowNormal(true);
	} else if(parameter.str() == "AMMO CANNONBALL:") {
		bool use;
		value >> use;
		if(use) this->ammo.setCannonBallFire(true);
	}

}


void GOSettings::saveLoadedValue(std::string parameter, std::string value) {


}