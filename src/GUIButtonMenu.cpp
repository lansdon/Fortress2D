#include "GUIButtonMenu.h"


GUIButtonMenu::GUIButtonMenu(WinParems *parems) : GUIButton(parems)
{
	winParems = parems;
	rows = cols = 1;
	
	setDimensions(rows, cols);
}


GUIButtonMenu::~GUIButtonMenu(void)
{
}

void GUIButtonMenu::setWinParems(WinParems *parems) {
	winParems = parems;
	setDimensions(rows, cols);
}


GUIButton &GUIButtonMenu::newButton(std::string label, int targRow, int targCol) {
	GUIButton temp(winParems);
	buttons[targRow][targCol] = temp;
	return buttons[targRow][targCol];
}

void GUIButtonMenu::setDimensions(int newRows, int newCols) {
	rows = newRows;
	cols = newCols;
	btnWidth = getWidth() / cols;
	btnHeight = getHeight() / rows;
	buttons.resize(rows);
	for(int i=0; i<rows; ++i) {
		buttons[i].resize(cols);
		for(int j=0; j<cols; ++j) {
			buttons[i][j].setPos(getPosX()+(btnWidth*j), getPosY()-(btnHeight*i));
			buttons[i][j].setHeight(btnHeight);
			buttons[i][j].setWidth(btnWidth);
			buttons[i][j].setWinParems(winParems);
		}
	}
}

GUIButton &GUIButtonMenu::getButton(int row, int col) {
	return buttons[row][col];
}



void GUIButtonMenu::draw() {
	// Outside box  (border)
	glLoadIdentity();
	glColor3f(getColorBorder().r, getColorBorder().g, getColorBorder().b);
//	glTranslatef((GLfloat)getPosX()-(winParems->width()/2), (GLfloat)getPosY() - winParems->height()/2, (GLfloat)winParems->depth());       // Top left corner button
	glBegin(GL_QUADS);                      // Draw A Quad
		glVertex2d(getPosX(), getPosY());              // Top Left
		glVertex2d(getWidth(), getPosY());              // Top Right
		glVertex2d(getWidth(), getPosY()-getHeight());              // Bottom Right
		glVertex2d(getPosX(), getPosY()-getHeight());              // Bottom Left
	glEnd();                            // Done Drawing The Quad
	// Inside box  (background)
	glLoadIdentity();
	glColor3f(getColorBG().r, getColorBG().g, getColorBG().b);
//	glTranslatef((GLfloat)(getPosX()-(winParems->width()/2))+getBorder(), (GLfloat)(getPosY()) - winParems->height()/2 -getBorder(), (GLfloat)winParems->depth());       // Top left corner button
	glBegin(GL_QUADS);										// Draw A Quad
		glVertex2d(getPosX() + getBorder(), getPosY() - getBorder());									// Top Left
		glVertex2d(getPosX() + getWidth() - getBorder(), getPosY() - getBorder());					// Top Right
		glVertex2d(getPosX() + getWidth()-getBorder(), getPosY()-getHeight()+getBorder());   // Bottom Right
		glVertex2d(getPosX() + getBorder(), getPosY()-getHeight()+getBorder());					// Bottom Left
	glEnd();												// Done Drawing The Quad

	// Buttons
	for(int row = 0; row < rows; ++row) {
		for(int col = 0; col < cols; ++col) {
			buttons[row][col].draw();
		}
	}

}

// activate buttons that mouse is clicking
bool GUIButtonMenu::activate(Vector3 mouse) {
	bool foundButton = false;
	GUIButton *activeBtn = NULL;	// pointer to active button if found

	// Buttons
	for(int row = 0; row < rows; ++row) {
		for(int col = 0; col < cols; ++col) {
			if(buttons[row][col].isActivated(false) && activeBtn == NULL) {		// Check if button was previously active
				activeBtn = &buttons[row][col];
			}
			if((buttons[row][col].activate(mouse)) && !foundButton) {			// Check cursor position and activate button 
				foundButton = true;
			} else {
				buttons[row][col].setActive(false);
			}
		}
	}
	if(!foundButton && activeBtn != NULL)										// Keep activated button on if a new one isn't found
		activeBtn->setActive(true);
	return foundButton;
}

// checks child obejcts to see if clicked... true if a button is pressed
Vector3 GUIButtonMenu::getActiveButton() {
	bool btnPressed = false;

	// Buttons
	for(int row = 0; row < rows; ++row) {
		for(int col = 0; col < cols; ++col) {
			if(buttons[row][col].isActivated())
				return Vector3(row, col, 0);
		}
	}
	return Vector3(-1, -1, -1); // NONE FOUND
}



void GUIButtonMenu::setButtonLabel(int r, int c, std::string str) {
	buttons[r][c].setLabel(str);
}


