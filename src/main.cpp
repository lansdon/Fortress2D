#include <gl/freeglut.h>



/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>
#include "src\Game.h"


// GAME CLASSES
Game game;


//GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
//GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
//GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
//  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
//  {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
//GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
//  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
//  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
//GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

int w1;
int h1;

//void
//drawBox(void)
//{
//  int i;
//
//  for (i = 0; i < 6; i++) {
//    glBegin(GL_QUADS);
//    glNormal3fv(&n[i][0]);
//    glVertex3fv(&v[faces[i][0]][0]);
//    glVertex3fv(&v[faces[i][1]][0]);
//    glVertex3fv(&v[faces[i][2]][0]);
//    glVertex3fv(&v[faces[i][3]][0]);
//    glEnd();
//  }
//}


//void orthogonalStart () {
//    glMatrixMode(GL_PROJECTION);
//    glPushMatrix();
//    glLoadIdentity();
//    gluOrtho2D(0, w1, 0, h1);
//    glScalef(1, -1, 1);
//    glTranslatef(0, -h1, 0);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void orthogonalEnd () {
//    glMatrixMode(GL_PROJECTION);
//    glPopMatrix();
//    glMatrixMode(GL_MODELVIEW);
//}

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
	game.in.addKeyDown (key, x, y);
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
  ///* Setup cube vertex data. */
  //v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
  //v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
  //v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
  //v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
  //v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
  //v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

  /* Enable a single OpenGL light. */
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  //glEnable(GL_LIGHT0);
  //glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
//  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 45.0,
    /* aspect ratio */ (GLfloat)game.getScreenWidth() / (GLfloat)game.getScreenWidth(),
    /* Z near */ 0.1, /* Z far */ 1000.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  //glTranslatef(0.0, 0.0, -1.0);
  //glRotatef(60, 1.0, 0.0, 0.0);
  //glRotatef(-20, 0.0, 0.0, 1.0);

  game.initGL();
}

int main(int argc, char **argv)
{
	// Window Setup / Init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
