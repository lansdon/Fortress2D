#include "GUIButton.h"


GUIButton::GUIButton(WinParems *parems)
{
	setWinParems(parems);
	width = 50;
	height = 20;
	posX = 0;
	posY = 0;
	border = 4;
	label = "New Button";
	clr_bg.setColors(0, 0, 0, .5);
	clr_font.setColors(1, 1, 1, 1);
	clr_border.setColors(1, 1, 1, 1);
	clr_bg_h.setColors(0, .5, 0, .5);
	clr_font_h.setColors(0, 0, 0, 1);
	activated = false;
	parent = NULL;				// defaults to window
	font = GLUT_BITMAP_HELVETICA_12;
}


GUIButton::~GUIButton(void)
{
}


void GUIButton::draw() {
	// Outside box  (border)
	glLoadIdentity();
	glColor3f(clr_border.r, clr_border.g, clr_border.b);
//	glTranslatef((GLfloat)posX-(winParems->width()/2), (GLfloat)posY - winParems->height()/2, (GLfloat)winParems->depth());       // Top left corner button
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2d(posX, posY);              // Top Left
		glVertex2d(posX+width, posY);              // Top Right
		glVertex2d(posX+width, posY-height);              // Bottom Right
		glVertex2d(posX, posY-height);              // Bottom Left
	glEnd();                            // Done Drawing The Quad
	// Inside box  (background)
	glLoadIdentity();
	glColor3f(getColorBG().r, getColorBG().g, getColorBG().b);
//	glTranslatef((GLfloat)(getPosX()-(winParems->width()/2))+getBorder(), (GLfloat)(getPosY()) - winParems->height()/2 -getBorder(), (GLfloat)winParems->depth());       // Top left corner button
//	glTranslatef((GLfloat)(posX-winParems->width()/2)+border, (GLfloat)posY - (winParems->height()/2)-border, (GLfloat)winParems->depth());       // Top left corner button
	glBegin(GL_QUADS);										// Draw A Quad
		glVertex2d(posX+getBorder(), posY-getBorder());									// Top Left
		glVertex2d(posX+width-border, posY-getBorder());					// Top Right
		glVertex2d(posX+width-border, posY-height+border);   // Bottom Right
		glVertex2d(posX+getBorder(), posY-height+border);					// Bottom Left
	glEnd();												// Done Drawing The Quad

	// Label
	glColor3f(getColorFont().r, getColorFont().g, getColorFont().b);
	int labelWidth = glutBitmapLength(font, (unsigned char*)label.c_str());
	int labelHeight = glutBitmapHeight(font);
	text.text(label, posX + (width/2)-(labelWidth/2), posY-height/2-labelHeight/2, winParems->depth());

	// TEMP TESTING
	//for(int adj = 0; adj < 20; ++adj) {

	//	text.text(label, posX+(adj*4), posY-(adj*4), winParems->depth()+1);
	//}

}


bool GUIButton::activate(Vector3 coord) {			// activates the button if mouse coords match button location

	if( (coord.x() > posX && coord.x() < (posX + width)) &&				// valid x coord
		(coord.y() < posY && coord.y() > (posY - height)) )  {			// valid y coord
		activated = true;
		return true;
	}
	return false;
}


bool GUIButton::isActivated(bool reset) {	// check if activated
	if(activated) {	
		if(reset)
			activated = false; // optional reset
		return true;
	} else {
		return false;
	}
}


Util::Color GUIButton::getColorBG() {
	if(activated)
		return clr_bg_h;
	else return clr_bg;
}

Util::Color GUIButton::getColorFont() {
	if(activated)
		return clr_font_h;
	else return clr_font;
}
