#pragma once

/*
	This is the base class for all game objects

*/
#include <sstream>
#include<string>
#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library

#include <string>
#include "Util.h"
#include "GLText.h"
#include "WinParems.h"
#include <Box2D\Box2D.h>
#include <vector>
#include <list>
#include "TextureLoader.h"





class GameObj
{
public:
	GameObj(WinParems *parems, double x, double y);
	~GameObj(void);
	
	enum OBJECT_TYPE { ATTACKER, DEFENDER, BULLET, STATIC, NONE};		// General object types
//	enum OBJECT_SUB_TYPE { MONSTER, WALL, 

	// Accessor functions
	void setName(std::string str) { name = str; }
	std::string getName() { return name; }
//	void setPosX(float x) { posX = x; body->}	
//	void setPosY(float y) { posY = y; }
//	float getPosX() { return posX; }
//	float getPosY() { return posY; }
	//void setVecAngle(float theta) { angle = theta; recalculate(); }   // set vector angle of movement (degrees)
	//float getVecAngle() { return angle; };
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

//	void setCoordDepth(int *z) { COORD_DEPTH = z; }
//	void setGLObj(HDC *hDC, HWND *hWnd) { winParems.setHDC(hDC); winParems.setHWND(hWnd); } // pass main windown handle and hardware device context

	// update functions
	void update(double elapsedTime = 0);					// Main update function
	void move();						// automatic move function (using vector quantities)
	void attack(GameObj *enemy);						// automatic attack function
	void death();						// death sequnce
	void damage(int amount);			// damage taken function

	// Box2d
	b2Body *body;
	void addContact(GameObj *enemy);
	void subContact(GameObj *enemy);
	void addEnemy(GameObj *enemy, bool ranged = false);
	void removeEnemy(GameObj *enemy, bool ranged = false);
	bool cleanEnemiesList();

protected:
	std::string name;	// in game name of object
//	float posX, posY;
	float velocityMax;		// pixels per second
//	float angle;		// 0 = right   180 = left   90 = up
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

	double elapsedTime;

	void draw();						// draw the object on screen

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

	std::list<GameObj*> enemies;				// Track enemies we're in contact with;


//	image texture;		// Texture image ?
	GLuint textureID;


	// todo - // Soundbank

	// todo - Weapon


};

