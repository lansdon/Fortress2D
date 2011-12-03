#pragma once
#include <vector>
#include <fstream>
#include <sstream>
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
	void loadLevel(int level);
	int nextID();
	int getCurrentLevel() { return currentLevel; }
	void spawn(GameObjectManager &go);			// spawn the next creature

private:
	std::vector<unsigned int> spawnList;		// Chronological list of objects to spawn.
	int currentID;
	int currentLevel;
	std::string DEF_DIRECTORY;

	const int DEF_SPAWN_X;
	const int DEF_SPAWN_Y;
};

