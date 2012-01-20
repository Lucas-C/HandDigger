
#include <vector>
#include "Toolbox.h"

class Image
{
	public:
		Image(int pNbPoints);
	
		~Image();

		void premiere_detection(unsigned char * pVector, std::vector<MarqueurId> marqueurs);

		void placerMarqueurs(unsigned char * image);

		void remplirProfondeur(unsigned char * depth);


	public:
		int **mPositionsCenter;
		int nbPoints;
};

