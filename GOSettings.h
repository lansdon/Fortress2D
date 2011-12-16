#pragma once

// STL + C++ stuffs
#include<string>
#include<fstream>

// Box 2d
#include<Box2D\Box2D.h>

// My Stuff!
#include"Performance_Counter.h"
#include"Util.h"
#include"Settings.h"
#include"AmmoTypes.h"

class GOSettings
{
public:
	GOSettings(void);
	GOSettings(GOSettings &settings);
	~GOSettings(void);

	bool loadFromFile(std::string file);
	void saveExampleFile();
	void parseFileData(std::stringstream &parameter, std::stringstream &value);
	void saveLoadedValue(std::string parameter, std::string value);
	bool isValidParameter(std::stringstream &parameter);

	void setBasicSettings(
		std::string name="notset",	// in game name of object
		int hpCur=0,				// current hitpoints
		int hpMax=0,				// max hitpoints
		int arCur=0,				// current armor
		int arMax=0,				// Max Armor
		int damage_melee=0,			// base amount of damage from 
		int damage_ranged=0,			// amount of ranged attack damage // This comes from ammo!?
		bool npcTeam=false			// TRUE = NPC, FALSE = PC
		) {
			_name = name;						// in game name of object
			_hpCur = hpCur;						// current hitpoints
			_hpMax = hpMax;						// max hitpoints
			_arCur = arCur;						// current armor
			_arMax = arMax;						// Max Armor
			_damage_melee = damage_melee;		// base amount of damage from 
			_damage_ranged = damage_ranged;		// amount of ranged attack damage
			_npcTeam = npcTeam;					// TRUE = NPC, FALSE = PC
	}

	void setPhysicalSettings(
		b2Vec2 initPosition = b2Vec2(0, 0),		// (Pixel/screen loc) initPosition (passed to b2body) DO NOT USE DIRECTLY
		b2Vec2	initLinearVelocity = b2Vec2(0, 0),	// Initial Velocity (meters per sec)
		b2Vec2	linearVelocity = b2Vec2(0.0, 0.0),	// Current Velocity (meters per sec)
		float velocityMax = 0.0,		// meters per second
		float initAngle = 0.0,		// 0 = right  90 = up 180 = left   
		float angle = 0.0,		// 0 = right  90 = up 180 = left   
		float density = 1.0,
		float friction = 0.0,
		float textWidth = 1.0,	// (METERS) TEMP? This might not be the right way to do this.  Texture Width
		float textHeight = 1.0	// (METERS) TEMP? This might not be the right way to do this.  Texture Height
		) {
		_initPosition = initPosition;		// (Pixel/screen loc) initPosition (passed to b2body) DO NOT USE DIRECTLY
		_initLinearVelocity = initLinearVelocity;	// Initial Velocity (meters per sec)
		_linearVelocity = linearVelocity;	// Current Velocity (meters per sec)
		_velocityMax = velocityMax;		// meters per second
		_initAngle = initAngle;		// 0 = right  90 = up 180 = left   
		_angle = angle;		// 0 = right  90 = up 180 = left   
		_density = density;
		_friction = friction;
		_textWidth = textWidth;	// (METERS) TEMP? This might not be the right way to do this.  Texture Width
		_textHeight = textHeight;	// (METERS) TEMP? This might not be the right way to do this.  Texture Height
	}

	void setSoundTimers(
		float TIMER_SOUND_MOVE = 3.0,
		float TIMER_SOUND_MELEE = 1.0,
		float TIMER_SOUND_RANGED = 1.0,
		float TIMER_SOUND_DAMAGED = 2.0,
		float TIMER_SOUND_DEATH = 5.0,
		float TIMER_SOUND_IDLE = 10.0
		) {
		_TIMER_SOUND_MOVE =_TIMER_SOUND_MOVE;
		_TIMER_SOUND_MELEE = TIMER_SOUND_MELEE;
		_TIMER_SOUND_RANGED = TIMER_SOUND_RANGED;
		_TIMER_SOUND_DAMAGED = TIMER_SOUND_DAMAGED;
		_TIMER_SOUND_DEATH = TIMER_SOUND_DEATH;
		_TIMER_SOUND_IDLE = TIMER_SOUND_IDLE;
	}

	void setDefColors (	
		Util::Color DEF_DRAW_COLOR = Util::Color(1, 1, 1, 1), 
		Util::Color CONTACT_DRAW_COLOR = Util::Color(1, 0, 0, 1) ) {
		_DEF_DRAW_COLOR = DEF_DRAW_COLOR;
		_CONTACT_DRAW_COLOR = CONTACT_DRAW_COLOR;
	}

	void setObjectTypes(
		Settings::OBJECT_TYPE objType = Settings::OBJ_T_NONE, 
		Settings::OBJECT_ID objTypeID = Settings::OBJ_ID_NONE) {
		_objType = objType;
		_objTypeID = objTypeID;
	}

	void setLauncherSettings(
		float LAUNCH_MIN_VEL = 0,			// Lower bounds of launch velocity meters/sec
		float LAUNCH_MAX_VEL = 0,			// Upper bounds of launch velocity meters/sec
		bool LAUNCH_LEFT_ORIENTATION = 0, // true = facing left    false = facing right
		int LAUNCH_MIN_ANGLE = 0,			// MIN angle allowed (0 = horizontal plane. POS = up, neg = down.
		int LAUNCH_MAX_ANGLE = 0,
		int LAUNCH_MAX_PULL_LENGTH = 0,		// (max length a user can pull on launcher to achieve max launch velocity. (pixels)
		double RateOfFire = 0
		) {
			_LAUNCH_MIN_VEL = LAUNCH_MIN_VEL;			// Lower bounds of launch velocity meters/sec
			_LAUNCH_MAX_VEL = LAUNCH_MAX_VEL;			// Upper bounds of launch velocity meters/sec
			_LAUNCH_LEFT_ORIENTATION = LAUNCH_LEFT_ORIENTATION; // true = facing left    false = facing right
			_LAUNCH_MIN_ANGLE = LAUNCH_MIN_ANGLE;			// MIN angle allowed (0 = horizontal plane. POS = up, neg = down.
			_LAUNCH_MAX_ANGLE = LAUNCH_MAX_ANGLE;
			_LAUNCH_MAX_PULL_LENGTH = LAUNCH_MAX_PULL_LENGTH;		// (max length a user can pull on launcher to achieve max launch velocity. (pixels)
			_RoF = RateOfFire;
		}

	// Returns reference to the ammo struct where ammo types can be toggled on/off
	AmmoTypes &getAmmoTypes() { return ammo; }


	// Accessor functions
	void setName(std::string str) { _name = str; }
	std::string getName() { return _name; }
	void setInitPos(b2Vec2 initPos) { this->_initPosition = initPos; }	
	b2Vec2 getInitPosX() { return _initPosition; }
	void setInitLinearVelocity(b2Vec2 vel) { _initLinearVelocity = vel; }
	b2Vec2 getInitLinearVelocity() { return _initLinearVelocity; }
	void setCurrentLinearVelocity(b2Vec2 vel) { _linearVelocity = vel; }
	b2Vec2 getCurrentLinearVelocity() { return _linearVelocity; }
	void setInitVecAngle(float theta) { _initAngle = Util::normAngle(theta); } //recalculate(); }   // set vector angle of movement (degrees)
	float getInitVecAngle() { return _initAngle; };
	void setCurrentVecAngle(float theta) { _angle = Util::normAngle(theta);  } //recalculate(); }   // set vector angle of movement (degrees)
	float getCurrentVecAngle() { return _angle; };
	void setVelocityMax(float meterPerSec) { _velocityMax = meterPerSec;}   // meters per second
	float getVelocityMax() { return _velocityMax; };
	void setHP(int num) { _hpCur = num; }
	int getHP() { return _hpCur; }
	void setHPMax(int num) { _hpMax = num; }
	int getHPMax() { return _hpMax; }
	void setArmor(int num) { _arCur = num; }
	int getArmor() { return _arCur; }
	void setArmorMax(int num) { _arMax = num; }
	int getArmorMax() { return _arMax; }
	void setTextWidth(float width) { _textWidth = width; }
	float getTextWidth() { return _textWidth; }
	void setTextHeight(float height) { _textHeight = height; }
	float getTextHeight() { return _textHeight; }
	Settings::OBJECT_TYPE getType() { return _objType; }					// Generic object type
	void setType(Settings::OBJECT_TYPE type) { _objType = type; }			// Generic object type
	Settings::OBJECT_ID getTypeID() { return _objTypeID; }					// specific object type
	void setTypeID(Settings::OBJECT_ID typeID) { _objTypeID = typeID; }			// Specific object type
	void setTeam(bool bNPC = true) { _npcTeam = bNPC; }			
	bool isNPC() { return _npcTeam; }
	void setDamage(int damage) { _damage_melee = damage; }
	int getDamage() { return _damage_melee; }
	void setRangeDamage(int damage) { _damage_ranged = damage; }
	int getRangeDamage() { return _damage_ranged; }

	void setTextureFile(std::string fname) {_textureFilename = fname; } 
	std::string getTextureFilename() { return _textureFilename; }

// VARIABLES **************************************************************************



	// Basic Settings
	std::string _name;	// in game name of object
	int _hpCur;			// current hitpoints
	int _hpMax;			// max hitpoints
	int _arCur;			// current armor
	int _arMax;			// Max Armor
	int _damage_melee;			// base amount of damage from 
	int _damage_ranged;			// amount of ranged attack damage
	bool _npcTeam;				// TRUE = NPC, FALSE = PC

	// Object Type and Object ID (specific type) used for collision and other processing
	Settings::OBJECT_TYPE _objType;
	Settings::OBJECT_ID _objTypeID;

	// Position + Physics
	b2Vec2 _initPosition;		// (Pixel/screen loc) initPosition (passed to b2body) DO NOT USE DIRECTLY
	b2Vec2	_initLinearVelocity;	// Initial Velocity (meters per sec)
	b2Vec2	_linearVelocity;	// Current Velocity (meters per sec)
	float _velocityMax;		// meters per second
	float _initAngle;		// 0 = right  90 = up 180 = left   
	float _angle;		// 0 = right  90 = up 180 = left   
	float _density;
	float _friction;


	// Texture Dimensions:
	// Primitive Collision Box Dimensions (also used for basic texture placement + b2d body dimensions)
	float _textWidth;	// (METERS) TEMP? This might not be the right way to do this.  Texture Width
	float _textHeight;	// (METERS) TEMP? This might not be the right way to do this.  Texture Height
	std::string _textureFilename;

	// Timer intervals inbetween playing repeated sfx
	float _TIMER_SOUND_MOVE;
	float _TIMER_SOUND_MELEE;
	float _TIMER_SOUND_RANGED;
	float _TIMER_SOUND_DAMAGED;
	float _TIMER_SOUND_DEATH;
	float _TIMER_SOUND_IDLE;

	// Default Draw Colors
	Util::Color _DEF_DRAW_COLOR;
	Util::Color _CONTACT_DRAW_COLOR;


	////////////////////////////////////////
	// Launcher (derived class)  (ignore these for non-launcher objects)  // this may get moved to a seperate settings class
	////////////////////////////////////////
	float _LAUNCH_MIN_VEL;			// Lower bounds of launch velocity meters/sec
	float _LAUNCH_MAX_VEL;			// Upper bounds of launch velocity meters/sec
	bool _LAUNCH_LEFT_ORIENTATION; // true = facing left    false = facing right
	int _LAUNCH_MIN_ANGLE;			// MIN angle allowed (0 = horizontal plane. POS = up, neg = down.
	int _LAUNCH_MAX_ANGLE;
	int _LAUNCH_MAX_PULL_LENGTH;		// (max length a user can pull on launcher to achieve max launch velocity. (pixels)

	// Variables
//	float launchAngle;		// User defined current launch angle
//	float launchVelocity;		// Speed the ammo is launched at
//	bool activated;			// true if user is currently clicking on the launcher

	// Timer
//	Performance_Counter launchTimer;			// Rate of Fire in seconds

	// Ammo Types
	AmmoTypes ammo;

	// Rate of Fire
	double _RoF;
};

