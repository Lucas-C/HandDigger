#ifndef __DIGGER_H__
#define __DIGGER_H__

namespace Digger
{
	void init();
	// Actually ignore y
	// x = xWrist - xShoulder,
	// z = zWrist - zShoulder,
	void setPosDigger(double x, double y, double z);
	void draw(bool inCorner);

	void mouseCallback(int, int, int, int);
	void motionCallback(int, int);
	void keyboardCallback(unsigned char, int, int);
	void arrowKeyCallback(int, int, int);
	void reshapeCallback(int, int);
}

#endif //__DIGGER_H__