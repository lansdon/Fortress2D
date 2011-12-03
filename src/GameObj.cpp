#include "GameObj.h"


GameObj::GameObj(WinParems *parems, double x, double y) {

	this->winParems = parems;
	text.setWinParems(parems);

	//posX = posY = 0;
	velocityMax = 0;		// pixels per second
	//angle = 0;		// 0 = right   180 = left   90 = up
	//velX = (velocity * std::cos(Util::deg2Rad(angle))) * elapsedTime;
	//velY = (velocity * std::sin(Util::deg2Rad(angle))) * elapsedTime;
	hpCur = 0;			// current hitpoints
	hpMax = 0;			// max hitpoints
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

	objType = NONE;
	setTeam(false);

	// Load texture
	textureID = TextureLoader::LoadGLTextures("test.png");
}


GameObj::~GameObj(void)
{
	winParems->getWorld()->DestroyBody(body);	// Clean up B2Body Objects

}




void GameObj::move() {
	if(body) {
		b2Vec2 vel = body->GetLinearVelocity();
		vel.x = b2Min( vel.x + 0.1f,  velocityMax );
		body->SetLinearVelocity( vel );
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

//	enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	std::list<GameObj*>::iterator it = enemies.begin();

	while(it != enemies.end()) {
		if((*it) == enemy) {
			it = enemies.erase(it);
		} else {
			++it;
		}
	}
}


void GameObj::attack(GameObj *enemy) {
	if(enemy->isAlive()) {
		enemy->damage(getDamage());
	}
}


void GameObj::death() { 


}


void GameObj::damage(int amount) {
	if(getArmor() > amount)
		return;				// armor negates all damage
	else amount -= getArmor();
	setHP(getHP() - amount);

	if(getHP() < 0) {
		death();
	}
}

void GameObj::update(double elapsedTime) {
	this->elapsedTime = elapsedTime;
	// TO DO - Add all update functionality such as collision, movement, attacking, dying.

	if(isAlive()) {
		move();
		draw();

		for(std::list<GameObj*>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
			if(!(*it)->isAlive()) {
				it = enemies.erase(it);           // Change elemnts to be removed to NULL
			} else {
				attack((*it));
			}
		}
//		cleanEnemiesList();

	} else {
		body->SetTransform(b2Vec2(-5000, -5000), 0.0);
	}

//	move();

}


bool GameObj::isAlive() {
	if(getHP() > 0) 
		return true; 
	else{

	return false; 
	}
}



// remove dead enemies from the list
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


void GameObj::draw() {						// draw the object on screen
		// TEMP - draw function for testing
	glLoadIdentity();

	if(enemies.size() == 0)
		glColor3f(DEF_DRAW_COLOR.r, DEF_DRAW_COLOR.g, DEF_DRAW_COLOR.b);
	else glColor3f(CONTACT_DRAW_COLOR.r, CONTACT_DRAW_COLOR.g, CONTACT_DRAW_COLOR.b);

	b2Vec2 pos = body->GetPosition();
	if(winParems->useTextures()) {
		glEnable(GL_TEXTURE_2D); //Switch back to using colors instead of textures
		glBindTexture(GL_TEXTURE_2D, textureID);
 		glColor3f(1, 1, 1);
		 //Use blurry texture mapping (replace GL_LINEAR with GL_NEAREST for blocky)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   
//		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*winParems).depth());       // Move to 0,0 in bottom left corner of coord system
		glBegin(GL_QUADS);                      // Draw A Quad
			glTexCoord2f(0, 1);																			// Top Left
			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Left
			glTexCoord2f(1, 1);																		// Top Right
			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Right
			glTexCoord2f(1,  0);																	// Bottom Right
			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
			glTexCoord2f(0, 0);																	// Bottom Left
			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
		glEnd();                            // Done Drawing The Quad
		glDisable(GL_TEXTURE_2D); //Switch back to using colors instead of textures

	} else {		// NO TEXTURES

//		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*winParems).depth());       // Move to 0,0 in bottom left corner of coord system
		glBegin(GL_QUADS);                      // Draw A Quad
			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Left
			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Right
			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
		glEnd();                            // Done Drawing The Quad


	}	


//	text.text(name, posX - (name.length()/2), textHeight, winParems.depth());
	std::stringstream ss;
	ss << name << " " << "x=" << body->GetPosition().x << " y=" << body->GetPosition().y;
	std::stringstream ss2;
	ss2 << "hp=" << getHP() << " enemies=" << enemies.size();
	text.text(ss, (body->GetPosition().x+(*winParems).width()/2), (body->GetPosition().y+((*winParems).height()/2))+textHeight*3, (*winParems).depth());
	text.text(ss2, (body->GetPosition().x+(*winParems).width()/2), (body->GetPosition().y+((*winParems).height()/2))+textHeight*2.5, (*winParems).depth());
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
	bodyDef.linearVelocity(Util::meter2Pixel(5));
	bodyDef.userData = this;
	body = winParems->getWorld()->CreateBody(&bodyDef);
	dynamicBox.SetAsBox(Util::meter2Pixel(getTextWidth())/2,Util::meter2Pixel(getTextHeight())/2);	// Define another box shape for our dynamic body.
	fixtureDef.shape = &dynamicBox;			// Define the dynamic body fixture.
	fixtureDef.density = density;			// Set the box density to be non-zero, so it will be dynamic.	
	fixtureDef.friction = friction;			// Override the default friction.
	body->SetLinearVelocity(b2Vec2(velocityMax, 0.0));
	body->CreateFixture(&fixtureDef);		// Add the shape to the body.

}

