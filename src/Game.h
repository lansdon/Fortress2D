/*
	Game class
	By Lansdon Page
	11/7/2011
	
	- This is the main public class that manages the entire game.


*/


#pragma once


// Open GL Stuffs
#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\freeglut.h>

// STL etc
#include <sstream>
#include<string>
#include <iomanip>
#include <vector>
#include <map>

// Box 2d
#include <Box2D\Box2D.h>

// My stuffs
#include "Performance_Counter.h"	// Timer for calculating frame intervals (milliseconds)
#include "GameObj.h"
#include "GLText.h"
#include "settings.h"
#include "Input.h"
#include "Fort.h"
#include "GUIButtonMenu.h"
//#include "MyContactListener.h"
#include "GameObjectManager.h"
#include "LevelLoader.h"
#include "SoundManager.h"
#include "Launcher.h"


class MyContactListener : public b2ContactListener {

	void MyContactListener::BeginContact(b2Contact* contact) {
  
		//check if fixture A was a GameObj
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		GameObj *objA = static_cast<GameObj*> ( bodyUserDataA );
		GameObj *objB = static_cast<GameObj*> ( bodyUserDataB );
		
		// No valid collision objects
		if(bodyUserDataA == NULL && bodyUserDataB == NULL) return;	

		// GROUND COLLISION
		if(bodyUserDataA == NULL || bodyUserDataB == NULL) {
			if(bodyUserDataA != NULL) {
				if(objA->getType() == Settings::OBJ_T_BULLET) {
					objA->addContact(NULL);
				}
			}
			if(bodyUserDataB != NULL) {
				if(objB->getType() == Settings::OBJ_T_BULLET) {
					objB->addContact(NULL);
				}
			}
			return;
		}

//		GameObj::OBJECT_TYPE ot;

		// Colliding PC VS NPC OBjects
		if(objA->goSettings.isNPC() != objB->goSettings.isNPC()) {			// Check if objects are on opposite team.
			objA->addContact(objB);
			objB->addContact(objA);
		}
	}
  
	void MyContactListener::EndContact(b2Contact* contact) {
  
		//check if fixture A was a GameObj
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		if ( bodyUserDataA && bodyUserDataB ) {
			static_cast<GameObj*>( bodyUserDataA )->subContact(static_cast<GameObj*>( bodyUserDataB ));
			static_cast<GameObj*>( bodyUserDataB )->subContact(static_cast<GameObj*>( bodyUserDataA ));
		}
 	}
};



class Game
{
public:
	Game();

	~Game(void);

	bool initGL();

	bool update(); // Main "Loop" function  (the loop actually comes from winMain)
	void Game::draw();
	int getScreenWidth() { return settings.width(); }
	int getScreenHeight() { return settings.height(); }
	int getScreenDepth() { return settings.depth(); }

	// Input
	Input in;


private:

	enum GAME_STATE { MENU, ACTIVE, PAUSED };

	// Box2d
	// Ground Object
	b2BodyDef groundBodyDef;
	b2Body* groundBody;				// Ground body
	b2PolygonShape groundBox;		// Ground box
	MyContactListener contactListener;				// Collision Callback

	// Game / Level Vars
	int lvl;					// current game level
	int lvl_time_length;		// total timer
	int lvl_time_remaining;		// remaining timer
	void updateAttackers();
	//void updateDefenders();
//	void Game::loadLevel(int level=0);

	// TIMERS
	int timeStepCount;
	double frameElapsedTime;			// Amount of time passed since last frame
	double lastFrameElapsedTime;		// previous frame time for draw function reference
//	double t;
//	const double dt;
	double accumulator;
//	double previousState;
//	double currentState;
	Performance_Counter Timer;	// timer object for tracking high resolution time inbetween updates
	Performance_Counter leftBtnTimer;	// timer object for tracking high resolution time inbetween updates
	float LEFT_BUTTON_INTERVAL;			// amount of time inbetween single mouse clicks
	std::map<std::string, Performance_Counter> timers;
	Performance_Counter t_lvlSpawn;	// Timer for tracking spawn rate of attackers
	double CREATURE_SPAWNER_INTERVAL;

	float SCOREBOARD_HEIGHT;

	// Player Vars
	int score;
	int money;

	// Draw Functions //
	void drawMenu();			// draws the main menu
	void drawBackground();		// draws the level background
	void drawScoreboard();
	void drawFort();			// draws the player placed objects that make up the fortress

	// Open GL Functions/vars
	GLText text;
	Util::Color DEF_BG; // Background color
	Util::Color DEF_DRAW_COLOR; // draw color
	void glEnable2D();
	void glDisable2D();

	// User Input
	void processInput();
	void keyPressed(unsigned char key, int x, int y);
	void Game::specialKeyPressed(int key, int x, int y);

	// TEMP - Testing game objects - This will eventually be managed in containers
	void Game::makeAttacker();


	Settings settings;
	GameObjectManager* go;
	SoundManager sm;
	LevelLoader level;

	// Fort
	Fort fort;

	GUIButtonMenu *fortMenu;
	void processFortMenuButton();
	void setupFortMenu();
	std::string getFortButtonLabel(int row, int col);

	// Game Objects
	Launcher *activeLauncher;						// Currently Selected Launcher Object
	bool Game::activateGO(Vector3 mouse);			// Searches for a Launcher being activated
	void Game::doLaunch();					// Launch an object from the currently selected launch object


};




//
//
//void MyContactListener::BeginContact(b2Contact* contact) {
//  
//	//check if fixture A was a GameObj
//	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//	if ( bodyUserData )
//		static_cast<GameObj*>( bodyUserData )->addContact();
//  
//	//check if fixture B was a GameObj
//	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//	if ( bodyUserData )
//		static_cast<GameObj*>( bodyUserData )->addContact();
//  
//}
//  
//void MyContactListener::EndContact(b2Contact* contact) {
//  
//	//check if fixture A was a GameObj
//	void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
//	if ( bodyUserData )
//	static_cast<GameObj*>( bodyUserData )->subContact();
//  
//	//check if fixture B was a GameObj
//	bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
//	if ( bodyUserData )
//	static_cast<GameObj*>( bodyUserData )->subContact();
//  
//}