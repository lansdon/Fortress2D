#pragma once


#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <string>
#include <sstream>
#include "WinParems.h"
#include <gl\freeglut.h>

class GLText
{
public:
	GLText(WinParems *parems = NULL, int size = 12, std::string fontName = "Courier New");
	~GLText(void);
	// Text Functions
	GLvoid BuildFont(int size = 12, std::string fontName = "Courier New");
	GLvoid KillFont(GLvoid);
	void text(std::stringstream &ss, double x, double y, double z, int size = 12); // Print routine that allows coord specifications
	void text(std::string &str, double x, double y, double z, int size = 12); // overloaded Print routine that allows coord specifications
	void setWinParems(WinParems *parems) { winParems = parems; }



private:
	GLuint	base;				// Base Display List For The Font Set
	std::string fontName;
	unsigned int fontSize;
	bool fontBuilt;
	WinParems *winParems;


};

