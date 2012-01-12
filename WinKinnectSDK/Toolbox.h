#include <iostream>
#include <istream>
#include <fstream>

namespace Toolbox {

	bool surMarqueur(int redValue, int greenValue, int blueValue, float* couleurMarqueur, bool yuv);

	void creerPpm(const char *sortie, unsigned char * image);

	void rgbToHsv(unsigned char * image);
	
};
