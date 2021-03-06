/**
	@file Digger.cpp
	@brief Mechanical digger simulation

We consider four elements :
- the cabin
joined at point O with
- the upper-arm
joined at point V with
- the lower-arm
joined at point M with
- the diggerhand

First model :
- knowing the position M of the diggerhand and its orientation,
we want to compute the position V.

Second model :
- knowing the position and orientation of the diggerhand flat bottom,
we want to compute the positions M and V.

TODO: only use double ?

	@author CIMON Lucas
	@date 23 november 2011
*/
// Indentation used : 4 spaces

#include <list>
#include <cmath>
#ifndef M_PI
	#define M_PI	3.14159265
#endif
#include <cstdio>
#if _MSC_VER
#define snprintf _snprintf_s
#endif

#include "GL/glut.h"
#define glutSolidCylinder(base, height, slices, stacks) gluCylinder(gluNewQuadric(), base, base, height, slices, stacks)

#include "Digger.h"
#include "Point.h"
#include "Macros.hpp"


namespace Digger
{

/*** Model parameters ***/

const double	upperArmLength		= 5,
				lowerArmLength		= 5,
				diggerHandRadius	= 0.5,
				diggerHandWidth		= 1.5,
				distMaxSquared		= (upperArmLength * upperArmLength) + (lowerArmLength * lowerArmLength) * 2,
				vitesseMax			= 0.1; // Vitesse maximum de déplacement du bras

// Aesthetic ones
const double	jointRadius	= 0.3f,
				cabinSize	= 3,
				armRadius	= 0.2f;

/*** Interface parameters ***/
const double arrowStep	= 0.1;

// Camera parameters
int		nw			= 0,
		nh			= 0;
int		oldX		= 0,
		oldY		= 0;
double	rX			= 15,
		rY			= -60,
		dist		= -10;
bool	zoomMode	= false;

// FPS calcul parameters
double	fps			= 0;
int		startTime	= 0;
int		totalFrames	= 0;


Point computeVfromM();
// Global point variables
Point O, goal(6, 0, 1), V(computeVfromM()), M(goal);
double	shovelAngle = 0,	 // Shovel inclinaison
		shovelAngleGoal = 0;


/*** Model-related functions ***/

// Utility function giving in order solutions of a 2nd degree polynom
void sol2ndDegree(double a, double b, double c, double& sMin, double& sMax) {
	bool aIsNull = F_EQUAL(a, 0);
	double delta = b * b - 4 * a *c;
	if (delta < 0 || (aIsNull && F_EQUAL(b, 0))) {
		TRACE_("ERROR: no solution in \'sol2ndDegree\' with"
		<< "\n a = " << a
		<< "\n b = " << b
		<< "\n c = " << c);
		exit(13);
	}
	if (aIsNull) {
		sMin = sMax = c / b;
	} else {
		sMin = (-b - sqrt(delta)) / 2 / a;
		sMax = (-b + sqrt(delta)) / 2 / a;
	}
}

Point computeVfromM() {
/*
	Knowing M(X, Y, Z), V(x, y, z) is defined by the three following equations :
(1)		x² + y² + z² = upperArmLength²
(2)		(x - X)² + (y - Y)² + (z - Z)² = lowerArmLength²
(3)		Xy = Yx
	The last one imply that the whole arm is in a vertical plane.
	The system as two solutions, we want the one with the biggest z coordinate.

	RESOLUTION: We substitue (1) in (2) and the system become (with no nul M coord)
(1)		x² + y² + z² = upperArmLength²
(2)		z = (A - xX - yY) / Z
			where A = (X² + Y² + Z² + upperArmLength² - lowerArmLength²) / 2
(3)		y = Y/X * x

	We then obtains the following 2nd degree equation in x :
		x² + Y²/X² * x² + (A - xX - Y²/X * x)² / Z² = upperArmLength²
	=>	(1 + Y²/X² + (X + Y²/X)²/Z²) * x² - 2A(X + Y²/X)/Z² * x + A²/Z² - upperArmLength² = 0

	If (x == 0)
(1)		y² + z² = upperArmLength²
(2)		y = (A - zZ) / Y
	=> (1 + Z²/Y²) * z² - 2AZ/Y² * z + A² / Y² - upperArmLength² = 0

*/
	double	X2 = M.x * M.x,
			Y2 = M.y * M.y;

	if (F_EQUAL(M.z, 0)) {
		return Point(M.x / 2, M.y / 2,
			sqrt(upperArmLength * upperArmLength - X2 / 4 - Y2 / 4));
	}

	double	Z2 = M.z * M.z,
			A = (X2 + Y2 + Z2 + upperArmLength * upperArmLength - lowerArmLength * lowerArmLength) / 2;

	if (F_EQUAL(M.x, 0)) {
		double dumb = 0, z = 0;
		sol2ndDegree(1 + Z2 / Y2, -2 * A * M.z / Y2, A * A / Y2 - upperArmLength * upperArmLength, dumb, z);
		return Point(0, (A - z * M.z) / M.y, z);
	} else if (F_EQUAL(M.y, 0)) {
		double dumb = 0, z = 0;
		sol2ndDegree(1 + Z2 / X2, -2 * A * M.z / X2, A * A / X2 - upperArmLength * upperArmLength, dumb, z);
		return Point((A - z * M.z) / M.x, 0, z);
	}

	double x1 = 0, x2 = 0;
	sol2ndDegree(	1 + Y2 / X2 + (M.x + Y2 / M.x) * (M.x + Y2 / M.x) / Z2,
					-2 * A * (M.x + Y2 / M.x) / Z2,
					A * A / Z2 - upperArmLength * upperArmLength,
					x1, x2);

	double	z1 = (A - x1 * M.x - x1 * Y2 / M.x) / M.z,
			z2 = (A - x2 * M.x - x2 * Y2 / M.x) / M.z;

	if (z1 > z2)
		return Point(x1, x1 * M.y / M.x, z1);
	else
		return Point(x2, x2 * M.y / M.x, z2);
}

void testComputation() {
	TRACE(V);
	TRACE("");
	TRACE("x² + y² + z² = upperArmLength²");
	TRACE("-> " << V.x * V.x + V.y * V.y + V.z * V.z << " = " << upperArmLength * upperArmLength);

	TRACE("(x - X)² + (y - Y)² + (z - Z)² = lowerArmLength²");
	TRACE("-> " << (V.x - M.x) * (V.x - M.x) + (V.y - M.y) * (V.y - M.y) + (V.z - M.z) * (V.z - M.z) << " = " << lowerArmLength * lowerArmLength);

	TRACE("Xy = Yx");
	TRACE("-> " << M.x * V.y << " = " << M.y * V.x);

	double	X2 = M.x * M.x,
			Y2 = M.y * M.y,
			Z2 = M.z * M.z,
			A = (X2 + Y2 + Z2 + upperArmLength * upperArmLength - lowerArmLength * lowerArmLength) / 2,
			c = A * A / Z2 - upperArmLength * upperArmLength,
			b = -2 * A * (M.x + Y2 / M.x) / Z2,
			a = 1 + Y2 / X2 + (M.x + Y2 / M.x) * (M.x + Y2 / M.x) / Z2;
	TRACE("a * x² + b * x + c");
	TRACE("-> " << a*V.x*V.x + b*V.x + c);
	TRACE("");
}


/*** OpenGL-related functions ***/

void setOrthoForFont()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, nw, 0, nh);
	glScalef(1, -1, 1);
	glTranslatef(0, -nh, 0);
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
		glColor3d(1,1,0);
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
		glColor3d(0,0,1);
		glPushMatrix();
			glTranslatef(0,0, 0.8f);
			glutSolidCone(0.0325,0.2, 4,1);
			//Draw label
			glTranslatef(0,0.0625,0.225f);
			renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_10, (char*)"Z");
		glPopMatrix();
		glutSolidCone(0.0225,1, 4,1);

		glColor3d(1,0,0);
		glRotatef(90,0,1,0);
		glPushMatrix();
			glTranslatef(0,0,0.8f);
			glutSolidCone(0.0325,0.2, 4,1);
			//Draw label
			glTranslatef(0,0.0625,0.225f);
			renderSpacedBitmapString(0,0,0,GLUT_BITMAP_HELVETICA_10, (char*)"X");
		glPopMatrix();
		glutSolidCone(0.0225,1, 4,1);

		glColor3d(0,1,0);
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

void drawXYGrid(int gridSize)
{
	glBegin(GL_LINES);
	glColor3d(0.75f, 0.75f, 0.75f);
	for(int i = -gridSize; i <= gridSize; ++i) {
		glVertex3d(i, -gridSize, 0);
		glVertex3d(i, gridSize, 0);

		glVertex3d(-gridSize, i, 0);
		glVertex3d(gridSize, i, 0);
	}
	glEnd();
}

void drawCabin(double angle) {
	glColor3d(0.75f, 0.75f, 0.75f);
	glPushMatrix();
		glRotatef(angle / M_PI * 180, 0, 0, 1);
		glTranslatef(-jointRadius - cabinSize / 2, 0, 0);
		glutSolidCube(cabinSize);
	glPopMatrix();
}

void drawJoint(const Point& p)
{
	glColor3d(1.f, 0.f, 0.f);
	glPushMatrix();
		glTranslatef(p.x, p.y, p.z);
		glutWireSphere(jointRadius, 8, 8);
	glPopMatrix();
}

void drawArm(const Point& p1, const Point& p2)
{
	glColor3d(1.f, 0.5, 0.25);
	const double	vX = p2.x - p1.x,
					vY = p2.y - p1.y,
					vZ = p2.z - p1.z,
					flatNorm = sqrt(vX * vX + vY * vY),
					norm = sqrt(vX * vX + vY * vY + vZ * vZ),
					shift = jointRadius / norm;
	glPushMatrix();
		glTranslatef(p1.x + vX * shift, p1.y + vY * shift, p1.z + vZ * shift);
		// We use spherical coordinates
		if (vY >= 0)
			glRotatef(acos(vX / flatNorm) / M_PI * 180, 0, 0, 1);
		else
			glRotatef(-acos(vX / flatNorm) / M_PI * 180, 0, 0, 1);
		glRotatef(acos(vZ / norm) / M_PI * 180, 0, 1, 0);
		glutSolidCylinder(armRadius, norm - 2 * jointRadius, 30, 8);
	glPopMatrix();
}

void drawShovel(const Point& p, double theta)
{
	const double	numMajor = 12,
					numMinor = 12,
					majorStep = diggerHandWidth / numMajor,
					minorStep = M_PI / numMinor,
					flatNorm = sqrt(p.x * p.x + p.y * p.y),
					shiftCoeff = 1 + jointRadius / flatNorm;
	glColor3d(0.f, 0.7f, 0.f);
	TRACE_(theta);
	glPushMatrix();
		glTranslatef(p.x * shiftCoeff, p.y * shiftCoeff, p.z);
		// We use spherical coordinates
		if (p.y >= 0)
			glRotatef(acos(p.x / flatNorm) / M_PI * 180, 0, 0, 1);
		else
			glRotatef(-acos(p.x / flatNorm) / M_PI * 180, 0, 0, 1);
		glRotatef(90 - theta / M_PI * 180, 0, 1, 0);
		for (int i = 0; i < numMajor; ++i) {
			GLdouble y0 = 0.5 * diggerHandWidth - i * majorStep;
			GLdouble y1 = y0 - majorStep;
			glBegin(GL_TRIANGLE_STRIP);
			for (int j = 0; j <= numMinor; ++j) {
				double a = j * minorStep + M_PI / 2;
				GLdouble x = diggerHandRadius * cos(a);
				GLdouble z = diggerHandRadius * (1 + sin(a));
				glNormal3d(x / diggerHandRadius, 0.0, z / diggerHandRadius);
				glTexCoord2d(j / (GLdouble) numMinor, i / (GLdouble) numMajor);
				glVertex3d(x, y0, z);

				glNormal3f(x / diggerHandRadius, 0.0, z / diggerHandRadius);
				glTexCoord2d(j / (GLdouble) numMinor, (i + 1) / (GLdouble) numMajor);
				glVertex3d(x, y1, z);
			}
			glEnd();
		}
	glPopMatrix();
}

void updatePosDigger();
void renderModels()
{
	drawAxes();
	drawXYGrid(10);

	updatePosDigger();

	double	norm = M.norm(),
			xNormed = M.x / norm,
			yNormed = M.y / norm;

	glEnable(GL_LIGHTING);
		drawCabin(2 * atan(yNormed / (1 + xNormed)));
		drawJoint(O);
		drawArm(O, V);
		drawJoint(V);
		drawArm(V, M);
		drawJoint(M);
		drawShovel(M, shovelAngle);
	glDisable(GL_LIGHTING);
}

void init() {
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_LIGHTING);
	float diffuseColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
	glEnable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}

#define HUD_BUFFER_SIZE 127
char buffer[HUD_BUFFER_SIZE];
void draw(bool inCorner)
{
	if (inCorner)
		glViewport(0, 0, nw / 2, nh / 2);
	else
		glViewport(0, 0, nw, nh);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLdouble)nw / (GLdouble)nh, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(0,0,dist);
	glRotatef(rX,0,1,0);
	glRotatef(rY,1,0,0);

	//Calculate fps
	totalFrames++;
	int current = glutGet(GLUT_ELAPSED_TIME);
	if((current - startTime) > 1000) {
		double elapsedTime = current - startTime;
		fps = totalFrames * 1000.0 / elapsedTime;
		startTime = current;
		totalFrames=0;
	}
	snprintf(buffer, HUD_BUFFER_SIZE, "FPS: %3.2f", fps);

	glEnable(GL_DEPTH_TEST);
	renderModels();
	glDisable(GL_DEPTH_TEST);

	//Show the fps
	setOrthoForFont();
	glColor3d(1,1,1);
	renderSpacedBitmapString(20, 20, 0, GLUT_BITMAP_HELVETICA_12, buffer);
	resetPerspectiveProjection();

	if (inCorner)
		glViewport(0, 0, nw, nh);
}

void reshapeCallback(int nw_, int nh_) {
	nw = nw_;
	nh = nh_;
}

void mouseCallback(int button, int s, int x, int y)
{
	oldX = x;
	oldY = y;

	(void)s;
	if(button == GLUT_MIDDLE_BUTTON)
		zoomMode = true;
	else
		zoomMode = false;
}

void motionCallback(int x, int y)
{
	if (zoomMode) {
		dist *= 1 + (y - oldY) / 60.0;
	} else {
		rX += (x - oldX) / 5.0;
		rY += (y - oldY) / 5.0;
// 		double theta = 45 - rY / 180 * M_PI;
// 		double phi = -rX / 180 * M_PI;
// 		std::cout << "phi: " << phi << " | theta: " << theta << "\n";
	}
	oldX = x;
	oldY = y;
}

void keyboardCallback(unsigned char key, int, int)
{
	switch(key)
	{
		case 8: // Backspace
		case 127: // Delete
		case 27: // Echap
			exit(0);
			break;
		case 100: // Left arrow
			setPosDigger(M + Point(0, arrowStep, 0));
			goal = M;
			break;
		case 101: // Up arrow
			setPosDigger(M + Point(arrowStep, 0, 0));
			goal = M;
			break;
		case 102: // Right arrow
			setPosDigger(M + Point(0, -arrowStep, 0));
			goal = M;
			break;
		case 103: // Down arrow
			setPosDigger(M + Point(-arrowStep, 0, 0));
			goal = M;
			break;
		case 104: // PageUp
			setPosDigger(M + Point(0, 0, arrowStep));
			goal = M;
			break;
		case 105: // PageDown
			setPosDigger(M + Point(0, 0, -arrowStep));
			goal = M;
			break;
		default:
			TRACE("Key (" << (int)key << ") not handled.");
			break;
	}
}

void arrowKeyCallback(int key, int x, int y)
{
	keyboardCallback((unsigned char)key, x, y);
}

void setPosDigger(const Point& pos)
{
	//TRACE_("Pcandidate = " << pos);
	if (pos.x > 0
	&&	pos.squareNorm() < distMaxSquared) {
		Point	oldM = M,
				oldV = V;
		M = pos;
		V = computeVfromM();
 		//TRACE("M = " << M);
 		//TRACE("V = " << V);
 		//testComputation();
		if (V.x < 0) {
			M = oldM;
			V = oldV;
		} else {
			//TRACE_("\t pos = " << M);
		}
	}
}

void setGoalDigger(const Point& g)
{
	//TRACE_("gCandidate = " << g);
	if (g.x > 0
	&&	g.squareNorm() < distMaxSquared) {
		goal = g;
		//TRACE_("\t goal = " << goal);
	}
}

void setGlobalShovelAngle(double theta)
{
	shovelAngle = theta;
}

void setGoalGlobalShovelAngle(double theta)
{
	shovelAngleGoal = theta;
}

void updatePosDigger()
{
	shovelAngle += vitesseMax * (shovelAngleGoal - shovelAngle);

	Point direction(goal - M);
	double normDirection = sqrt(direction.squareNorm());
	if (normDirection > vitesseMax) {
		double rapport = vitesseMax / normDirection;
		direction = direction * rapport;
	}
	setPosDigger(M + direction);
}

}
