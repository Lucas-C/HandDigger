#ifndef DEF_H_DIGGER_
#define DEF_H_DIGGER_

class Point;

namespace Digger
{
	void init();
	void draw(bool inCorner);

	void setPosDigger(const Point& pos);
	void setGoalDigger(const Point& g);
	void setGlobalShovelAngle(double theta); // "world" angle
	void setGoalGlobalShovelAngle(double theta); // "world" angle

	void mouseCallback(int, int, int, int);
	void motionCallback(int, int);
	void keyboardCallback(unsigned char, int, int);
	void arrowKeyCallback(int, int, int);
	void reshapeCallback(int, int);
}

#endif //DEF_H_DIGGER_