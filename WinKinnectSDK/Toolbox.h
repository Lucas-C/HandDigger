#include <iostream>
#include <istream>
#include <fstream>

enum MarqueurId { ORANGE };

namespace Toolbox {

	bool surMarqueur(int redValue, int greenValue, int blueValue, MarqueurId marqId, bool yuv);

	void creerPpm(const char *sortie, unsigned char * image);

	void rgbToHsv(unsigned char * image);
	
};
