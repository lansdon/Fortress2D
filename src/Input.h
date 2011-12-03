#pragma once

#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "WinParems.h"
#include "Vector3.h"
#include "GLText.h"
#include <sstream>
#include <vector>



class Input
{
public:
	Input(WinParems *parems = NULL);
	~Input();

	struct buttonState {
		buttonState() { state = GLUT_KEY_UP; } // 
		int state;
//		bool held;
		int x, y;
	};


	void setWinParems(WinParems *parems) { winParems = parems; text.setWinParems(parems); }
	void update();						// General update routine every frame
	std::vector<buttonState> &getKeys() { return vKeys; }		//vector containing key press information (index 0=key pressed? index 1 = key held?)
	std::vector<buttonState> &getClicks() { return vMouseBtns; }		//vector containing button press information (index 0=btn pressed? index 1 = btn held?)
	Vector3 getMousePos();
//	void addEvent(UINT uMsgType, WPARAM wParam);
	bool isKeyPressed(char *key);			// returns true if key is pressed
	bool isKeyPressed(unsigned int ascii);			// returns true if key is pressed
//	bool isKeyHeld(char *key);			// returns true if key is pressed
//	bool isKeyHeld(unsigned int ascii);			// returns true if key is pressed
	bool isBtnPressed(unsigned int btnNum);			// returns true if mouse button # was pressed
//	bool isBtnHeld(unsigned int btnNum) { return vMouseBtns[btnNum].held; }			// returns true if mouse button # was pressed


	// NEW GLUT FUNCTIONS
	void addKeyDown(unsigned char key, int x, int y);
	void addKeyUp( int key, int x, int y);
	void addSpecialDown( int key, int x, int y);
	void addSpecialUp( int key, int x, int y);
	void addMouseEvent(int button, int state, int x, int y);
	buttonState getButtonState(int button);
	buttonState getKeyState(unsigned char key);
	void setMousePos(int x, int y);


	WinParems *winParems;
	GLText text;



private:

	Vector3 mouseCoord;
	std::vector<buttonState> vKeys;		//vector containing key press information (index 0=key pressed? index 1 = key held?)
	std::vector<buttonState> vMouseBtns;		//vector containing button press information (index 0=btn pressed? index 1 = btn held?)

	void updateMouse();			// updates mouse variable with current mouse pos
	void updateKeys();			



//	Vector3 getOGLPos(int x, int y);	// Converts screen coords to GL coords

};

