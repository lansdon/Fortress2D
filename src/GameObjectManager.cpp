#include "GameObjectManager.h"


GameObjectManager::GameObjectManager(Settings *settings, SoundManager &soundManager) : sm(soundManager) {
	this->settings = settings;
}


GameObjectManager::~GameObjectManager() {
	std::list<GameObj*>::iterator it = attackers.begin();
	while (it != attackers.end()) {
		it = destroyObject(*it);
	}
	std::list<GameObj*>::iterator it2 = defenders.begin();
	while (it2 != defenders.end()) {
		destroyObject(*it2);
	}
}

//
//GameObj* GameObjectManager::makeWarDog(double x, double y) {
//	GameObj *temp = new GOWarDog(settings, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeBarbarian(double x, double y) {
//	GameObj *temp = new GOBarbarian(settings, x, y);
//	addObject(temp);
//	return temp;
//}

GameObj* GameObjectManager::makeArcher(double x, double y) {
	GOArcher *temp = new GOArcher(settings, x, y);
//	GOArcher *temp = new GameObject(settings, x, y);
	temp->setSoundSourceID(sm.registerObject());				// Register new object with sound manager
	addObject(temp);
	return temp;
}
//
//GameObj* GameObjectManager::makeSeigeEngine(double x, double y) {
//	GameObj *temp = new GOSeigeEngine(settings, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeFence(double x, double y) {
//	GameObj *temp = new GOFence(settings, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeMote(double x, double y) {
//	GameObj *temp = new GOMote(settings, x, y);
//	addObject(temp);
//	return temp;
//}
//
GameObj* GameObjectManager::makeWoodWall(double x, double y) {
	GameObj *temp = new GOWoodWall(settings, x, y);
	addObject(temp);
	return temp;
}

GameObj* GameObjectManager::makeStoneWall(double x, double y) {
	GameObj *temp = new GOStoneWall(settings, x, y);
	temp->setSoundSourceID(sm.registerObject());				// Register new object with sound manager
	addObject(temp);
	return temp;
}

GameObj* GameObjectManager::makeArcherTower(double x, double y) {
	GameObj *temp = new GOArcherTower(settings, x, y);
	temp->setSoundSourceID(sm.registerObject());				// Register new object with sound manager
	addObject(temp);
	return temp;
}
//
//GameObj* GameObjectManager::makeMageTower(double x, double y) {
//	GameObj *temp = new GOMageTower(settings, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeOilTower(double x, double y) {
//	GameObj *temp = new GOOilTower(settings, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeCatapult(double x, double y) {
//	GameObj *temp = new GOCatapult(settings, x, y);
//	addObject(temp);
//	return temp;
//}

GameObj* GameObjectManager::makeArrow(double x, double y, bool bNPCTeam) {
	GameObj *temp = new GOAArrow(settings, x, y);
	temp->goSettings.setTeam(bNPCTeam);
	temp->body->SetFixedRotation(false);
	addObject(temp);
	return temp;
}





// Remove Object from master list and destory references to that object
std::list<GameObj*>::iterator GameObjectManager::destroyObject(GameObj *obj2Kill) {

	// Locations where a reference may occur.
	
	// Todo ADD Nullification of activeLauncher pointer.
	// Game::activeLauncher


	// Removal from attacker/defender lists 
	// removal of individual enemy lists
	// Deletion of object  (note: box2d world deletion called on body from GameObj deconstructor
	std::list<GameObj*>::iterator it_friends_current, it_friends_end, it_enemies_current, it_enemies_end;		// Iterators for each list (npc and pc)

	// Setup iterators depending on which team the object belongs to.
	if(obj2Kill->goSettings.isNPC()) {									
		it_friends_current = attackers.begin();
		it_friends_end = attackers.end();
		it_enemies_current = defenders.begin();
		it_enemies_end = defenders.end();
	} else {
		it_friends_current = defenders.begin();
		it_friends_end = defenders.end();
		it_enemies_current = attackers.begin();
		it_enemies_end = attackers.end();
	}

	// Loops through (enemy) list that object DOES NOT belong to
	while(it_enemies_current != it_enemies_end) {
		// Clean up references to the object being deleted
		(*it_enemies_current)->removeEnemy(obj2Kill);
		++it_enemies_current;
	}

	// Loops though list that object DOES belong to
	bool found = false;
	while(it_friends_current != it_friends_end) {
		// Clean up references to the object being deleted
//		(*it_current)->removeEnemy(obj2Kill);

		// Remove object from master list
		if((*it_friends_current) == obj2Kill) {
			found = true;
			if(obj2Kill->goSettings.isNPC()) {
				delete (*it_friends_current);
				it_friends_current = attackers.erase(it_friends_current);
			} else {
				delete (*it_friends_current);
				it_friends_current = defenders.erase(it_friends_current);
			}
		} else {
			++it_friends_current;
		}
		if(found) return it_friends_current;
	}
	return it_friends_end;
}

void GameObjectManager::addObject(GameObj *newObj) { // Adds object to appropriate tracking list
	if(newObj->isNPC()) {
		attackers.push_back(newObj);
	} else {
		defenders.push_back(newObj);
	}
}



// Function for starting a new level and clearing out the NPC list
void GameObjectManager::resetAttackers() {

	// Loop through all attackers, remove references to each attacker, remove the attacker from master list.
	std::list<GameObj*>::iterator it_a = attackers.begin();
	while(it_a != attackers.end()) {

		// Remove references to attacker from all defenders
		//std::list<GameObj*>::iterator it_d = defenders.begin();
		//while(it_d != defenders.end()) {
		//	(*it_d)->removeEnemy(*it_a);
		//	++it_d;
		//}
		destroyObject(*it_a);
//		it_a = attackers.erase(it_a);				// Remove from attacker list.
	}
	attackers.clear();
}





// This function updates the attacking mobs / movement / collision / attacks
void GameObjectManager::updateDefenders() {

	std::list<GameObj*>::iterator it = defenders.begin();
	while(it != defenders.end()) {
		if(!(*it)->isAlive()) {											// Cleanup expired objects
			it = destroyObject(*it);
		} else {
			(*it)->update(sm);
			++it;
		}
	}
}


// This function updates the attacking mobs / movement / collision / attacks
void GameObjectManager::updateAttackers() {

	std::list<GameObj*>::iterator it = attackers.begin();
	while(it != attackers.end()) {
		if(!(*it)->isAlive()) {											// Cleanup expired objects
			it = destroyObject(*it);
		} else {
			(*it)->update(sm);
			++it;
		}
	}
}


// This function updates the attacking mobs / movement / collision / attacks
void GameObjectManager::drawAll(b2Vec2 mouse) {

	std::list<GameObj*>::iterator it = attackers.begin();
	while(it != attackers.end()) {
		if((*it)->isAlive()) {
			(*it)->draw(mouse);
		}
		++it;
	}
	it = defenders.begin();
	while(it != defenders.end()) {
		if((*it)->isAlive()) {
			(*it)->draw(mouse);
		}
		++it;
	}
}