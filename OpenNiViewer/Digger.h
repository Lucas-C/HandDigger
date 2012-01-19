#ifndef __DIGGER_H__
#define __DIGGER_H__

namespace Digger
{
	void init();
	void draw();
	void finalize();

	void arrowKeyCallback(int, int, int);
	void keyboardCallback(unsigned char, int, int);
	void mouseCallback(int, int, int, int);
	void motionCallback(int, int);
	void reshapeCallback(int, int);
}

#endif //__DIGGER_H__