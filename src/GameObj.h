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
#include "WinParems.h"
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
	GameObj(WinParems *parems, double x, double y);
	~GameObj(void);
	
	// Timer intervals inbetween playing repeated sfx
	float TIMER_SOUND_MOVE;
	float TIMER_SOUND_MELEE;
	float TIMER_SOUND_RANGED;
	float TIMER_SOUND_DAMAGED;
	float TIMER_SOUND_DEATH;
	float TIMER_SOUND_IDLE;

	enum OBJECT_TYPE { ATTACKER, DEFENDER, BULLET, STATIC, NONE};		// General object types
	const int16 COLLISION_GROUP_GROUND;
	const int16 COLLISION_GROUP_NPC_BULLET;
	const int16 COLLISION_GROUP_NPC_ATTACKER;
	const int16 COLLISION_GROUP_PC_BULLET;
	const int16 COLLISION_GROUP_PC_DEFENDER;

	// Accessor functions
	void setName(std::string str) { name = str; }
	std::string getName() { return name; }
//	void setPosX(float x) { posX = x; body->}	
//	void setPosY(float y) { posY = y; }
//	float getPosX() { return posX; }
//	float getPosY() { return posY; }
	void setVecAngle(float theta) { angle = theta; } //recalculate(); }   // set vector angle of movement (degrees)
	float getVecAngle() { return angle; };
	void setVelocity(float meterPerSec) { velocityMax = meterPerSec;}   // meters per second
	float getVelocity() { return velocityMax; };
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
	OBJECT_TYPE getType() { return objType; }
	void setType(OBJECT_TYPE type) { objType = type; }
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
	void update(SoundManager &sm);					// Main update function
	void move(SoundManager &sm);						// automatic move function (using vector quantities)
	void attack(GameObj *enemy, SoundManager &sm);						// automatic attack function
	void death(SoundManager &sm);						// death sequnce
	void damage(int amount, SoundManager &sm);			// damage taken function

	// Box2d
	b2Body *body;
	void addContact(GameObj *enemy);
	void subContact(GameObj *enemy);
	void addEnemy(GameObj *enemy, bool ranged = false);
	void removeEnemy(GameObj *enemy, bool ranged = false);
	bool cleanEnemiesList();
	b2Vec2 getPos() { return body->GetPosition(); }

	// Sound
	void setSoundSourceID(unsigned int id) { soundSourceID = id; }

protected:
	std::string name;	// in game name of object
//	float posX, posY;
	float velocityMax;		// pixels per second
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

	WinParems *winParems;			// Contains window x, y, z and handles

	GLText text;

	Util::Color DEF_DRAW_COLOR;
	Util::Color CONTACT_DRAW_COLOR;

	// BOX2D
	OBJECT_TYPE objType;
	void setupB2D(double x, double y);
	bool npcTeam;
	int contacts;					// Number of contacts
	b2Filter getFixtureCollisionFilter();



	std::list<GameObj*> enemies;				// Track enemies we're in contact with;


//	image texture;		// Texture image ?
	GLuint textureID;


	// Sound Source ID
	WinParems::OBJECT_TYPE objID;				// Specific object type ID
	unsigned int soundSourceID;



	// todo - Weapon
	std::vector<unsigned int> ammo;
//	void *weapon;
};

