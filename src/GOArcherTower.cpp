#include "GOArcherTower.h"


GOArcherTower::GOArcherTower(WinParems *parems, double x, double y) : Launcher(parems, x, y)
{
	hpCur = 80;			// current hitpoints
	hpMax = 80;			// max hitpoints
	arCur = 5;			// current armor
	arMax = 5;			// Max Armor
	damage_basic = 0;	// basic damage (melee)
	damage_range = 0;	// ranged damage
	setVelocity(0);		// max velocity (m/s)

	textWidth = 3;	// TEMP? This might not be the right way to do this.  Texture Width (METERS)
	textHeight = 5;	// TEMP? This might not be the right way to do this.  Texture Height (METERS)
	elapsedTime = 0;
	body = NULL;

	density = 1.0;
	friction = 1.03;
	velocityMax = 0;

	DEF_DRAW_COLOR.setColors(1, 1, 1, 1);
	CONTACT_DRAW_COLOR.setColors(1, 0, 0, 1);

	contacts = 0;

	objType = OBJECT_TYPE::DEFENDER;
	objID = WinParems::OBJ_T_ARCHER_TOWER;

	setupB2D(x, y);

	setTeam(false); // NPC team

	textureID = TextureLoader::LoadGLTextures("archer.jpg");


	// Launcher Vars
	//	float MIN_VEL;			// Lower bounds of launch velocity meters/sec
	//float MAX_VEL;			// Upper bounds of launch velocity meters/sec
	//bool LEFT_ORIENTATION; // true = facing left    false = facing right
	//int MIN_ANGLE;			// MIN angle allowed (0 = horizontal plane. POS = up, neg = down.
	//int MAX_ANGLE;
	//int MAX_PULL_LENGTH;		// (max length a user can pull on launcher to achieve max launch velocity. (pixels)


	//// Variables
	//int launchAngle;		// User defined current launch angle
	//int launchVelocity;		// Speed the ammo is launched at
	//bool activated;			// true if user is currently clicking on the launcher


}


GOArcherTower::~GOArcherTower()
{
}

bool GOArcherTower::activate(Vector3 coord) {			// activates the button if mouse coords match button location

	if( (coord.x() > this->getPos().x && coord.x() < (getPos().x + this->getTextWidth())) &&				// valid x coord
		(coord.y() < this->getPos().y && coord.y() > (this->getPos().y - getTextHeight())) )  {			// valid y coord
		activated = true;
		return true;
	}
	return false;
}


bool GOArcherTower::isActivated(bool reset) {	// check if activated
	if(activated) {	
		if(reset)
			activated = false; // optional reset
		return true;
	} else {
		return false;
	}
}

void GOArcherTower::setActivated(bool bActive) {
	activated = bActive;
}
//void GOArcherTower::draw(b2Vec2 mouse) {						// draw the object on screen
//		// TEMP - draw function for testing
//	glLoadIdentity();
//
//	if(enemies.size() == 0)
//		glColor3f(DEF_DRAW_COLOR.r, DEF_DRAW_COLOR.g, DEF_DRAW_COLOR.b);
//	else glColor3f(CONTACT_DRAW_COLOR.r, CONTACT_DRAW_COLOR.g, CONTACT_DRAW_COLOR.b);
//
//	b2Vec2 pos = body->GetPosition();
//	if(winParems->useTextures()) {
//		glEnable(GL_TEXTURE_2D); //Switch back to using colors instead of textures
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glColor3f(1, 1, 1);
//		 //Use blurry texture mapping (replace GL_LINEAR with GL_NEAREST for blocky)
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
//	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL );
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
//   
////		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*winParems).depth());       // Move to 0,0 in bottom left corner of coord system
//		glBegin(GL_QUADS);                      // Draw A Quad
//			glTexCoord2f(0, 1);																			// Top Left
//			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Left
//			glTexCoord2f(1, 1);																		// Top Right
//			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Right
//			glTexCoord2f(1,  0);																	// Bottom Right
//			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
//			glTexCoord2f(0, 0);																	// Bottom Left
//			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
//		glEnd();                            // Done Drawing The Quad
//		glDisable(GL_TEXTURE_2D); //Switch back to using colors instead of textures
//
//	} else {		// NO TEXTURES
//
////		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*winParems).depth());       // Move to 0,0 in bottom left corner of coord system
//		glBegin(GL_QUADS);                      // Draw A Quad
//			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Left
//			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y + Util::meter2Pixel(textHeight)/2);              // Top Right
//			glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
//			glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
//		glEnd();                            // Done Drawing The Quad
//
//	}	
//
//	// Draw user launch vector based on mouse coords
//	if(activated) {
//		b2Vec2 origin(getTextWidth()/2, getTextHeight()/2); 
//		glLineWidth(2.0);
//		glBegin(GL_LINES);                      // Draw A line
//			glVertex2d(0, 0);              // Top Left
//			glVertex2d(mouse.x, mouse.y);              // Top Right
//			//glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
//			//glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
//		glEnd();                            // Done Drawing The Quad
//
//	}
//
//
////	text.text(name, posX - (name.length()/2), textHeight, winParems.depth());
//	std::stringstream ss;
//	ss << name << " " << "x=" << body->GetPosition().x << " y=" << body->GetPosition().y;
//	std::stringstream ss2;
//	ss2 << "hp=" << getHP() << " enemies=" << enemies.size();
//	text.text(ss, body->GetPosition().x, body->GetPosition().y+textHeight*4, winParems->depth());
//	text.text(ss2, body->GetPosition().x, body->GetPosition().y+textHeight*2.5, winParems->depth());
//}
//
