#include "GOArcherTower.h"


GOArcherTower::GOArcherTower(Settings *settings, double x, double y) : Launcher(settings, x, y)
{
	
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("archertower.dat", x, y);

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
//	if(settings->useTextures()) {
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
////		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*settings).depth());       // Move to 0,0 in bottom left corner of coord system
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
////		glTranslatef(body->GetPosition().x, body->GetPosition().y, (*settings).depth());       // Move to 0,0 in bottom left corner of coord system
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
////	text.text(name, posX - (name.length()/2), textHeight, settings.depth());
//	std::stringstream ss;
//	ss << name << " " << "x=" << body->GetPosition().x << " y=" << body->GetPosition().y;
//	std::stringstream ss2;
//	ss2 << "hp=" << getHP() << " enemies=" << enemies.size();
//	text.text(ss, body->GetPosition().x, body->GetPosition().y+textHeight*4, settings->depth());
//	text.text(ss2, body->GetPosition().x, body->GetPosition().y+textHeight*2.5, settings->depth());
//}
//
