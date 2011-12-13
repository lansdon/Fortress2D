#pragma once
#include "GUIButton.h"
#include <vector>

/*
	Class to handle a collection of GUIButtons
*/

class GUIButtonMenu : public GUIButton
{
public:
	GUIButtonMenu(Settings *settings);
	~GUIButtonMenu(void);
	GUIButton& newButton(std::string label, int targRow, int targCol);
	void setDimensions(int newRows, int newCols);
	GUIButton &getButton(int row, int col);
	void GUIButtonMenu::draw();
	void setSettings(Settings *settings);

	bool GUIButtonMenu::activate(Vector3 mouse);			// activate buttons that mouse is clicking
	Vector3 getActiveButton();					// checks child obejcts to see if clicked... true if a button is pressed
	void processButton(int r, int c);
	void setButtonLabel(int r, int c, std::string str);
	Vector3 getDimensions() { return Vector3(rows, cols, 0); }

private:

	std::vector<std::vector<GUIButton>> buttons;
	int rows, cols;						// Menu Grid
	Settings *settings;
	float btnWidth, btnHeight;			// width and height of child buttons
};

