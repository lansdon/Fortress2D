#pragma once

#include <list>



#include "GameObj.h"
// Object Derived Classes
#include "GOArcher.h"
#include "GOArcherTower.h"
//#include "GOBarbarian.h"
//#include "GOCatapult.h"
//#include "GOFence.h"
//#include "GOMageTower.h"
//#include "GOMote.h"
//#include "GOOilTower.h"
//#include "GOSeigeEngine.h"
#include "GOStoneWall.h"
//#include "GOWarDog.h"
//#include "GOWoodWall.h"
#include "GOAArrow.h"


#include "settings.h"
#include "SoundManager.h"

/*
	The purpose of the object manager is to maintain all game objects that are ever created.
	Creation and Destruction is always done through this class.

*/
struct GameObjParems {
	std::string name;
	int hitpoints;
	int armor;
	Vector3 position;
	double angle;
	int damage;
	int rangeDamage;
	int ObjectType;
	bool NPCTeam;
	bool dynamicBody;
	Vector3 Position;
	double linearVel;
	double texWidth;
	double texHeight;
	double density;
	double friction;
};

class GameObjectManager
{
public:
	GameObjectManager(Settings *settings, SoundManager &soundManager);
	~GameObjectManager();
	GameObj* makeWarDog(double x, double y);
	GameObj* makeBarbarian(double x, double y);
	GameObj* makeArcher(double x, double y);
	//GameObj* makeSeigeEngine(double x, double y);
	//GameObj* makeFence(double x, double y);
	//GameObj* makeMote(double x, double y);
	//GameObj* makeWoodWall(double x, double y);
	GameObj* makeStoneWall(double x, double y);
	GameObj* makeArcherTower(double x, double y);
	//GameObj* makeMageTower(double x, double y);
	//GameObj* makeOilTower(double x, double y);
	//GameObj* makeCatapult(double x, double y);

	// AMMO
	GameObj* makeArrow(double x, double y, bool bNPCTeam);

	std::list<GameObj*>::iterator destroyObject(GameObj *obj2Kill);

	void updateDefenders();
	void updateAttackers();
	void drawAll(b2Vec2 mouse);

	std::list<GameObj*> &getAttackers() { return attackers; }
	std::list<GameObj*> &getDefenders() { return defenders; }

	void setSettings(Settings *settings) { this->settings = settings; }

private:

	// NPC ATTACKER OBJECTS
	std::list<GameObj*> attackers;

	// PC DEFENDER OBJECTS
	std::list<GameObj*> defenders;

	void addObject(GameObj *newObj); // Adds object to appropriate tracking list
//	bool removeObject(GameObj *deadObj);

	void resetAttackers();

	Settings *settings;

	SoundManager &sm;

};

