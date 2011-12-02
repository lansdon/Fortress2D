#include "Input.h"


Input::Input(WinParems *parems)
{
	winParems = parems;
//	text = new GLText(winParems);

	vKeys.resize(256);
	vMouseBtns.resize(2);

	//// Initialize keyboard and mouse button tracking vectors
	//for(int i=0; i<256; ++i) {
	//	buttonState temp;
	//	vKeys.push_back(temp);							// resize for 256 keys
	//}
	//for(int i=0; i<2; ++i) {
	//	buttonState temp;
	//	vMouseBtns.push_back(temp);						// support 2 buttons  (ignore slot zero)
	//}
}


Input::~Input()
{
}



void Input::update() {
	

	// TO DO

	// Check keyboard input
//	updateKeys();
	
	// check mouse input
	updateMouse();


	// DEBUG
	std::stringstream ss;
	ss << "MOUSE x=" << mouseCoord.x() << " Y=" << mouseCoord.y();
	text.text(ss, 400, 300, (*winParems).depth());

}



// Find mouse coordinates relative to openGL (mouse clicks handled by addevent()
void Input::updateMouse() {
	
//	POINT mouse;                        // Stores The X And Y Coords For The Current Mouse Position
//	GetCursorPos(&mouse);                   // Gets The Current Cursor Coordinates (Mouse Coordinates)
////	ScreenToClient((*winParems).hwnd(), &mouse);
//	
//	// TEMP GLUTFIX NEEDED!
//	mouse.x = 50; 
//	mouse.y = 50;
//	mouseCoord.set(mouse.x - ((*winParems).width()/2), ((*winParems).height()-mouse.y) - ((*winParems).height()/2), 0);  // reverse y coord to zero on bottom 

	//DEBUG
	std::stringstream ss;
	ss << "premouse x=" << mouseCoord.x() << " y=" << mouseCoord.y();
	text.text(ss, 650, 0, (*winParems).depth());
}
//
//Vector3 Input::getOGLPos(int x, int y)
//{
//    GLint viewport[4];
//    GLdouble modelview[16];
//    GLdouble projection[16];
//    GLfloat winX, winY, winZ;
//    GLdouble posX, posY, posZ;
// 
//    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
//    glGetDoublev( GL_PROJECTION_MATRIX, projection );
//    glGetIntegerv( GL_VIEWPORT, viewport );
// 
//    winX = (float)x;
//    winY = (float)viewport[3] - (float)y;
//    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
// 
//    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
//
//	//DEBUG
//	std::stringstream ss;
//	ss << "viewport x=" << viewport[0] << " y=" << viewport[1] << " width=" << viewport[2] << " height=" << viewport[3];
//	text.text(ss, 400, 275, (*winParems).depth());
//
//    return Vector3(posX, posY, posZ);
//}


void Input::updateKeys() {



}

//  OLD PRE GLUT 
//void Input::addEvent(UINT uMsgType, WPARAM wParam) {
//	switch(uMsgType) {
//		case WM_KEYDOWN:							// Is A Key Being Held Down?
//		{
//			vKeys[wParam].pressed = TRUE;					// If So, Mark It As TRUE
//		} break;
//
//		case WM_KEYUP:								// Has A Key Been Released?
//		{
//			vKeys[wParam].pressed = FALSE;					// If So, Mark It As FALSE
//		} break;
//		case WM_LBUTTONDOWN:								// Has A Key Been Released?
//		{
//			vMouseBtns[0].pressed = TRUE;					// If So, Mark It As FALSE
//		} break;
//		case WM_LBUTTONUP:								// Has A Key Been Released?
//		{
//			vMouseBtns[0].pressed = FALSE;					// If So, Mark It As FALSE
//		} break;
//		case WM_RBUTTONDOWN:								// Has A Key Been Released?
//		{
//			vMouseBtns[1].pressed = TRUE;					// If So, Mark It As FALSE
//		} break;
//		case WM_RBUTTONUP:								// Has A Key Been Released?
//		{
//			vMouseBtns[1].pressed = FALSE;					// If So, Mark It As FALSE
//		} break;
//
//	}
//
//
//}




bool Input::isKeyPressed(char *key) {			// returns true if key is pressed
	return isKeyPressed((unsigned int)key);
}


bool Input::isKeyPressed(unsigned int ascii) {			// returns true if key is pressed

	if (vKeys[ascii].pressed && !vKeys[ascii].held) {               // L Key Being Pressed Not Held?
		vKeys[ascii].held=TRUE;                // lp Becomes TRUE
	}
	if (!vKeys[ascii].pressed) {                 // Has L Key Been Released?
		vKeys[ascii].held=FALSE;               // If So, lp Becomes FALSE
	}

	if(vKeys[ascii].pressed)
		return true;
	else return false;


}

bool Input::isBtnPressed(unsigned int btnNum) {			// returns true if mouse button # was pressed

	if(btnNum > 1 || btnNum < 0)
		return false;

	if (vMouseBtns[btnNum].pressed && !vMouseBtns[btnNum].held) {               // L Key Being Pressed Not Held?
		vMouseBtns[btnNum].held=TRUE;                // lp Becomes TRUE
	}
	if (!vMouseBtns[btnNum].pressed) {                 // Has L Key Been Released?
		vMouseBtns[btnNum].held=FALSE;               // If So, lp Becomes FALSE
	}

	if(vMouseBtns[btnNum].pressed)
		return true;
	else return false;


}



Vector3 Input::getMousePos(bool ll_origin) { 
	//Vector3 mouse = mouseCoord;
	//if(ll_origin) {
	//	mouse.set(mouseCoord.x() + winParems->width()/2, mouseCoord.y() + winParems->height()/2, 0);
	//}
//	updateMouse(); 

	return mouseCoord; 
}



// NEW GLUT FUNCTIONS
void Input::addKeyDown(unsigned char key, int x, int y) {
	vKeys[key].pressed = TRUE;					// If So, Mark It As TRUE
	vKeys[key].x = x;
	vKeys[key].y = y;
}

void Input::addKeyUp( int key, int x, int y) {
	vKeys[key].pressed = FALSE;					// If So, Mark It As TRUE
	vKeys[key].x = x;
	vKeys[key].y = y;

}

// Do we need a seperate vector to hold these keys??
void Input::addSpecialDown( int key, int x, int y) {
	vKeys[key].pressed = TRUE;					// If So, Mark It As TRUE
	vKeys[key].x = x;
	vKeys[key].y = y;

}


void Input::addSpecialUp( int key, int x, int y) {
	vKeys[key].pressed = TRUE;					// If So, Mark It As TRUE
	vKeys[key].x = x;
	vKeys[key].y = y;
}


void Input::addMouseEvent(int button, int state, int x, int y) {
	setMousePos(x, y);
	if(vMouseBtns.size() < button+1) vMouseBtns.resize(button+1);

	vMouseBtns[button].pressed = state;					// If So, Mark It As FALSE
	vMouseBtns[button].x = x;
	vMouseBtns[button].y = y;
}

void Input::setMousePos(int x, int y) {
	y = winParems->height()-y;
	mouseCoord.set(x, y, 0);

// EVENT driven won't display on screen !!!
	//std::stringstream ss;
	//ss << "mouse=(" << x << "," << y << ")";
	//text.text(ss.str(), x, y, winParems->depth());
	//text.text(ss.str(), 300, 300, winParems->depth());
}
