
#include <vector>
#include "Toolbox.h"

class Image
{
	public:
		Image(int pNbPoints);
	
		~Image();

		void premiere_detection(unsigned char * pVector, float *pColor);

		void placerMarqueurs(unsigned char * image);


	public:
		int **mPositionsCenter;
		int nbPoints;
};

