#include "GameObjectManager.h"


GameObjectManager::GameObjectManager(WinParems *parems, SoundManager &soundManager) : sm(soundManager) {
	winParems = parems;
}


GameObjectManager::~GameObjectManager() {
	std::list<GameObj*>::iterator it = attackers.begin();
	while (it != attackers.end()) {
		delete (*it);
		++it;
	}
	it = defenders.begin();
	while (it != defenders.end()) {
		delete (*it);
		++it;
	}

}

//
//GameObj* GameObjectManager::makeWarDog(double x, double y) {
//	GameObj *temp = new GOWarDog(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeBarbarian(double x, double y) {
//	GameObj *temp = new GOBarbarian(winParems, x, y);
//	addObject(temp);
//	return temp;
//}

GameObj* GameObjectManager::makeArcher(double x, double y) {
	GameObj *temp = new GOArcher(winParems, x, y);
	temp->setSoundSourceID(sm.registerObject());				// Register new object with sound manager
	addObject(temp);
	return temp;
}
//
//GameObj* GameObjectManager::makeSeigeEngine(double x, double y) {
//	GameObj *temp = new GOSeigeEngine(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeFence(double x, double y) {
//	GameObj *temp = new GOFence(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeMote(double x, double y) {
//	GameObj *temp = new GOMote(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeWoodWall(double x, double y) {
//	GameObj *temp = new GOWoodWall(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
GameObj* GameObjectManager::makeStoneWall(double x, double y) {
	GameObj *temp = new GOStoneWall(winParems, x, y);
	addObject(temp);
	return temp;
}

//GameObj* GameObjectManager::makeArcherTower(double x, double y) {
//	GameObj *temp = new GOArcherTower(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeMageTower(double x, double y) {
//	GameObj *temp = new GOMageTower(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeOilTower(double x, double y) {
//	GameObj *temp = new GOOilTower(winParems, x, y);
//	addObject(temp);
//	return temp;
//}
//
//GameObj* GameObjectManager::makeCatapult(double x, double y) {
//	GameObj *temp = new GOCatapult(winParems, x, y);
//	addObject(temp);
//	return temp;
//}


// Remove Object from master list and destory references to that object
void GameObjectManager::destroyObject(GameObj *obj2Kill) {
	std::list<GameObj*>::iterator it_current, it_end, it_current2, it_end2;		// Iterators for each list (npc and pc)

	if(obj2Kill->isNPC()) {									// Setup iterators for NPC or PC list
		it_current = attackers.begin();
		it_end = attackers.end();
		it_current2 = defenders.begin();
		it_end2 = defenders.end();
	} else {
		it_current = defenders.begin();
		it_end = defenders.end();
		it_current2 = attackers.begin();
		it_end2 = attackers.end();
	}

	// Loops through list that object DOES NOT belong to
	while(it_current2 != it_end2) {
		// Clean up references to the object being deleted
		(*it_current)->removeEnemy(obj2Kill);
	}

	// Loops though list that object DOES belong to
	bool found = false;
	while(it_current != it_end) {
		// Clean up references to the object being deleted
		(*it_current)->removeEnemy(obj2Kill);

		// Remove object from master list
		if((*it_current) == obj2Kill) {
			delete (*it_current);
			found = true;
			if(obj2Kill->isNPC()) {
				it_current = attackers.erase(it_current);
			} else {
				it_current = defenders.erase(it_current);
			}
		} else {
			++it_current;
		}
	}
}

void GameObjectManager::addObject(GameObj *newObj) { // Adds object to appropriate tracking list
	if(newObj->isNPC()) {
		attackers.push_back(newObj);
	} else {
		defenders.push_back(newObj);
	}
}




void GameObjectManager::resetAttackers() {

	// Loop through all attackers, remove references to each attacker, remove the attacker from master list.
	std::list<GameObj*>::iterator it_a = attackers.begin();
	while(it_a != attackers.end()) {

		// Remove references to attacker from all defenders
		std::list<GameObj*>::iterator it_d = defenders.begin();
		while(it_d != defenders.end()) {
			(*it_d)->removeEnemy(*it_a);
			++it_d;
		}
		delete (*it_a);
		it_a = attackers.erase(it_a);				// Remove from attacker list.
	}
}


// This function updates the attacking mobs / movement / collision / attacks
void GameObjectManager::updateDefenders() {

	std::list<GameObj*>::iterator it = defenders.begin();
	while(it != defenders.end()) {
		if(!(*it)->isAlive()) {											// Cleanup expired objects
			winParems->getWorld()->DestroyBody((*it)->body);
			it = defenders.erase(it);
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
			winParems->getWorld()->DestroyBody((*it)->body);
			it = defenders.erase(it);
		} else {
			(*it)->update(sm);
			++it;
		}
	}
}


// This function updates the attacking mobs / movement / collision / attacks
void GameObjectManager::drawAll() {

	std::list<GameObj*>::iterator it = attackers.begin();
	while(it != attackers.end()) {
		(*it)->draw();
		++it;
	}
	it = defenders.begin();
	while(it != defenders.end()) {
		(*it)->draw();
		++it;
	}
}