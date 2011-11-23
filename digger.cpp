#include <cmath>
#include <iostream>
#include <stdio.h>
#include <list>
#include <GL/freeglut.h>

#include "Macros.hpp"

static const int	WINDOW_WIDTH		= 1024, 
					WINDOW_HEIGHT		= 768,
					REFRESH_PERIOD_IN_MS	= 1000 / 60;

int		oldX		= 0,
		oldY		= 0;
float	rX			= 15,
		rY			= 0;
float	fps			= 0;
int		startTime	= 0;
int		totalFrames	= 0;
int		state		= 1;
float	dist		= -5;

void setOrthoForFont()
{	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glScalef(1, -1, 1);
	glTranslatef(0, -WINDOW_HEIGHT, 0);
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
}

void resetPerspectiveProjection() 
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void renderSpacedBitmapString(
							  int x, 
							  int y,
							  int spacing, 
							  void *font,
							  char *string) 
{
	char *c;
	int x1=x;
	for (c=string; *c != '\0'; c++) {
		glRasterPos2i(x1,y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font,*c) + spacing;
		x1 = x1 + glutBitmapWidth(font,*c) + spacing;
	}
}

void drawVec(double x, double y, double z)
{
	double norm = sqrt(x * x + y * y + z * z);
	glPushMatrix();
		double phi = 180;
		if (z > -0.9999)
			phi = 2 * atan(x / (1 + z)) * 180 / M_PI;
		double theta = acos(-y) * 180 / M_PI;
		glColor3f(1,1,0);
		glRotated(180 + phi,0,1,0);
		glRotated(90 + theta,1,0,0);
		glPushMatrix();
			glutSolidCone(0.0325, norm, 4, 1);			
		glPopMatrix();					
	glPopMatrix();
}

void drawAxes()
{	 
	//To prevent the view from disturbed on repaint
	//this push matrix call stores the current matrix state
	//and restores it once we are done with the arrow rendering
	glPushMatrix();
		glColor3f(0,0,1);
		glPushMatrix();
			glTranslatef(0,0, 0.8f);
			glutSolidCone(0.0325,0.2, 4,1);
			//Draw label			
			glTranslatef(0,0.0625,0.225f);
			renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_10, (char*)"Z");
		glPopMatrix();					
		glutSolidCone(0.0225,1, 4,1);

		glColor3f(1,0,0);
		glRotatef(90,0,1,0);	
		glPushMatrix();
			glTranslatef(0,0,0.8f);
			glutSolidCone(0.0325,0.2, 4,1);
			//Draw label
			glTranslatef(0,0.0625,0.225f);
			renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_10, (char*)"X");
		glPopMatrix();					
		glutSolidCone(0.0225,1, 4,1);

		glColor3f(0,1,0);
		glRotatef(90,-1,0,0);	
		glPushMatrix();
			glTranslatef(0,0, 0.8f);
			glutSolidCone(0.0325,0.2, 4,1);
			//Draw label
			glTranslatef(0,0.0625,0.225f);
			renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_10, (char*)"Y");
		glPopMatrix();					
		glutSolidCone(0.0225,1, 4,1);	
	glPopMatrix();
}

void drawGrid(int GRID_SIZE)
{
	glBegin(GL_LINES);
	glColor3f(0.75f, 0.75f, 0.75f);
	for(int i=-GRID_SIZE;i<=GRID_SIZE;i++) {
		glVertex3f((float)i,0,(float)-GRID_SIZE);
		glVertex3f((float)i,0,(float)GRID_SIZE);

		glVertex3f((float)-GRID_SIZE,0,(float)i);
		glVertex3f((float)GRID_SIZE,0,(float)i);
	}
	glEnd();
}

void renderModels() 
{ 
	drawAxes();
	drawGrid(10);
	glutWireSphere(6, 30, 30);
	
	glEnable(GL_LIGHTING);
		glutSolidCube(10);
	glDisable(GL_LIGHTING);
} 

void initGL() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glClearColor(0.3f, 0.4f, 0.5f, 1.0);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	float ambientColor[]	= { 0.0f, 0.1f, 0.2f, 0.0f };
	float diffuseColor[]	= { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

void onReshape(int nw, int nh) {
	glViewport(0,0,nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)nw / (GLfloat)nh, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

#define MAX_PATH 127
char buffer[MAX_PATH];
void onRender() {
	//Calculate fps
	totalFrames++;
	int current = glutGet(GLUT_ELAPSED_TIME);
	if((current - startTime) > 1000) {		
		float elapsedTime = float(current-startTime);
		fps = ((float)(totalFrames * 1000) / elapsedTime) ;
		startTime = current;
		totalFrames=0;
	}

	snprintf(buffer, MAX_PATH, "FPS: %3.2f", fps);

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0,0,dist);
	glRotatef(rX,0,1,0);
	glRotatef(rY,1,0,0);

	glEnable(GL_LIGHTING);
		renderModels();
	glDisable(GL_LIGHTING);

	setOrthoForFont();
	glColor3f(1,1,1);
	//Show the fps
	renderSpacedBitmapString(20, 20, 0, GLUT_BITMAP_HELVETICA_12, buffer);

	resetPerspectiveProjection();

	glutSwapBuffers();
}

void mouseCallback(int button, int s, int x, int y)
{
	oldX = x; 
	oldY = y; 
	
	(void)s;
	if(button == GLUT_MIDDLE_BUTTON)
		state = 0;
	else
		state = 1;
}

void motionCallback(int x, int y)
{
	if (state == 0) {
		dist *= (1 + (float)(y - oldY) / 60);
	} else {
		rX += (float)(x - oldX) / 5; 
		rY += (float)(y - oldY) / 5; 
// 		float theta = 45 - rY / 180 * M_PI;
// 		float phi = -rX / 180 * M_PI;
// 		std::cout << "phi: " << phi << " | theta: " << theta << "\n";
	}
	oldX = x;
	oldY = y;
}

static void keyboardCallback(unsigned char key, int, int)
{
	switch(key)
	{
		case 8: // Backspace
		case 127: // Delete
		case 27: // Echap
			exit(0);
			break;
		default:
			TRACE("Key (" << (int)key << ") not handled.");
			break;
	}
}

static void arrowKeyCallback(int key, int x, int y)
{
	keyboardCallback((unsigned char)key, x, y);
}

void refreshTimer(int millisec)
{
	glutTimerFunc(millisec, refreshTimer, millisec);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
// 	atexit(onShutdown);

	TRACE("Use the mouse to rotate the camera or zoom with the middle button pressed.");
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutSetWindow(glutCreateWindow("DiggerHand prototype"));

	glutDisplayFunc(onRender);
	glutTimerFunc(REFRESH_PERIOD_IN_MS, refreshTimer, REFRESH_PERIOD_IN_MS);
	glutReshapeFunc(onReshape);

	glutKeyboardFunc(keyboardCallback);
	glutSpecialFunc(arrowKeyCallback);

	glutMouseFunc(mouseCallback);
	glutMotionFunc(motionCallback);

	initGL();

	glutMainLoop();
	
	return 0;
}
