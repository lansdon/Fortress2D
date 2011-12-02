#include "Fort.h"


Fort::Fort(WinParems *parems) {
	winParems = parems;
	text.setWinParems(parems);
	SECTOR_WIDTH = 0;				// meters
	SECTOR_TOTAL = 0;

	// TEMP! THis should default to none... Set to wall for testing.
//	selectedType = NONE;
	selectedType = WALL_STONE;  // TEMP - Remove after UI exists for selecting object types

	elapsedTime = 0.0;
	PLACEMENT_TIMER = 2.0;

	// Fort Object Default Definitions
	pNone = new FortParems(0, 0, "", 0, 0, 0, 0);
	pWoodWall = new FortParems(10, 5, "Wood Wall", 0, 0, 100, 2);
	pStoneWall= new FortParems(10, 5, "Stone Wall", 0, 0, 200, 4);
	pMote = new FortParems(10, 5, "Mote", 0, 0, 100, 100);
	pTowerArcher = new FortParems(10, 5, "Archer Tower", 0, 0, 100, 3);
	pTowerMage= new FortParems(10, 5, "Mage Tower", 0, 0, 100, 3);
	pTowerOil = new FortParems(10, 5, "Wood Wall", 0, 0, 100, 3);
	pCatapult = new FortParems(5, 10, "Catapult", 0, 0, 50, 2);
	pFence = new FortParems(5, 2.5, "Fence", 0, 0, 50, 1);

}

void Fort::start() { // do we need to initialize this object post-constructor?
	SECTOR_WIDTH = Util::meter2Pixel(5);				// meters
	SECTOR_TOTAL = (winParems->width() - winParems->mid()) / SECTOR_WIDTH;
	activeSectors.resize(SECTOR_TOTAL);
}


Fort::~Fort(void) {
	delete pNone;
	delete pWoodWall;
	delete pStoneWall;
	delete pMote;
	delete pTowerArcher;
	delete pTowerMage;
	delete pTowerOil;
	delete pCatapult;
	delete pFence;
}



bool Fort::addObj(GameObj *newObj) {
	this->obj.push_back(newObj);
	return true;
}




void Fort::draw(Vector3 mouse) {
	// Offset mouse coords for lower left corner origin
	mouse.set(mouse.x(), mouse.y(), mouse.z());


	//std::vector<GameObj*>::iterator it = obj.begin();
	//while(it != obj.end()) {
	//	(*it)->update();
	//	++it;
	//}

	
	drawPlacementGuide(mouse);

	std::stringstream ss;
	ss <<  "fortmouse=(" << mouse.x() << "," << mouse.y() << ") selected:" << selectedType;
	text.text(ss, 200, 0, winParems->depth());

}

// Get the column # of valid placement loctions (Mid Point = column 0... Right most screen is last col)
unsigned int Fort::getPlacementCol(double mouseX) {
	
	if(mouseX < winParems->mid()) return 0; // Invalid location

	unsigned int col = (mouseX - winParems->mid()) / SECTOR_WIDTH; // find the column number starting at MID point
	if(col > SECTOR_TOTAL)
		return SECTOR_TOTAL;
	else return col;
}


// returns left most x coordinate where placement object should start
unsigned int Fort::getPlacementX(double mouseX) {
//	return (winParems->mid() + (getPlacementCol(mouseX) * SECTOR_WIDTH));		// left side of the column
	return ((winParems->mid()-winParems->width()/2) + (getPlacementCol(mouseX) * SECTOR_WIDTH));		// left side of the column according to openGL center origin
}


void Fort::drawPlacementGuide(Vector3 &mouse) {
//	if((mouse.x() < (*winParems).mid()) || (mouse.x() > (*winParems).width())) // Only draw placement guide in legal bounds
//		return;

//	unsigned int col = getPlacementCol(mouse.x()); // find the column number starting at MID point
//	unsigned int xBegin = (*winParems).mid() + (col*SECTOR_WIDTH);		// left side of the column
	unsigned int xBegin = getPlacementX(mouse.x());		// left side of the column

	glLoadIdentity();
	glColor3f(1, 1, 1);
	glTranslatef(xBegin, (*winParems).floor() - (*winParems).height()/2, (*winParems).depth());       // Move to 0,0 in bottom left corner of coord system
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2d(-0.5, 50);              // Top Left
		glVertex2d(0.5, 50);              // Top Right
		glVertex2d(0.5, (*winParems).floor());              // Bottom Right
		glVertex2d(-0.5, (*winParems).floor());              // Bottom Left
	glEnd();                            // Done Drawing The Quad

	glLoadIdentity();
	glTranslatef(xBegin + SECTOR_WIDTH, (*winParems).floor() - (*winParems).height()/2, (*winParems).depth());       // Move to 0,0 in bottom left corner of coord system
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2d(-0.5, 50);              // Top Left
		glVertex2d(0.5, 50);              // Top Right
		glVertex2d(0.5, (*winParems).floor());              // Bottom Right
		glVertex2d(-0.5, (*winParems).floor());              // Bottom Left
	glEnd();                            // Done Drawing The Quad



}


// Creates a pointer to a wall with given parameters
bool Fort::makeObj(float posX, GameObjectManager &go) {
//		enum PLACEMENT_TYPE { NONE, WALL_WOOD, WALL_STONE, MOTE, TOWER_ARCHER, TOWER_MAGE, TOWER_OIL, ART_CATAPULT, FENCE};

	// Timer - Get elapsed time since last update
	Timer.Calculate_Ellapsed_Time();
	elapsedTime += Timer.Ellapsed_Seconds();
	if(elapsedTime < PLACEMENT_TIMER) return false;			// 2 seconds between creating fort objects

	// ERROR!
//	if(!validPlacement(posX)) 
//		return false;

	//GameObj* temp = new GameObj(winParems, posX, 0);
	//temp->setType(GameObj::OBJECT_TYPE::DEFENDER);
	//temp->setTeam(false);

	//temp->setPosX(getPlacementX(posX));
	//temp->setPosY(winParems->floor());

	switch(selectedType) {
		case WALL_WOOD: {	go.makeStoneWall(getPlacementX(posX), -200);	} break;
		case WALL_STONE: { go.makeStoneWall(getPlacementX(posX), winParems->floor());	} break;
		case MOTE: { go.makeStoneWall(getPlacementX(posX), winParems->floor());	} break;
		case TOWER_ARCHER: { go.makeStoneWall(getPlacementX(posX), winParems->floor());	} break;
		case TOWER_MAGE: { go.makeStoneWall(getPlacementX(posX), winParems->floor());	} break;
		case TOWER_OIL: { go.makeStoneWall(getPlacementX(posX), winParems->floor());	} break;
		case CATAPULT: { go.makeStoneWall(getPlacementX(posX), winParems->floor());	} break;
		case FENCE: { go.makeStoneWall(getPlacementX(posX), winParems->floor());	} break;
	}

	
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(posX, 0);  // This needs to be adjusted for midpoint of the object?
	//bodyDef.userData = temp;
	//temp->body = winParems->getWorld()->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
//	b2PolygonShape dynamicBox;
//	dynamicBox.SetAsBox(temp->getTextWidth()/2, temp->getTextHeight()/2);
//	// Define the dynamic body fixture.
//	b2FixtureDef fixtureDef;
//	fixtureDef.shape = &dynamicBox;
//	// Set the box density to be non-zero, so it will be dynamic.
//	fixtureDef.density = 10.0f;
//	// Override the default friction.
//	fixtureDef.friction = 0.3f;
////	temp->body->SetLinearVelocity(b2Vec2(i*2, 0.0));
//	// Add the shape to the body.
//	temp->body->CreateFixture(&fixtureDef);
//
//	addObj(temp);


	elapsedTime = 0.0;
	Timer.Reset(0.0);		// Start the timer to measure interval between updates

	return true;
}




bool Fort::validPlacement(float posX) {
	posX = Util::convertCenter2LowerLeftX(posX, winParems);

	if(posX < winParems->mid()) return false;

	if(posX > winParems->width()) return false;


//	if(!getPlacementCol(posX)) return false;	// Invalid For location

	if(!isFortObjSelected()) return false;		// Does the user have a object type selected to place? (wall, tower, mote, etc)


	// Everything sounds good!
	return true;
}

void Fort::setSelectedType(PLACEMENT_TYPE type) {
	selectedType = type; 
}

bool Fort::isFortObjSelected() {
	
	
	// TODO - Need to check for an item selection
	
	
	return true;

}