#include "LevelLoader.h"


LevelLoader::LevelLoader(void) : DEF_SPAWN_X(100), DEF_SPAWN_Y(40), DEF_DISTANCE_BETWEEN_SPAWNS(20)
{
	currentID = 0;
	DEF_DIRECTORY = "level/";

//	DEF_SPAWN_X = 5;
//	DEF_SPAWN_Y = 40;
}


LevelLoader::~LevelLoader(void)
{
}


void LevelLoader::loadLevel(int level, GameObjectManager &go) {

	bool begin = false;
	std::stringstream fName;
	fName << DEF_DIRECTORY << "level" << level << ".dat";
	std::ifstream file(fName.str());
	if(file.is_open()) {							// valid file
		currentLevel = level;
//		spawnList.clear();
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
					spawnList.push(newID);
				}
			}
		}	// end loop

		file.close();
	
	} else {  // FAIL TO OPEN!
		bool fail = true;		// does nothing
	}
}

int LevelLoader::nextID() {
	//++currentID;
	//if(currentID < spawnList.size()) {
	//	return spawnList[currentID];
	//}
	if(spawnList.empty())
		return -1;
	else {
		return spawnList.front();
	}
}


void LevelLoader::spawn(GameObjectManager &go) {			// spawn the next creature
	// TODO ADD LOADING SCREEN
	
	int xSpawn = DEF_SPAWN_X;
	while(!spawnList.empty()) {
		xSpawn -= DEF_DISTANCE_BETWEEN_SPAWNS;

		switch(spawnList.front()) {
			case 1: go.makeArcher(xSpawn, DEF_SPAWN_Y); break;		// War Dog
			case 2: go.makeArcher(xSpawn, DEF_SPAWN_Y); break;		// Barbarian
			case 3: go.makeArcher(xSpawn, DEF_SPAWN_Y); break;		// Archer
			case 4: go.makeArcher(xSpawn, DEF_SPAWN_Y); break;		// Seige Engine
			default: break;											// do nothing
		}
		spawnList.pop();
	}
}



// Numbers used in leve.dat files   (need to convert level files into Settings::OBJECT_ID
//0=NONE
//1=WARDOG
//2=SPEARMAN
//3=ARCHER
//4=SEIGE ENGINE


std::vector<bool> LevelLoader::getSpawnListTypes() {


	spawnListTypeID.resize(Settings::TOTAL_OBJ_IDS + 1);
	std::queue<unsigned int> temp(spawnList);		// Chronological list of objects to spawn.

	// Search for types of attackers being loaded this level
	while(!temp.empty()) {
		switch(temp.front()) {
			case 1: spawnListTypeID[Settings::OBJ_ID_DOG] = true; break;
			case 2: spawnListTypeID[Settings::OBJ_ID_SPEARMAN] = true; break;
			case 3: spawnListTypeID[Settings::OBJ_ID_ARCHER] = true; break;
			case 4: spawnListTypeID[Settings::OBJ_ID_SEIGE_ENGINE] = true; break;
		}
		temp.pop();
	}
	

	// AUTOMATICALLY LOAD DEFENDER OBJECTS
	spawnListTypeID[Settings::OBJ_ID_ARCHER_TOWER] = true;
	spawnListTypeID[Settings::OBJ_ID_CATAPAULT] = true;
	spawnListTypeID[Settings::OBJ_ID_FENCE] = true;
	spawnListTypeID[Settings::OBJ_ID_MAGE_TOWER] = true;
	spawnListTypeID[Settings::OBJ_ID_MOTE] = true;
	spawnListTypeID[Settings::OBJ_ID_OIL_TOWER] = true;
	spawnListTypeID[Settings::OBJ_ID_STONEWALL] = true;
	spawnListTypeID[Settings::OBJ_ID_WOODWALL] = true;

	// AUTOMATICALLY LOAD AMMO
	spawnListTypeID[Settings::OBJ_ID_ARROW] = true;
	spawnListTypeID[Settings::OBJ_ID_CANNONBALL] = true;

	return spawnListTypeID;

}
