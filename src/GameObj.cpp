#include "GameObj.h"


GameObj::GameObj(Settings *settings, double x, double y) // :
	//COLLISION_GROUP_GROUND(1),
	//COLLISION_GROUP_NPC_BULLET(2), 
	//COLLISION_GROUP_NPC_ATTACKER(4),
	//COLLISION_GROUP_PC_BULLET(16),
	//COLLISION_GROUP_PC_DEFENDER(32)

{

	this->settings = settings;
	text.setSettings(settings);


	elapsedTime = 0;
	body = NULL;

	groundContact = false;
	contacts = 0;		// TEMP?

	// Load texture
	textureID = TextureLoader::LoadGLTextures("test.png");

	// Sound ID
	soundSourceID = 0;
}


GameObj::~GameObj(void)
{
	settings->getWorld()->DestroyBody(body);	// Clean up B2Body Objects

}




void GameObj::move(SoundManager &sm) {
	if(!moveSpecial(sm)) {

		if(body) {
			// Gradual speed increase for objects with a max velocity set  // (Bullets should have max Vel ZERO) // this logic will need updating!
			if(goSettings.getVelocityMax()) {
				b2Vec2 vel = body->GetLinearVelocity();
				vel.x = b2Min( vel.x + 0.1f,  goSettings.getVelocityMax() );
				body->SetLinearVelocity( vel );
			}

			t_move.Calculate_Ellapsed_Time();
			if(t_move.TotalTime() >= TIMER_SOUND_MOVE) {
				SoundManager::Sounds soundID;
				switch(goSettings.getTypeID()) {
					case Settings::OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_MOVE; break;
					case Settings::OBJ_ID_STONEWALL: soundID = sm.SND_STONEWALL_MOVE; break;
		//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
		//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
		//			case settings.OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
					default: soundID = sm.SND_DOG_MOVE; break;
				}
				sm.playSound(soundSourceID, soundID, body->GetPosition());
				t_move.Reset(0.0);
			}
		}	
	}
}


void GameObj::addEnemy(GameObj *enemy, bool ranged) {
	bool found = false;

	for(std::list<GameObj*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		if((*it) == enemy)
			found = true;
	}

	if(!found) {
		enemies.push_back(enemy);
	}
}


void GameObj::removeEnemy(GameObj *enemy, bool ranged) {
	if(!enemies.size())
		return;

	std::list<GameObj*>::iterator it = enemies.begin();
	while(it != enemies.end()) {
		if((*it) == enemy) {
			it = enemies.erase(it);
			return;
		} else {
			++it;
		}
	}
}


void GameObj::attack(GameObj *enemy, SoundManager &sm) {
//	if(enemy->isAlive()) {
		// SFX
		t_melee.Calculate_Ellapsed_Time();
		if(t_melee.TotalTime() >= TIMER_SOUND_MELEE) {
			SoundManager::Sounds soundID;
			switch(goSettings.getTypeID()) {
				case Settings::OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
				case Settings::OBJ_ID_STONEWALL: soundID = sm.SND_STONEWALL_MELEE; break;
	//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
	//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
	//			case settings.OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
				default: soundID = sm.SND_ARCHER_DAMAGED; break;
			}
			sm.playSound(soundSourceID, soundID, body->GetPosition());
			t_melee.Reset(0.0);
		}

		// DAMAGE ENEMY
		enemy->damage(goSettings.getDamage(), sm);

		// Special Behavior (defined in derived classes)
		attackSpecial(enemy, sm);
//	}
}

// This function will calculate launche parameters and save them in the launch struct to be processed by calling object
void GameObj::rangedAttack(b2Vec2 nearest) {				// Ranged attack
	// Check timer
	t_launch.Calculate_Ellapsed_Time();
	if(t_launch.TotalTime() < (1 / goSettings._RoF)) {
		return;
	}


	std::srand( time(NULL));
	float accuracy = 75.0;							// TEMP - This should be a GoSettings variable 
	if(accuracy > 100) accuracy = 100;				// Accuracy from 0-100 (percent)  95 means it will hit approx 95/100 times
	int randomAdj =  (100-accuracy)*2;		// double to account for +/-
	double adjustment = rand() % randomAdj - randomAdj/2;
	int maxRange = (pow(goSettings._LAUNCH_MAX_VEL, 2) * sin((Util::PI/4)*2))/9.8;					// (v_0^2 sin(theta)) / g
	
	// Closest enemy is out of range    (maybe don't bother shooting?)
	if(maxRange < abs(getPos().x - nearest.x)) { 
		// launch at max velocity  +  45 + (45* (adjustment/100))
		// to do
		// need a way to launch arrows... (preload??) 

		// Don't shoot until in range!
		//launch.angle = 45.0 + (45.0 * (adjustment/100.0));
		//launch.velocity.Set(goSettings._LAUNCH_MAX_VEL * cos(Util::deg2Rad(launch.angle)), goSettings._LAUNCH_MAX_VEL * sin(Util::deg2Rad(launch.angle)));
		//launch.ammo = goSettings.ammo;
		//launch.launchTriggered = true;
	}
	// ENEMY IN RANGE
	// Need to add random adjustment to velocity AND angle.
	else {
		// ANGLE
		float angle = 45.0 + (45.0 * (adjustment/100.0));					// Take angle with random adjustment
		if(angle > goSettings._LAUNCH_MAX_ANGLE) angle = goSettings._LAUNCH_MAX_ANGLE;
		if(angle < goSettings._LAUNCH_MIN_ANGLE) angle = goSettings._LAUNCH_MIN_ANGLE;		
		launch.angle = angle;
		
		// VELOCITY
		// Use angle to calculate a launch velocity to get "near" the target     v = sqrt( (R*g) / sin(2theta))
		float range = Util::pixel2Meter(abs(nearest.x - body->GetPosition().x));	// meters to enemy
		int v0 = sqrt( (range * 9.8) / sin(Util::deg2Rad(2 * launch.angle)));
		v0 += (v0 * adjustment);
		if(v0 > goSettings._LAUNCH_MAX_VEL) v0 = goSettings._LAUNCH_MAX_VEL;
		if(v0 < goSettings._LAUNCH_MIN_VEL) v0 = goSettings._LAUNCH_MIN_VEL;
		launch.velocity.Set(v0 * cos(Util::deg2Rad(launch.angle)), v0 * sin(Util::deg2Rad(launch.angle)));
		
		launch.ammo = goSettings.ammo; // TODO - Need to add ammo selection for objects with more than 1 type of ammo?
		launch.launchTriggered = true;

		// FIRE!
		doLaunch();

	}

	t_launch.Reset(0.0);
}


// Process calculated launches for individual objects.   (currently this is for processing AI launches)
void GameObj::doLaunch() {
	GameObj* newAmmo = nextAmmo();
	if(newAmmo != NULL && launch.launchTriggered) {
	
		if(!isNPC()) {
			launch.angle += 90;
		}

		//newAmmo->body->SetActive(true);
		//newAmmo->body->SetAwake(true);
		//newAmmo->goSettings.setHP(newAmmo->goSettings.getHPMax());
		//newAmmo->goSettings.setHP(1);
		//setGroundContact(false);
		newAmmo->resetObjectState();

		newAmmo->goSettings.setInitVecAngle(launch.angle);
		newAmmo->goSettings.setCurrentVecAngle(launch.angle);
		newAmmo->goSettings.setVelocityMax(0);
		newAmmo->goSettings.setInitLinearVelocity(launch.velocity); 
		newAmmo->body->SetTransform(this->body->GetPosition(), Util::deg2Rad(launch.angle));
		newAmmo->body->SetLinearVelocity(launch.velocity);
		newAmmo->body->SetAngularDamping(.01);
		newAmmo->goSettings.setTeam(goSettings.isNPC());
		newAmmo->body->GetFixtureList()->SetFilterData(newAmmo->getFixtureCollisionFilter());
		launch.launchTriggered = false;
	}
}



// Find unused ammo object
GameObj* GameObj::nextAmmo() {
	std::vector<GameObj*>::iterator it = ammo.begin();
	while(it != ammo.end()) {
		if((*it)->body->IsActive() == false || this->isAlive() == false || (*it)->body->IsAwake() == false) {
			return *it;
		}
		++it;
	}
	return NULL;
}

void GameObj::death(SoundManager &sm) { 
	// SFX
	t_death.Calculate_Ellapsed_Time();
	if(t_death.TotalTime() >= TIMER_SOUND_DEATH) {
		SoundManager::Sounds soundID;
		switch(goSettings.getTypeID()) {
			case Settings::OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_DEATH; break;
			case Settings::OBJ_ID_STONEWALL: soundID = sm.SND_STONEWALL_DEATH; break;
	//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
	//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
	//			case settings.OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
			default: soundID = sm.SND_ARCHER_DEATH; break;
		}
		sm.playSound(soundSourceID, soundID, body->GetPosition());
		t_death.Reset(0.0);
	}

	// Special Behavior (defined in derived classes)
	deathSpecial(sm);
}


void GameObj::damage(int amount, SoundManager &sm) {
	// Process incoming damage
	if(getArmor() > amount)
		return;				// armor negates all damage
	else amount -= getArmor();
	setHP(getHP() - amount);

	// SFX
	t_damaged.Calculate_Ellapsed_Time();
	if(t_damaged.TotalTime() >= TIMER_SOUND_DAMAGED) {
		SoundManager::Sounds soundID;
		switch(goSettings.getTypeID()) {
			case Settings::OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_DAMAGED; break;
			case Settings::OBJ_ID_STONEWALL: soundID = sm.SND_STONEWALL_DAMAGED; break;
	//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
	//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
	//			case settings.OBJ_ID_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
			default: soundID = sm.SND_ARCHER_DAMAGED; break;
		}
		sm.playSound(soundSourceID, soundID, body->GetPosition());
		t_damaged.Reset(0.0);
	}

	// Special Behavior (defined in derived classes)
	damageSpecial(amount, sm);

	// Death sequence
	if(getHP() < 0) {
		death(sm);
	}
}

void GameObj::update(SoundManager &sm, b2Vec2 nearest) {
//	this->elapsedTime = elapsedTime;

	if(!body->IsActive()) {
		return;
	}

	bool doRanged = true;

	if(isAlive()) {
		move(sm);

		// Melee Attacks
		for(std::list<GameObj*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
			if((*it)->isAlive()) {
				attack((*it), sm);
				doRanged = false;
			}
		}

		// Ranged attacks
		if(doRanged) {
			if(goSettings._LAUNCH_MAX_VEL) {
				rangedAttack(nearest);
			}
		}

		// Proccess ground contact
		if(groundContact) {
			// BULLETS - disappear after striking the ground.
			if(goSettings.getType() == Settings::OBJ_T_BULLET) {
				goSettings.setHP(0);
//				body->SetActive(false);
			}
		}
	} else {
//		body->SetTransform(b2Vec2(-5000, -5000), 0.0);
	}

	// Special Behavior (defined in derived classes)
	updateSpecial(sm);

}


bool GameObj::isAlive() {
	if(getHP() > 0) 
		return true; 
	else return false; 
}



// remove dead enemies from the list // THIS IS BEING HANDLED BY GAME OBJ MANAGER! REMOVE~!
bool GameObj::cleanEnemiesList() {
	std::list<GameObj*>::iterator it = enemies.begin();
	while(it != enemies.end()) {
		if(!(*it)->isAlive()) {
			it = enemies.erase(it);           // Change elemnts to be removed to NULL
		} else {
			++it;
		}
	}

	return true;
}


void GameObj::draw(b2Vec2 mouse) {						// draw the object on screen
	if(!body->IsActive()) {
//		return;
	}

	glLoadIdentity();

	if(enemies.size() == 0)
		glColor3f(goSettings._DEF_DRAW_COLOR.r, goSettings._DEF_DRAW_COLOR.g, goSettings._DEF_DRAW_COLOR.b);
	else glColor3f(goSettings._CONTACT_DRAW_COLOR.r, goSettings._CONTACT_DRAW_COLOR.g, goSettings._CONTACT_DRAW_COLOR.b);

	b2Vec2 pos = body->GetPosition();
	glTranslatef(body->GetPosition().x, body->GetPosition().y, 0);       // center position
	glRotatef(Util::rad2Deg(body->GetAngle()), 0, 0, 1);

	if(settings->useTextures()) {
		glEnable(GL_TEXTURE_2D); //Switch back to using colors instead of textures
		glBindTexture(GL_TEXTURE_2D, textureID);
		glColor3f(1, 1, 1);
		 //Use blurry texture mapping (replace GL_LINEAR with GL_NEAREST for blocky)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   
		glBegin(GL_QUADS);                      // Draw A Quad
			glTexCoord2f(0, 1);																			// Top Left
			glVertex2d( -Util::meter2Pixel(goSettings._textWidth)/2, Util::meter2Pixel(goSettings._textHeight)/2);              // Top Left
			glTexCoord2f(1, 1);																		// Top Right
			glVertex2d(Util::meter2Pixel(goSettings._textWidth)/2, Util::meter2Pixel(goSettings._textHeight)/2);              // Top Right
			glTexCoord2f(1,  0);																	// Bottom Right
			glVertex2d(Util::meter2Pixel(goSettings._textWidth)/2, -Util::meter2Pixel(goSettings._textHeight)/2);              // Bottom Right
			glTexCoord2f(0, 0);																	// Bottom Left
			glVertex2d( - Util::meter2Pixel(goSettings._textWidth)/2, -Util::meter2Pixel(goSettings._textHeight)/2);      // Bottom Left
		glEnd();                            // Done Drawing The Quad
		glDisable(GL_TEXTURE_2D); //Switch back to using colors instead of textures

	} else {		// NO TEXTURES

//		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*settings).depth());       // Move to 0,0 in bottom left corner of coord system
		glBegin(GL_QUADS);                      // Draw A Quad
			glVertex2d(-Util::meter2Pixel(goSettings._textWidth)/2, Util::meter2Pixel(goSettings._textHeight)/2);              // Top Left
			glVertex2d(Util::meter2Pixel(goSettings._textWidth)/2, Util::meter2Pixel(goSettings._textHeight)/2);              // Top Right
			glVertex2d(Util::meter2Pixel(goSettings._textWidth)/2, -Util::meter2Pixel(goSettings._textHeight)/2);              // Bottom Right
			glVertex2d(-Util::meter2Pixel(goSettings._textWidth)/2, -Util::meter2Pixel(goSettings._textHeight)/2);      // Bottom Left
		glEnd();                            // Done Drawing The Quad

	}	

//	text.text(name, posX - (name.length()/2), textHeight, settings.depth());
	std::stringstream ss;
//	ss << goSettings._name << " " << "x=" << body->GetPosition().x << " y=" << body->GetPosition().y;
	std::stringstream ss2;
//	ss2 << "hp=" << getHP() << " enemies=" << enemies.size();
	ss2 << "hp=" << getHP();
//	text.text(ss, body->GetPosition().x, body->GetPosition().y+goSettings._textHeight + 20, settings->depth());
	text.text(ss2, body->GetPosition().x, body->GetPosition().y+goSettings._textHeight + 10, settings->depth());
}



// calculates velocity vectors
//void GameObj::recalculate() {
//	velX = velocity * std::cos(Util::deg2Rad(angle));
//	velY = velocity * std::sin(Util::deg2Rad(angle));
//
//
//}



void GameObj::addContact(GameObj *enemy) {
	if(enemy == NULL) {
		groundContact = true;
	}
	else if(enemy->isNPC() != isNPC()) {
//		contacts++; 
		if(enemy->getType() != Settings::OBJ_T_BULLET) {
			addEnemy(enemy); 
		}
	}
}


void GameObj::subContact(GameObj *enemy) {
//	contacts--; 
	removeEnemy(enemy); 
}




///////////////////////////////////////////////////////////////
// Box2D Setup
void GameObj::setupB2D(double x, double y) {

	b2BodyDef bodyDef;
	b2PolygonShape dynamicBox;
	b2FixtureDef fixtureDef;

//	if(objType == STATIC) {
//		bodyDef.type = b2_staticBody;
//	} else {
		bodyDef.type = b2_dynamicBody;
//	}
	bodyDef.position.Set(x, y);
//	bodyDef.linearVelocity(Util::meter2Pixel(5));
	bodyDef.userData = this;
	body = settings->getWorld()->CreateBody(&bodyDef);
	dynamicBox.SetAsBox(Util::meter2Pixel(getTextWidth())/2,Util::meter2Pixel(getTextHeight())/2);	// Define another box shape for our dynamic body.
	fixtureDef.shape = &dynamicBox;			// Define the dynamic body fixture.
	fixtureDef.density = goSettings._density;			// Set the box density to be non-zero, so it will be dynamic.	
	fixtureDef.friction = goSettings._friction;			// Override the default friction.
	fixtureDef.filter = getFixtureCollisionFilter();
//	fixtureDef.filter.maskBits = getFixtureCollissionFilter().maskBits;


	body->SetLinearVelocity(b2Vec2(goSettings.getVelocityMax(), 0.0));
	body->CreateFixture(&fixtureDef);		// Add the shape to the body.

}


// Build collision filters based on object types and team
b2Filter GameObj::getFixtureCollisionFilter() {
	b2Filter filter;

	// ATTACKERS
	if(this->isNPC()) {
		if(getType() == Settings::OBJ_T_BULLET) {
			filter.categoryBits = Settings::COLLISION_CAT_NPC_BULLET;		// NPC BULLET GROUP
			filter.maskBits = Settings::COLLISION_CAT_PC_DEFENDER + Settings::COLLISION_CAT_GROUND;		// List of possible targets
		} else {
			filter.categoryBits = Settings::COLLISION_CAT_NPC_ATTACKER;		// NPC ATTACKER GROUP
			filter.maskBits = Settings::COLLISION_CAT_PC_DEFENDER + Settings::COLLISION_CAT_GROUND + Settings::COLLISION_CAT_PC_BULLET;		// List of possible targets
		}
	
	// DEFENDERS	
	} else {
		if(getType() == Settings::OBJ_T_BULLET) {
			filter.categoryBits = Settings::COLLISION_CAT_PC_BULLET;		// PC BULLET GROUP
			filter.maskBits = Settings::COLLISION_CAT_NPC_ATTACKER + Settings::COLLISION_CAT_GROUND;		// List of Possible targets
		} else {
			filter.categoryBits = Settings::COLLISION_CAT_PC_DEFENDER;		// PC ATTACKER GROUP
			filter.maskBits = Settings::COLLISION_CAT_PC_DEFENDER + Settings::COLLISION_CAT_GROUND + Settings::COLLISION_CAT_NPC_ATTACKER + Settings::COLLISION_CAT_NPC_BULLET;		// PC defenders don't collide with defender bullets  // this may change!
		}
	}
	
	return filter;
}





// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
void GameObj::loadObject(std::string datFilename, double x, double y) {

	// Load Settings
	goSettings.loadFromFile(datFilename);
	
	// Setup Physics
	setupB2D(x, y);

	// Load Texture
	textureID = TextureLoader::LoadGLTextures(goSettings.getTextureFilename());

}

void GameObj::resetObjectState() {			// reset an object so i can be re-used
	this->cleanEnemiesList();
	this->setHP(getHPMax());
	this->body->SetActive(true);
	this->body->SetAwake(true);
	this->setGroundContact(false);

}