#pragma once
#include <string>
#include "Util.h"
#include "Vector3.h"
#include "WinParems.h"
#include "GLText.h"

class GUIButton
{
public:
	GUIButton(WinParems *parems = NULL);
	~GUIButton(void);
	void setWidth(float w) { width = w; }
	void setHeight(float h) { height = h; }
	void setPos(float x, float y) { posX=x; posY=y; }
	void setLabel(std::string str) { label = str; }
	void setColorBG(Util::Color bg) { clr_bg = bg; }
	void setColorFont(Util::Color font) { clr_font = font; }
	void setColorBorder(Util::Color border) { clr_border = border; }
	void setBorder(float size) { border = size; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	float getPosX() { return posX; }
	float getPosY() { return posY; }
	float getBorder() { return border; }
	//Util::Color getBGColor() { return clr_bg; }
	//Util::Color getFontColor() { return clr_font; }
	void setWinParems(WinParems *parems) {winParems = parems; text.setWinParems(parems); }

	bool setActive(bool bActive) { activated = bActive; return activated;}
	virtual void draw();
	bool activate(Vector3 coord);			// activates the button if mouse coords match button location
	bool isActivated(bool reset = false);	// check if activated

	Util::Color getColorBG();
	Util::Color getColorFont();
	Util::Color getColorBorder() {return clr_border; }

	void setFont(void *newFont) { font = newFont; }
	void* getFont() { return font; }


//	enum BUTTON_TYPE { NULL, SWALL, WWALL, 
private:
	float width, height, posX, posY, border;
	std::string label;
	Util::Color clr_bg, clr_font, clr_border, clr_bg_h, clr_font_h;
	bool activated;
	
	WinParems *winParems;

	GLText text;

	GUIButton *parent; // parent container    null = relative to window

	void *font;
	// Need graphic support



};

