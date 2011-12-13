#include "GLText.h"


GLText::GLText(Settings *settings, int size, std::string fontName)
{
	this->settings = settings;
	this->fontName = fontName;
	this->fontSize = size;
	fontBuilt = false;
//	BuildFont(size, fontName);
}


GLText::~GLText(void)
{
	KillFont();
}




GLvoid GLText::BuildFont(int size, std::string fontName) { 						// Build Our Bitmap Font
//	if(fontBuilt) return; // only build once
//
//	HFONT	font;										// Windows Font ID
//	HFONT	oldfont;									// Used For Good House Keeping
//
//	base = glGenLists(96);								// Storage For 96 Characters
//
//	font = CreateFont(	-size,							// Height Of Font
//						0,								// Width Of Font
//						0,								// Angle Of Escapement
//						0,								// Orientation Angle
//						FW_BOLD,						// Font Weight
//						FALSE,							// Italic
//						FALSE,							// Underline
//						FALSE,							// Strikeout
//						ANSI_CHARSET,					// Character Set Identifier
//						OUT_TT_PRECIS,					// Output Precision
//						CLIP_DEFAULT_PRECIS,			// Clipping Precision
//						ANTIALIASED_QUALITY,			// Output Quality
//						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
//						fontName.c_str());					// Font Name
////						"Courier New");					// Font Name
//
//	oldfont = (HFONT)SelectObject((*settings).hdc(), font);           // Selects The Font We Want
//	wglUseFontBitmaps((*settings).hdc(), 32, 96, base);				// Builds 96 Characters Starting At Character 32
//	SelectObject((*settings).hdc(), oldfont);							// Selects The Font We Want
//	DeleteObject(font);									// Delete The Font
//	fontBuilt = true;
}

GLvoid GLText::KillFont(GLvoid) {									// Delete The Font List
	glDeleteLists(base, 96);							// Delete All 96 Characters
}


// Print text to the screen at x, y.  ToDO - Add support for variable font size! (and font tracking)
void GLText::text(std::stringstream &ss, double x, double y, double z, int size) {
	text(ss.str(), x, y, z, size);
}

// Print text to the screen at x, y.  ToDO - Add support for variable font size! (and font tracking)
void GLText::text(std::string &str, double x, double y, double z, int size) {
	//BuildFont();
	//glLoadIdentity();                       // Reset The View
	//glTranslatef((GLfloat)(*settings).width()/-2, (GLfloat)(*settings).height()/-2, z + 1);       // Move to 0,0 in bottom left corner of coord system
	//glRasterPos2f(x, y);
	//glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	//glListBase(base - 32);								// Sets The Base Character to 32
	//glCallLists(strlen(str.c_str()), GL_UNSIGNED_BYTE, str.c_str());	// Draws The Display List Text
	//glPopAttrib();										// Pops The Display List Bits


	glLoadIdentity();                       // Reset The View
//	glTranslatef((GLfloat)0, (GLfloat)0, z + 1);       // Move to 0,0 in bottom left corner of coord system
//	glTranslatef((GLfloat)(*settings).width()/-2, (GLfloat)(*settings).height()/-2, z + 1);       // Move to 0,0 in bottom left corner of coord system
	glRasterPos2f(x, y);

	glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char*)(str.c_str()));
}

