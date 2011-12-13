#include "GameObj.h"


GameObj::GameObj(Settings *settings, double x, double y) :
	COLLISION_GROUP_GROUND(1),
	COLLISION_GROUP_NPC_BULLET(2), 
	COLLISION_GROUP_NPC_ATTACKER(4),
	COLLISION_GROUP_PC_BULLET(16),
	COLLISION_GROUP_PC_DEFENDER(32)

{

	this->settings = settings;
	text.setSettings(settings);



	// Sound Effect Timers
	TIMER_SOUND_MOVE = 2.0; // ms
	TIMER_SOUND_MELEE = 1.0; // ms
	TIMER_SOUND_RANGED = 1.0; // ms
	TIMER_SOUND_DAMAGED = 1.0; // ms
	TIMER_SOUND_DEATH = 2.0; // ms
	TIMER_SOUND_IDLE = 5.0; // ms

	//posX = posY = 0;
	velocityMax = 0;		// pixels per second
	//angle = 0;		// 0 = right   180 = left   90 = up
	hpCur = 10;			// current hitpoints
	hpMax = 10;			// max hitpoints
	arCur = 0;			// current armor
	arMax = 0;			// Max Armor
	damage_basic = 0;	// basic damage (melee)
	damage_range = 0;	// ranged damage

	textWidth = 10;	// TEMP? This might not be the right way to do this.  Texture Width
	textHeight = 10;	// TEMP? This might not be the right way to do this.  Texture Height
	elapsedTime = 0;
	body = NULL;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;		// TEMP?

//	objType = NONE;
//	setTeam(false);

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
			if(velocityMax) {
				b2Vec2 vel = body->GetLinearVelocity();
				vel.x = b2Min( vel.x + 0.1f,  velocityMax );
				body->SetLinearVelocity( vel );
			}

			t_move.Calculate_Ellapsed_Time();
			if(t_move.TotalTime() >= TIMER_SOUND_MOVE) {
				SoundManager::Sounds soundID;
				switch(objID) {
					case Settings::OBJ_T_ARCHER: soundID = sm.SND_ARCHER_MOVE; break;
					case Settings::OBJ_T_STONEWALL: soundID = sm.SND_STONEWALL_MOVE; break;
		//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
		//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
		//			case settings.OBJ_T_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
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
	if(enemy->isAlive()) {
		// SFX
		t_melee.Calculate_Ellapsed_Time();
		if(t_melee.TotalTime() >= TIMER_SOUND_MELEE) {
			SoundManager::Sounds soundID;
			switch(objID) {
				case Settings::OBJ_T_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
				case Settings::OBJ_T_STONEWALL: soundID = sm.SND_STONEWALL_MELEE; break;
	//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
	//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
	//			case settings.OBJ_T_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
				default: soundID = sm.SND_ARCHER_DAMAGED; break;
			}
			sm.playSound(soundSourceID, soundID, body->GetPosition());
			t_melee.Reset(0.0);
		}

		// DAMAGE ENEMY
		enemy->damage(getDamage(), sm);

		// Special Behavior (defined in derived classes)
		attackSpecial(enemy, sm);
	}
}


void GameObj::death(SoundManager &sm) { 
	// SFX
	t_death.Calculate_Ellapsed_Time();
	if(t_death.TotalTime() >= TIMER_SOUND_DEATH) {
		SoundManager::Sounds soundID;
		switch(objID) {
			case Settings::OBJ_T_ARCHER: soundID = sm.SND_ARCHER_DEATH; break;
			case Settings::OBJ_T_STONEWALL: soundID = sm.SND_STONEWALL_DEATH; break;
	//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
	//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
	//			case settings.OBJ_T_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
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
		switch(objID) {
			case Settings::OBJ_T_ARCHER: soundID = sm.SND_ARCHER_DAMAGED; break;
			case Settings::OBJ_T_STONEWALL: soundID = sm.SND_STONEWALL_DAMAGED; break;
	//			case settings.OBJ_T_DOG: soundID = sm.SND_DOG_MELEE; break;
	//			case settings.OBJ_T_SPEARMAN: soundID = sm.SND_SPEARMAN_MELEE; break;
	//			case settings.OBJ_T_ARCHER: soundID = sm.SND_ARCHER_MELEE; break;
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

void GameObj::update(SoundManager &sm) {
//	this->elapsedTime = elapsedTime;
	// TO DO - Add all update functionality such as collision, movement, attacking, dying.

	if(isAlive()) {
		move(sm);

		for(std::list<GameObj*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
			if((*it)->isAlive()) {
				attack((*it), sm);
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
	glLoadIdentity();

	if(enemies.size() == 0)
		glColor3f(DEF_DRAW_COLOR.r, DEF_DRAW_COLOR.g, DEF_DRAW_COLOR.b);
	else glColor3f(CONTACT_DRAW_COLOR.r, CONTACT_DRAW_COLOR.g, CONTACT_DRAW_COLOR.b);

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
			glVertex2d( -Util::meter2Pixel(textWidth)/2, Util::meter2Pixel(textHeight)/2);              // Top Left
			glTexCoord2f(1, 1);																		// Top Right
			glVertex2d(Util::meter2Pixel(textWidth)/2, Util::meter2Pixel(textHeight)/2);              // Top Right
			glTexCoord2f(1,  0);																	// Bottom Right
			glVertex2d(Util::meter2Pixel(textWidth)/2, -Util::meter2Pixel(textHeight)/2);              // Bottom Right
			glTexCoord2f(0, 0);																	// Bottom Left
			glVertex2d( - Util::meter2Pixel(textWidth)/2, -Util::meter2Pixel(textHeight)/2);      // Bottom Left
		glEnd();                            // Done Drawing The Quad
		//glBegin(GL_QUADS);                      // Draw A Quad
		//	glTexCoord2f(0, 1);																			// Top Left
		//	glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Left
		//	glTexCoord2f(1, 1);																		// Top Right
		//	glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Right
		//	glTexCoord2f(1,  0);																	// Bottom Right
		//	glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
		//	glTexCoord2f(0, 0);																	// Bottom Left
		//	glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
		//glEnd();                            // Done Drawing The Quad
		glDisable(GL_TEXTURE_2D); //Switch back to using colors instead of textures

	} else {		// NO TEXTURES

//		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*settings).depth());       // Move to 0,0 in bottom left corner of coord system
		glBegin(GL_QUADS);                      // Draw A Quad
			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Left
			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Right
			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
		glEnd();                            // Done Drawing The Quad

	}	

//	text.text(name, posX - (name.length()/2), textHeight, settings.depth());
	std::stringstream ss;
	ss << name << " " << "x=" << body->GetPosition().x << " y=" << body->GetPosition().y;
	std::stringstream ss2;
	ss2 << "hp=" << getHP() << " enemies=" << enemies.size();
	text.text(ss, body->GetPosition().x, body->GetPosition().y+textHeight + 20, settings->depth());
	text.text(ss2, body->GetPosition().x, body->GetPosition().y+textHeight + 10, settings->depth());
}



// calculates velocity vectors
//void GameObj::recalculate() {
//	velX = velocity * std::cos(Util::deg2Rad(angle));
//	velY = velocity * std::sin(Util::deg2Rad(angle));
//
//
//}



void GameObj::addContact(GameObj *enemy) {
	if(enemy->isNPC() != isNPC()) {
//		contacts++; 
		addEnemy(enemy); 
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
	fixtureDef.density = density;			// Set the box density to be non-zero, so it will be dynamic.	
	fixtureDef.friction = friction;			// Override the default friction.
	fixtureDef.filter = getFixtureCollisionFilter();
//	fixtureDef.filter.maskBits = getFixtureCollissionFilter().maskBits;


	body->SetLinearVelocity(b2Vec2(velocityMax, 0.0));
	body->CreateFixture(&fixtureDef);		// Add the shape to the body.

}


// Build collision filters based on object types and team
b2Filter GameObj::getFixtureCollisionFilter() {
	b2Filter filter;

	// ATTACKERS
	if(this->isNPC()) {
		if(getType() == BULLET) {
			filter.categoryBits = COLLISION_GROUP_NPC_BULLET;		// NPC BULLET GROUP
			filter.maskBits = COLLISION_GROUP_PC_DEFENDER + COLLISION_GROUP_GROUND;		// List of possible targets
		} else {
			filter.categoryBits = COLLISION_GROUP_NPC_ATTACKER;		// NPC ATTACKER GROUP
//			filter.maskBits = COLLISION_GROUP_PC_DEFENDER + COLLISION_GROUP_PC_BULLET;		// List of possible targets
		}
	
	// DEFENDERS	
	} else {
		if(getType() == BULLET) {
			filter.categoryBits = COLLISION_GROUP_PC_BULLET;		// PC BULLET GROUP
			filter.maskBits = COLLISION_GROUP_NPC_ATTACKER + COLLISION_GROUP_GROUND;		// List of Possible targets
		} else {
			filter.categoryBits = COLLISION_GROUP_PC_DEFENDER;		// PC ATTACKER GROUP
			//filter.maskBits = COLLISION_GROUP_PC_BULLET;		// PC defenders don't collide with defender bullets  // this may change!
		}
	}
	
	return filter;
}
