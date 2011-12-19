#include <gl/freeglut.h>
#include <gl/glut.h>
#include "Game.h"
#include "GOSettings.h"

// GAME CLASSES
Game game;


int w1;
int h1;

void display() {
	game.draw();
}


void loop() {
	game.update();
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);
    w1 = w;
    h1 = h;
    glMatrixMode (GL_MODELVIEW);
}

void addKeyDown(unsigned char key, int x, int y) {
//	game.in.addKeyDown (key, x, y);//
	game.keyPressed(key, x, y);
}

void addKeyUp(unsigned char key, int x, int y) {
	game.in.addKeyUp(key, x, y);
}

void addSpecialDown( int key, int x, int y) {
	game.in.addSpecialDown(key, x, y);
}

void addSpecialUp( int key, int x, int y) {
	game.in.addSpecialUp(key, x, y);
}

void addMouseEvent(int button, int state, int x, int y) {
	game.in.addMouseEvent(button, state, x, y);
}

void passiveMousePos(int x, int y) {
	game.in.setMousePos(x, y);
}

void init(void)
{

  ///* Setup the view of the cube. */
  //glMatrixMode(GL_PROJECTION);
  //gluPerspective( /* field of view in degree */ 45.0,
  //  /* aspect ratio */ (GLfloat)game.getScreenWidth() / (GLfloat)game.getScreenWidth(),
  //  /* Z near */ 0.1, /* Z far */ 1000.0);
  //glMatrixMode(GL_MODELVIEW);
  //gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
  //  0.0, 0.0, 0.0,      /* center is at (0,0,0) */
  //  0.0, 1.0, 0.);      /* up is in positive Y direction */


  game.initGL();
}

int main(int argc, char **argv)
{
	// Window Setup / Init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(game.getScreenWidth(), game.getScreenHeight());
	glutCreateWindow("GLUT F2D TEST");
 
	// Game loop callback
	glutDisplayFunc(display);
	glutIdleFunc(loop);
	// Input callbacks
	glutKeyboardFunc(addKeyDown);
	glutKeyboardUpFunc(addKeyUp);
	glutSpecialFunc(addSpecialDown);
	glutSpecialUpFunc(addSpecialUp);
	glutMouseFunc(addMouseEvent);
	glutPassiveMotionFunc(passiveMousePos);

	glutReshapeFunc (reshape);
	init();
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}
