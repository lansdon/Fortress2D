#include "Launcher.h"


Launcher::Launcher(WinParems *parems, int x, int y) : GameObj(parems, x, y)
{

	MIN_VEL = 0.5;			// Lower bounds of launch velocity meters/sec
	MAX_VEL = 10;			// Upper bounds of launch velocity meters/sec
	LEFT_ORIENTATION = true; // true = facing left    false = facing right
	MIN_ANGLE = -45.0;			// MIN angle allowed relative to direction facing (0 = horizontal plane. POS = up, neg = down.
	MAX_ANGLE = 85.0;			// degrees
	MAX_PULL_LENGTH = 75;		// (max length a user can pull on launcher to achieve max launch velocity. (meters)

	activated = false;

}


Launcher::~Launcher(void)
{
} 



bool Launcher::activate(b2Vec2 coord) {			// activates the button if mouse coords match button location
	double left = getPos().x - (Util::meter2Pixel(getTextWidth())/2);
	double right = getPos().x + (Util::meter2Pixel(getTextWidth())/2);
	double top = getPos().y + (Util::meter2Pixel(getTextHeight())/2);
	double bottom = getPos().y - (Util::meter2Pixel(getTextHeight())/2);

	if( (coord.x >= left && coord.x <= right) &&				// valid x coord
		(coord.y <= top  && coord.y >= bottom ) ) {			// valid y coord
		activated = true;
		return true;
	}
	return false;
}


bool Launcher::isActivated(bool reset) {	// check if activated
	if(activated) {	 
		if(reset)
			activated = false; // optional reset
		return true;
	} else {
		return false;
	}
}

void Launcher::setActivated(bool bActive) {
	activated = bActive;
}
void Launcher::draw(b2Vec2 mouse) {						// draw the object on screen
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

	// Draw user launch vector based on mouse coords
	if(activated) {
//		b2Vec2 origin(pos.x, pos.y); 
		double angle = Util::deg2Rad(calculateMouseAngle(mouse));			// Line angle from horizontal
		double mag = getLauncherDrawLength(mouse);			// Magnitude of line

//		b2Vec2 origin(getTextWidth()/2, getTextHeight()/2); 
		glLineWidth(2.0);
		glBegin(GL_LINES);                      // Draw A line
			glVertex2d(pos.x, pos.y);					// Origin
//			glVertex2d(mouse.x, mouse.y);					
			glVertex2d(pos.x + (mag * std::cos(angle)), pos.y + (mag * std::sin(angle)));				// End point
			//glVertex2d(pos.x + Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);              // Bottom Right
			//glVertex2d(pos.x - Util::meter2Pixel(textWidth)/2, pos.y - Util::meter2Pixel(textHeight)/2);      // Bottom Left
		glEnd();                            // Done Drawing The Quad

	}


//	text.text(name, posX - (name.length()/2), textHeight, winParems.depth());
	std::stringstream ss;
	ss << name << " " << "x=" << body->GetPosition().x << " y=" << body->GetPosition().y;
	std::stringstream ss2;
	ss2 << "hp=" << getHP() << " enemies=" << enemies.size();
	text.text(ss, body->GetPosition().x, body->GetPosition().y+textHeight*4, winParems->depth());
	text.text(ss2, body->GetPosition().x, body->GetPosition().y+textHeight*2.5, winParems->depth());
}


// Calculate angles with min/max restrictions
double Launcher::calculateMouseAngle(b2Vec2 mouse) {
	b2Vec2 pos = body->GetPosition();
	float mouseAngle = Util::rad2Deg(std::atan2(mouse.y - pos.y, mouse.x - pos.x));	// Angle of line to mouse coord
	float drawAngle = mouseAngle;

	if(drawAngle < -MAX_ANGLE) drawAngle = -MAX_ANGLE;
	else if(drawAngle > -MIN_ANGLE) drawAngle = -MIN_ANGLE;

//	float maxMouseAngle = 

	// set launch angle
	if(drawAngle < 0) launchAngle = drawAngle + 180;
	else launchAngle = drawAngle - 180;


	// Debug
	std::stringstream ss;
	ss << "Angle: " << drawAngle;
	text.text(ss, 500, 300, 0);


	return drawAngle;
}

// Calculate the length of the launch velocity line
double Launcher::getLauncherDrawLength(b2Vec2 mouse) {
	b2Vec2 pos = body->GetPosition();

	float mag = sqrt(std::pow(mouse.y - pos.y, 2) + std::pow(mouse.x - pos.x, 2));

	// Limit the length of the "pull string"
	if(mag > MAX_PULL_LENGTH) mag = MAX_PULL_LENGTH;

	// Set Launcher Initial Velocity
	launchVelocity = mag * (MAX_PULL_LENGTH / MAX_VEL);					// Vel based on pull string (mouse)
	if(launchVelocity < MIN_VEL) launchVelocity = MIN_VEL;				// Min Vel

	// Debug
	std::stringstream ss;
	ss << "Total Mag: " << mag;
	text.text(ss, 500, 260, 0);

	return mag;
}
//
//void Launcher::launch(void *go) {
//
//	GameObj* temp = go->makeArrow(body->GetPosition().x, body->GetPosition().y);
//	temp->setVecAngle(launchAngle);
////	temp->setVelocity(launchVelocity);
//	temp->body->SetLinearVelocity(b2Vec2(launchVelocity * std::cos(angle), launchVelocity * std::sin(angle)));
//}



