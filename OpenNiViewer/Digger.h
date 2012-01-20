#ifndef DEF_H_DIGGER_
#define DEF_H_DIGGER_

class Point;

namespace Digger
{
	void init();
	void setPosDigger(const Point& pos);
	void setGoalDigger(const Point& g);
	void draw(bool inCorner);

	void mouseCallback(int, int, int, int);
	void motionCallback(int, int);
	void keyboardCallback(unsigned char, int, int);
	void arrowKeyCallback(int, int, int);
	void reshapeCallback(int, int);
}

#endif //DEF_H_DIGGER_