#include "GLText.h"


GLText::GLText(Settings *settings, int size, std::string fontName)
{
	this->settings = settings;
	this->fontName = fontName;
	this->fontSize = size;
}


GLText::~GLText(void)
{
}




// Print text to the screen at x, y.  ToDO - Add support for variable font size! (and font tracking)
void GLText::text(std::stringstream &ss, double x, double y, double z, int size) {
	text(ss.str(), x, y, z, size);
}

// Print text to the screen at x, y.  ToDO - Add support for variable font size! (and font tracking)
void GLText::text(std::string &str, double x, double y, double z, int size) {

	glLoadIdentity();                       // Reset The View
	glRasterPos2f(x, y);

	switch(size) {
		case 12: glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)(str.c_str())); break;
		case 18: glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)(str.c_str())); break;
		default: glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)(str.c_str())); break;
	}
}

