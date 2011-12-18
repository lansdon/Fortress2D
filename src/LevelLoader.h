#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

#include "GameObjectManager.h"

/*
	This class loads level data from file and caches the current level information.
	Provides interface functions for retrieving data
*/
class LevelLoader
{
public:
	LevelLoader(void);
	~LevelLoader(void);
	void loadLevel(int level, GameObjectManager &go);
	int nextID();
	int getCurrentLevel() { return currentLevel; }
	void spawn(GameObjectManager &go);			// spawn the next creature

	std::vector<bool> LevelLoader::getSpawnListTypes();



private:
	std::queue<unsigned int> spawnList;		// Chronological list of objects to spawn.
	std::vector<bool> spawnListTypeID;		// List of which Settings::TypeID is loaded this level

	int currentID;
	int currentLevel;
	std::string DEF_DIRECTORY;

	const int DEF_SPAWN_X;
	const int DEF_SPAWN_Y;
	const int DEF_DISTANCE_BETWEEN_SPAWNS;
};

