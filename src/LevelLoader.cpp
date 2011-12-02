#include "LevelLoader.h"


LevelLoader::LevelLoader(void)
{
	currentID = 0;
	DEF_DIRECTORY = "level/";
}


LevelLoader::~LevelLoader(void)
{
}


void LevelLoader::loadLevel(int level) {
	bool begin = false;
	std::stringstream fName;
	fName << DEF_DIRECTORY << "level" << level << ".dat";
	std::ifstream file(fName.str());
	if(file.is_open()) {							// valid file
		currentLevel = level;
		spawnList.clear();
		while(!file.eof()) {			// loop through file
			// TODO- Add search for multiple tags here  (creatures, level timer, etc)
			if(!begin) {				// begin flag indicates the start of level data
				std::string strIn;		// looking for the begin flag
				file >> strIn;
				if(strIn == "level_begin") {
					begin = true;
				}
			
			// BEGIN FOUND - LOAD DATA
			} else {
				int newID = -1;
				file >> newID;
				if(newID > 0 && newID < 20) {
					spawnList.push_back(newID);
				}
			}
		}	// end loop

		file.close();
	
	} else {  // FAIL TO OPEN!
		bool fail = true;		// does nothing
	}
}

int LevelLoader::nextID() {
	++currentID;
	if(currentID < spawnList.size()) {
		return spawnList[currentID];
	}
	return -1;
}


void LevelLoader::spawn(GameObjectManager &go) {			// spawn the next creature
	int id = nextID();

	switch(id) {
		case 1: go.makeArcher(-375, -50); break;		// War Dog
		case 2: go.makeArcher(-375, -50); break;		// Barbarian
		case 3: go.makeArcher(-375, -50); break;		// Archer
		case 4: go.makeArcher(-375, -50); break;		// Seige Engine
		default: // do nothing
			break;
	}
}



