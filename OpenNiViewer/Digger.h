#ifndef DEF_H_DIGGER_
#define DEF_H_DIGGER_

namespace Digger
{
	void init();
	void setPosDigger(double x, double y, double z);
	void setPosDiggerScaled(double x, double y, double z);
	void setGoalDigger(double x, double y, double z);
	void setGoalDiggerScaled(double x, double y, double z);
	void draw(bool inCorner);

	void mouseCallback(int, int, int, int);
	void motionCallback(int, int);
	void keyboardCallback(unsigned char, int, int);
	void arrowKeyCallback(int, int, int);
	void reshapeCallback(int, int);
}

#endif //DEF_H_DIGGER_