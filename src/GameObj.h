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
//#include "GameObjectManager.h"

//
//struct GOSettings {
//
//
//
//}
//


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

	enum OBJECT_TYPE { ATTACKER, DEFENDER, BULLET, STATIC, NONE};		// General object types
	const uint16 COLLISION_GROUP_GROUND;
	const uint16 COLLISION_GROUP_NPC_BULLET;
	const uint16 COLLISION_GROUP_NPC_ATTACKER;
	const uint16 COLLISION_GROUP_PC_BULLET;
	const uint16 COLLISION_GROUP_PC_DEFENDER;

	// Accessor functions
	void setName(std::string str) { name = str; }
	std::string getName() { return name; }
//	void setPosX(float x) { posX = x; body->}	
//	void setPosY(float y) { posY = y; }
//	float getPosX() { return posX; }
//	float getPosY() { return posY; }
	void setInitLinearVelocity(b2Vec2 vel) { initLinearVelocity = vel; }
	b2Vec2 getInitLinearVelocity() { return initLinearVelocity; }
	void setCurrentLinearVelocity(b2Vec2 vel) { linearVelocity = vel; }
	b2Vec2 getCurrentLinearVelocity() { return linearVelocity; }
	void setInitVecAngle(float theta) { initAngle = Util::normAngle(theta); } //recalculate(); }   // set vector angle of movement (degrees)
	float getInitVecAngle() { return initAngle; };
	void setCurrentVecAngle(float theta) { angle = Util::normAngle(theta);  } //recalculate(); }   // set vector angle of movement (degrees)
	float getCurrentVecAngle() { return angle; };
	void setVelocityMax(float meterPerSec) { velocityMax = meterPerSec;}   // meters per second
	float getVelocityMax() { return velocityMax; };
	void setHP(int num) { hpCur = num; }
	int getHP() { return hpCur; }
	void setHPMax(int num) { hpMax = num; }
	int getHPMax() { return hpMax; }
	void setArmor(int num) { arCur = num; }
	int getArmor() { return arCur; }
	void setArmorMax(int num) { arMax = num; }
	int getArmorMax() { return arMax; }
	void setTextWidth(float width) { textWidth = width; }
	float getTextWidth() { return textWidth; }
	void setTextHeight(float height) { textHeight = height; }
	float getTextHeight() { return textHeight; }
	OBJECT_TYPE getType() { return objType; }					// Generic object type
	void setType(OBJECT_TYPE type) { objType = type; }			// Generic object type
	Settings::OBJECT_TYPE getTypeID() { return objID; }					// specific object type
	void setTypeID(Settings::OBJECT_TYPE typeID) { objID = typeID; }			// Specific object type
	void setTeam(bool bNPC = true) { npcTeam = bNPC; }			
	bool isNPC() { return npcTeam; }
	void setDamage(int damage) { damage_basic = damage; }
	int getDamage() { return damage_basic; }
	void setRangeDamage(int damage) { damage_range = damage; }
	int getRangeDamage() { return damage_range; }
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

protected:
	std::string name;	// in game name of object
//	float posX, posY;
	b2Vec2	linearVelocity;	// Initial Velocity (meters per sec)
	b2Vec2	initLinearVelocity;	// Initial Velocity (meters per sec)
	float velocityMax;		// meters per second
	float initAngle;		// 0 = right  90 = up 180 = left   
	float angle;		// 0 = right  90 = up 180 = left   
//	float velX;
//	float velY;
	int hpCur;			// current hitpoints
	int hpMax;			// max hitpoints
	int arCur;			// current armor
	int arMax;			// Max Armor
	int damage_basic;			// base amount of damage from 
	int damage_range;			// amount of ranged attack damage
	float textWidth;	// TEMP? This might not be the right way to do this.  Texture Width
	float textHeight;	// TEMP? This might not be the right way to do this.  Texture Height
	float density;
	float friction;

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

	Util::Color DEF_DRAW_COLOR;
	Util::Color CONTACT_DRAW_COLOR;

	// BOX2D
	OBJECT_TYPE objType;
	void setupB2D(double x, double y);
	bool npcTeam;
	int contacts;					// Number of contacts



	std::list<GameObj*> enemies;				// Track enemies we're in contact with;


//	image texture;		// Texture image ?
	GLuint textureID;


	// Sound Source ID
	Settings::OBJECT_TYPE objID;				// Specific object type ID
	unsigned int soundSourceID;



	// todo - Weapon
	std::vector<unsigned int> ammo;
//	void *weapon;
};

