#pragma once

/*
	This is the base class for all game objects

*/
// Open GL
#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

// Open AL
#include "openal\include\al.h"

// STL
#include <sstream>
#include<string>
#include <vector>
#include <list>

// Box 2d
#include <Box2D.h>

// My Stuff
#include "Util.h"
#include "GLText.h"
#include "settings.h"
#include "TextureLoader.h"
#include "SoundManager.h"
#include "Performance_Counter.h"
#include "GOSettings.h"



class GameObj
{
public:
	GameObj(Settings *settings, double x, double y);
	~GameObj(void);
	
	// Timer intervals inbetween playing repeated sfx
	float TIMER_SOUND_MOVE;
	float TIMER_SOUND_MELEE;
	float TIMER_SOUND_RANGED;
	float TIMER_SOUND_DAMAGED;
	float TIMER_SOUND_DEATH;
	float TIMER_SOUND_IDLE;

//	enum OBJECT_TYPE { ATTACKER, DEFENDER, BULLET, STATIC, NONE};		// General object types
	//const uint16 COLLISION_GROUP_GROUND;
	//const uint16 COLLISION_GROUP_NPC_BULLET;
	//const uint16 COLLISION_GROUP_NPC_ATTACKER;
	//const uint16 COLLISION_GROUP_PC_BULLET;
	//const uint16 COLLISION_GROUP_PC_DEFENDER;

//	// Accessor functions
	void setName(std::string str) { goSettings._name = str; }
	std::string getName() { return goSettings._name; }
//	void setPosX(float x) { posX = x; body->}	
//	void setPosY(float y) { posY = y; }
//	float getPosX() { return posX; }
//	float getPosY() { return posY; }
	void setInitLinearVelocity(b2Vec2 vel) { goSettings._initLinearVelocity = vel; }
	b2Vec2 getInitLinearVelocity() { return goSettings._initLinearVelocity; }
	void setCurrentLinearVelocity(b2Vec2 vel) { goSettings._linearVelocity = vel; }
	b2Vec2 getCurrentLinearVelocity() { return goSettings._linearVelocity; }
	void setInitVecAngle(float theta) { goSettings._initAngle = Util::normAngle(theta); } //recalculate(); }   // set vector angle of movement (degrees)
	float getInitVecAngle() { return goSettings._initAngle; };
	void setCurrentVecAngle(float theta) { goSettings._angle = Util::normAngle(theta);  } //recalculate(); }   // set vector angle of movement (degrees)
	float getCurrentVecAngle() { return goSettings._angle; };
	void setVelocityMax(float meterPerSec) { goSettings._velocityMax = meterPerSec;}   // meters per second
	float getVelocityMax() { return goSettings._velocityMax; };
	void setHP(int num) { goSettings._hpCur = num; }
	int getHP() { return goSettings._hpCur; }
	void setHPMax(int num) { goSettings._hpMax = num; }
	int getHPMax() { return goSettings._hpMax; }
	void setArmor(int num) { goSettings._arCur = num; }
	int getArmor() { return goSettings._arCur; }
	void setArmorMax(int num) { goSettings._arMax = num; }
	int getArmorMax() { return goSettings._arMax; }
	void setTextWidth(float width) { goSettings._textWidth = width; }
	float getTextWidth() { return goSettings._textWidth; }
	void setTextHeight(float height) { goSettings._textHeight = height; }
	float getTextHeight() { return goSettings._textHeight; }
	Settings::OBJECT_TYPE getType() { return goSettings._objType; }					// Generic object type
	void setType(Settings::OBJECT_TYPE type) { goSettings._objType = type; }			// Generic object type
	Settings::OBJECT_ID getTypeID() { return goSettings._objTypeID; }					// specific object type
	void setTypeID(Settings::OBJECT_ID typeID) { goSettings._objTypeID = typeID; }			// Specific object type
	void setTeam(bool bNPC = true) { goSettings._npcTeam = bNPC; }			
	bool isNPC() { return goSettings.isNPC(); }
//	void setDamage(int damage) { damage_basic = damage; }
//	int getDamage() { return damage_basic; }
//	void setRangeDamage(int damage) { damage_range = damage; }
//	int getRangeDamage() { return damage_range; }
	bool isAlive();
	virtual bool activate(b2Vec2 mouse) =0;	// dummy stub - override for launcher objects.
	virtual bool isActivated(bool reset) =0;	// dummy stub - override for launcher objects.
	virtual void draw(b2Vec2 mouse);						// draw the object on screen
//	virtual void launch(void* go) { }			//stub 

	// update functions
	virtual void attack(GameObj *enemy, SoundManager &sm);						// automatic attack function
	virtual void death(SoundManager &sm);						// death sequnce
	virtual void damage(int amount, SoundManager &sm);			// damage taken function
	virtual void move(SoundManager &sm);						// automatic move function (using vector quantities)
	virtual void update(SoundManager &sm);					// Main update function
	// Virtual Specialization Calls for derived class specific behavior
	// return TRUE to override default routine
	virtual bool attackSpecial(GameObj *enemy, SoundManager &sm) { return false; };						// automatic attack function
	virtual bool deathSpecial(SoundManager &sm) { return false; };						// death sequnce
	virtual bool damageSpecial(int amount, SoundManager &sm) { return false; };			// damage taken function
	virtual bool moveSpecial(SoundManager &sm) { return false; };						// automatic move function (using vector quantities)
	virtual bool updateSpecial(SoundManager &sm) { return false; };					// Main update function

	// Box2d
	b2Body *body;
	void addContact(GameObj *enemy);
	void subContact(GameObj *enemy);
	void addEnemy(GameObj *enemy, bool ranged = false);
	void removeEnemy(GameObj *enemy, bool ranged = false);
	bool cleanEnemiesList();
	b2Vec2 getPos() { return body->GetPosition(); }
	b2Filter getFixtureCollisionFilter();

	// Sound
	void setSoundSourceID(unsigned int id) { soundSourceID = id; }

	// Settings!
	GOSettings goSettings;

	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	void loadObject(std::string datFilename, double x, double y);

protected:
//	std::string name;	// in game name of object
////	float posX, posY;
//	b2Vec2	linearVelocity;	// Initial Velocity (meters per sec)
//	b2Vec2	initLinearVelocity;	// Initial Velocity (meters per sec)
//	float velocityMax;		// meters per second
//	float initAngle;		// 0 = right  90 = up 180 = left   
//	float angle;		// 0 = right  90 = up 180 = left   
////	float velX;
////	float velY;
//	int hpCur;			// current hitpoints
//	int hpMax;			// max hitpoints
//	int arCur;			// current armor
//	int arMax;			// Max Armor
//	int damage_basic;			// base amount of damage from 
//	int damage_range;			// amount of ranged attack damage
//	float textWidth;	// TEMP? This might not be the right way to do this.  Texture Width
//	float textHeight;	// TEMP? This might not be the right way to do this.  Texture Height
//	float density;
//	float friction;

	// TIMERS
	double elapsedTime;			// REMOVE?
	Performance_Counter t_move;	// timer for move sfx intervals
	Performance_Counter t_melee;	// timer for move sfx intervals
	Performance_Counter t_ranged;	// timer for move sfx intervals
	Performance_Counter t_damaged;	// timer for move sfx intervals
	Performance_Counter t_death;	// timer for move sfx intervals
	Performance_Counter t_idle;	// timer for move sfx intervals


	void recalculate();

	Settings *settings;			// Contains window x, y, z and handles

	GLText text;

	//Util::Color DEF_DRAW_COLOR;
	//Util::Color CONTACT_DRAW_COLOR;

	// BOX2D
//	OBJECT_TYPE objType;
	void setupB2D(double x, double y);
//	bool npcTeam;
	int contacts;					// Number of contacts
	bool groundContact;				// toggle true when collision with ground occurs.


	std::list<GameObj*> enemies;				// Track enemies we're in contact with;


//	image texture;		// Texture image ?
	GLuint textureID;


	// Sound Source ID
//	Settings::OBJECT_ID objID;				// Specific object type ID
	unsigned int soundSourceID;



	// todo - Weapon
//	std::vector<unsigned int> ammo;
//	void *weapon;
};

