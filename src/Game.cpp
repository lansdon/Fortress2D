#include "Game.h"

//const b2Vec2 Game::gravity(0, -10);

Game::Game() {
	// Configure window parememter object (passed around to other classes)
	winParems.setDepth(-725);
	winParems.setHeight(600);
	winParems.setWidth(800);
	winParems.setFloor(20);
	winParems.setMid(winParems.width()/2);
	winParems.setTextures(true);				// TOGGLE TEXTURES OFF / ON

	DEF_BG.setColors(0, 0, 0, 0);				// Default background color = black
	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);		// def draw color = white
	
	lvl = 0;					// current game level
	lvl_time_length = 0;		// total timer
	lvl_time_remaining = 0;		// remaining timer
	
	// Timers
	timeStepCount=0;
//	t = 0.0;
//	dt = 0.01;
	accumulator = 0.0;
//	previousState = 0;
//	currentState = 0;

	frameElapsedTime = 0.0;		// elapsed time between frames

	LEFT_BUTTON_INTERVAL = .5;		// seconds between mouse clicks
	CREATURE_SPAWNER_INTERVAL = 6.0;	// Seconds between creature spawns

	// BOX2d Initialization
	winParems.getWorld()->SetContactListener(&contactListener);

	// STATIC GROUND LEVEL
	groundBodyDef.position.Set(winParems.mid(), winParems.floor()/2);
//	groundBodyDef.position.Set(0.0f, -winParems.height()/2);
	groundBody = winParems.getWorld()->CreateBody(&groundBodyDef);
	groundBox.SetAsBox(winParems.width(), winParems.floor()/2);
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Player Vars
	score = 0;
	money = 0;

	glEnable2D();			// REMOVE?

	activeLauncher = NULL;

	SCOREBOARD_HEIGHT = (winParems.height()/14);
	
	// Fort Menu Setup
	setupFortMenu();

	// Pass windows paremeters to child objects
	in.setWinParems(&winParems);
	text.setWinParems(&winParems);
	fort.setWinParems(&winParems);

	// Game Object Manager
	go = new GameObjectManager(&winParems, sm);

	// Initialization of objects
	fort.start();
}

//void Game::setGLObj(HDC *hDC, HWND *hWnd) { // pass main windown handle and hardware device context
//	winParems.setHDC(hDC); 
//	winParems.setHWND(hWnd); 
//
//	//// Pass windows paremeters to child objects
//	in.setWinParems(&winParems);
//	text.setWinParems(&winParems);
//	fort.setWinParems(&winParems);
//	fortMenu->setWinParems(&winParems);
//	go->setWinParems(&winParems);
//} 


Game::~Game(void) {
	glDisable2D();

	// Cleanup bodies and game objects
//	std::vector<GameObj*>::iterator it = attackerObj.begin();
//	while(it != attackerObj.end()) {
////		winParems.getWorld()->DestroyBody((*it)->body);
//		delete (*it);
//		++it;
//	}
//
	winParems.getWorld()->DestroyBody(groundBody);

	delete go;
	delete fortMenu;
}

bool Game::initGL() {

	sm.init();								// Sound Manager

	//// Pass windows paremeters to child objects
	in.setWinParems(&winParems);
	text.setWinParems(&winParems);
	fort.setWinParems(&winParems);
	fortMenu->setWinParems(&winParems);
	go->setWinParems(&winParems);
	return true;
}



void Game::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // Clear The Screen And The Depth Buffer
	glLoadIdentity();
	glEnable2D();

	// Draw Functions
	drawBackground();
	drawScoreboard();
	drawMenu();
	fort.draw(in.getMousePos());
	go->drawAll(b2Vec2(in.getMousePos().x(), in.getMousePos().y()));

	// Debug /////////////////////////////////////////////////////////////////////////////////////////////
	std::stringstream ss;
	ss << "Manager: Attackers=" << go->getAttackers().size() << " Defenders=" << go->getDefenders().size();
	text.text(ss, 10, 450, winParems.depth());

	std::stringstream ss2;
	ss2 << "Sound Manager: Sources=" << sm.getSourceCount() << " Buffers=" << sm.getBufferCount();
	text.text(ss2, 10, 425, winParems.depth());

	if(lastFrameElapsedTime != 0.0) {
		std::stringstream fps;
		fps << "FPS = " << (1 / lastFrameElapsedTime);				// Instant FPS
		fps << "step:" << timeStepCount;
		text.text(fps, 10, 5, winParems.depth()+10);

		// DEBUG
		std::stringstream ss;
		ss << "MOUSE x=" << in.getMousePos().x() << " Y=" << in.getMousePos().y();
		text.text(ss, in.getMousePos().x(), in.getMousePos().y(), winParems.depth());			
	}
	// End Debug /////////////////////////////////////////////////////////////////////////////////////////////

	glDisable2D();
	// Last step - swap buffers
	glutSwapBuffers();

}



// Main "Loop" function  (the loop actually comes from winMain)
bool Game::update() {

	// TEMP - Load an object for testing
	// To-do Need to add level loading
	if(!lvl) {
		lvl = 1;
		level.loadLevel(lvl);
		sm.loadSounds(level.getSpawnListTypes());
	}

	// Timer - Get elapsed time since last update
	Timer.Calculate_Ellapsed_Time();
	frameElapsedTime = Timer.TotalTime();
	accumulator += frameElapsedTime;	// tracks physics engine timestep
	lastFrameElapsedTime = frameElapsedTime;
	//if(frameElapsedTime > 0.25)
	//	frameElapsedTime = 0.25;

	// Physics Update - Box2d
	double ts = winParems.getTimeStep();
	while( accumulator >= ts ) {
		++timeStepCount;
		winParems.step();
		accumulator -= winParems.getTimeStep();
	}

	// Game Objects
	go->updateDefenders();
	updateAttackers();

	// Input
	processInput();

	// Draw Functions
	glutPostRedisplay();

	// END ! Last! - This timer reset should be at the very end of update function
	frameElapsedTime = 0.0;
	Timer.Reset(0.0);		// Start the timer to measure interval between updates

	return true;  
}


// Draw Main Menu
void Game::drawMenu() {
	fortMenu->draw();
}



// draws the level background
void Game::drawBackground() {		

	glLoadIdentity();
	glColor3f(DEF_DRAW_COLOR.r, DEF_DRAW_COLOR.g, DEF_DRAW_COLOR.b);
	
	// Draw ground plane
//	glTranslatef((GLfloat)0, (GLfloat)0, (GLfloat)winParems.depth());       // Move to 0,0 in bottom left corner of coord system
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2f(0, winParems.floor());              // Top Left
		glVertex2f(winParems.width(), winParems.floor());              // Top Right
		glVertex2f(winParems.width(), winParems.floor()-1);              // Bottom Right
		glVertex2f(0, winParems.floor()-1);              // Bottom Left
	glEnd();                            // Done Drawing The Quad

	// Mid Point
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2d(winParems.mid(), winParems.floor());              // Top Left
		glVertex2d(winParems.mid()+1, winParems.floor());              // Top Right
		glVertex2d(winParems.mid()+1, winParems.floor()-5);              // Bottom Right
		glVertex2d(winParems.mid(), winParems.floor()-5);              // Bottom Left
	glEnd();                            // Done Drawing The Quad

}


// Draw the scoreboard
void Game::drawScoreboard() {
	glLoadIdentity();
	glColor3f(DEF_DRAW_COLOR.r, DEF_DRAW_COLOR.g, DEF_DRAW_COLOR.b);
	
	// top line
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2d(0, winParems.height());              // Top Left
		glVertex2d(winParems.width(), winParems.height());              // Top Right
		glVertex2d(winParems.width(), winParems.height()-1);              // Bottom Right
		glVertex2d(0, winParems.height()-1);              // Bottom Left
	glEnd();                            // Done Drawing The Quad

	// bottom line
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2d(0, winParems.height()-SCOREBOARD_HEIGHT);              // Top Left
		glVertex2d(winParems.width(), winParems.height()-SCOREBOARD_HEIGHT);              // Top Right
		glVertex2d(winParems.width(), winParems.height()-SCOREBOARD_HEIGHT-1);              // Bottom Right
		glVertex2d(0, winParems.height()-SCOREBOARD_HEIGHT-1);              // Bottom Left
	glEnd();                            // Done Drawing The Quad

  // Display score:
	float sPosX = 30;
	float sPosY = winParems.height() - SCOREBOARD_HEIGHT/2;
	std::stringstream s1, s2, s3, s4;
	//r2 << std::fixed << std::setprecision(2); 
	//r3 << std::fixed << std::setprecision(2); 
	s4 << std::setprecision(0); 
	s1 << "Score: " << score;
	s2 << "Cash: " << money;
	s3 << "Level: " << lvl << std::endl;
	s4 << "Timer: " << lvl_time_remaining;
	text.text(s1, sPosX, sPosY, winParems.depth());
	text.text(s2, sPosX + (1*(winParems.width()/4)), sPosY, winParems.depth());
	text.text(s3, sPosX + (2*(winParems.width()/4)), sPosY, winParems.depth());
	text.text(s4, sPosX + (3*(winParems.width()/4)), sPosY, winParems.depth());
}


// draws the player placed objects that make up the fortress
void Game::drawFort() {		

}


void Game::glEnable2D() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, winParems.width(), 0, winParems.height());
//    glScalef(1, -1, 1);
//    glTranslatef(0, -winParems.height(), 0);
    glMatrixMode(GL_MODELVIEW);
}

void Game::glDisable2D() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}



// This function updates the attacking mobs / movement / collision / attacks
void Game::updateAttackers() {
	t_lvlSpawn.Calculate_Ellapsed_Time();	// Timer for tracking spawn rate of attackers
	if(t_lvlSpawn.TotalTime() >= CREATURE_SPAWNER_INTERVAL) {
		level.spawn(*go);
		t_lvlSpawn.Reset(0.0);
	}
	go->updateAttackers();
}


void Game::makeAttacker() {
	t_lvlSpawn.Calculate_Ellapsed_Time();
	if(t_lvlSpawn.TotalTime() >= CREATURE_SPAWNER_INTERVAL) {
		go->makeArcher(-300, 0);
		t_lvlSpawn.Reset(0.0);
	}
}

void Game::keyPressed(unsigned char key, int x, int y) {
	// Get modifiers
	int alt, ctrl, modifiers, shift;
	modifiers = glutGetModifiers();
	alt = modifiers & GLUT_ACTIVE_ALT;
	ctrl = modifiers & GLUT_ACTIVE_CTRL;
	shift = modifiers & GLUT_ACTIVE_SHIFT;

	// PROCESS KEYBOARD INPUT
	switch(key) {
		case 'L':
		case 'l': {
			std::string msg("L IS PRESSED!!");
			text.text(msg, 300.0, 200.0, winParems.depth());
//			makeAttacker();
		} break;
	}
}



void Game::specialKeyPressed(int key, int x, int y) {
	// Get modifiers
	int alt, ctrl, modifiers, shift;
	modifiers = glutGetModifiers();
	alt = modifiers & GLUT_ACTIVE_ALT;
	ctrl = modifiers & GLUT_ACTIVE_CTRL;
	shift = modifiers & GLUT_ACTIVE_SHIFT;

	// PROCESS KEYBOARD INPUT
	switch(key) {
		case 'L':
		case 'l': {
			std::string msg("L IS PRESSED!!");
			text.text(msg, 300.0, 200.0, winParems.depth());
//			makeAttacker();
		} break;
	}
}




void Game::processInput() { 

	// Add Keyboard input HERE!

	// L //
	if (in.isKeyPressed('L') || in.isKeyPressed('l')) {
		std::string msg("L IS PRESSED!!");
		text.text(msg, 300.0, 200.0, winParems.depth());
		makeAttacker();
		sm.playtest();										// Testing Sound!
	}

	// LEFT MOUSE BUTTON
	if (in.isBtnPressed(GLUT_LEFT_BUTTON)) {
		Vector3 mouse = in.getMousePos();
//		Vector3 center_mouse = in.getMousePos();
		// Timer - Get elapsed time since last update
		leftBtnTimer.Calculate_Ellapsed_Time();
		std::stringstream msg1;
		msg1 << "Mousetimer=" << leftBtnTimer.TotalTime();
		text.text(msg1, 300.0, 210.0, winParems.depth());
		
		// CHECK LEFT-BUTTON TIMER
		if(leftBtnTimer.TotalTime() >= LEFT_BUTTON_INTERVAL) {
			// First check the active launcher
			if(activeLauncher != NULL) {
				doLaunch();
			}
			


			// FORT MENU BUTTONS
			else if(fortMenu->activate(mouse)) {
				text.text(std::string("ACTIVATED A BUTTON!"), 300.0, 510.0, winParems.depth());
				processFortMenuButton();
			}
			
			// LAUNCHER OBJECTS
			else if(activateGO(mouse)) {


			}
			else if(fort.validPlacement(mouse.x())) {
				fort.makeObj(mouse.x(), *go);
			}
			leftBtnTimer.Reset(0.0);
		}
		std::string msg("Left mouse button IS HELD!!");
		text.text(msg, 275.0, 200.0, winParems.depth());
	}

	// RIGHT MOUSE BUTTON
	if (in.isBtnPressed(GLUT_RIGHT_BUTTON)) {
		std::string msg("RIGHT MOUSE BUTTON IS PRESSED!!");
		text.text(msg, 300.0, 200.0, winParems.depth());
	}

}


void Game::processFortMenuButton() {
	Vector3 btn = fortMenu->getActiveButton();
	int row = btn.x();
	int col = btn.y();

	switch(row) {
		case 0: {
			switch(col) {
				case 0: fort.setSelectedType(Fort::FENCE); break;
				case 1: fort.setSelectedType(Fort::MOTE); break;
				case 2: fort.setSelectedType(Fort::WALL_WOOD); break;
				case 3: fort.setSelectedType(Fort::WALL_STONE); break;
//				case 4: fort.setSelectedType(Fort::PLACEMENT_TYPE.CATAPULT); break;
				default: fort.setSelectedType(Fort::NONE); break;
			}
		} break;
		case 1: {
			switch(col) {
				case 0: fort.setSelectedType(Fort::TOWER_ARCHER); break;
				case 1: fort.setSelectedType(Fort::TOWER_MAGE); break;
				case 2: fort.setSelectedType(Fort::TOWER_OIL); break;
				case 3: fort.setSelectedType(Fort::CATAPULT); break;
//				case 4: fort.setSelectedType(Fort::PLACEMENT_TYPE.FENCE); break;
				default: fort.setSelectedType(Fort::NONE); break;
			}
		} break;
		default: fort.setSelectedType(Fort::NONE); break;
	}

}





void Game::setupFortMenu() {
	std::string label;

	fortMenu = new GUIButtonMenu(&winParems);
	fortMenu->setHeight(60);
	fortMenu->setWidth(winParems.width());
	fortMenu->setPos(0,  winParems.height()-SCOREBOARD_HEIGHT);
	fortMenu->setDimensions(2, 4);

	// Buttons
	for(int row = 0; row < fortMenu->getDimensions().x(); ++row) {
		for(int col = 0; col < fortMenu->getDimensions().y(); ++col) {
			fortMenu->setButtonLabel(row, col, getFortButtonLabel(row, col));
		}
	}
}



std::string Game::getFortButtonLabel(int row, int col) {
	std::string label;
	switch(row) {
		case 0: {
			switch(col) {
				case 0: label = "Fence"; break;
				case 1: label = "Mote"; break;
				case 2: label = "Wood Wall"; break;
				case 3: label = "Stone Wall"; break;
//				case 4: label = "Fence"; break;
				default: label = "NULL"; break;
			}
		} break;
		case 1: {
			switch(col) {
				case 0: label = "Archer Tower"; break;
				case 1: label = "Mage Tower"; break;
				case 2: label = "Oil Tower"; break;
				case 3: label = "Catapult"; break;
//				case 4: label = "Fence"; break;
				default: label = "NULL"; break;
			}
		} break;
		default: label = "NULL"; break;
	}
	return label;
}



bool Game::activateGO(Vector3 mouse) {
	b2Vec2 mouse2;
	mouse2.Set(mouse.x(), mouse.y());
	std::list<GameObj*> defenders = go->getDefenders();
	std::list<GameObj*>::iterator it = defenders.begin();
	
	if(activeLauncher != NULL) {
		activeLauncher->isActivated(true);				// RESET
		activeLauncher = NULL;							// Clear pointer
	}

	// searching for mouse clicks on a launcher object.
	while(it != defenders.end()) {
		if(it._Ptr->_Myval->activate(mouse2) ) {
			activeLauncher = static_cast<Launcher*>(it._Ptr->_Myval);
			return true;								// FOUND ONE!
		}
		++it;
	}

	return false;										// DIDN'T FIND ONE
}



void Game::doLaunch() {

	GameObj* temp = go->makeArrow(activeLauncher->body->GetPosition().x, activeLauncher->body->GetPosition().y);
	temp->setVecAngle(activeLauncher->getLaunchAngle());
//	temp->setVelocity(launchVelocity);
	temp->body->SetLinearVelocity(b2Vec2(activeLauncher->getLaunchVelocity() * std::cos(Util::deg2Rad(activeLauncher->getLaunchAngle())), activeLauncher->getLaunchVelocity() * std::sin(Util::deg2Rad(activeLauncher->getLaunchAngle()))));
	temp->setTeam(activeLauncher->isNPC());
	//	b2Fixture *fixture = temp->body->GetFixtureList();




}

