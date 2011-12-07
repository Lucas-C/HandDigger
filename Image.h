#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <cstdint>

#include "Macros.hpp"
#include "Toolbox.h"

class Image
{
	public:
		Image(int pNbPoints);

		~Image();

		void premiere_detection(std::vector<uint8_t> pVector, float *pColor);

		void detections_en_cours(std::vector<uint8_t> pVector, float *pColor);

	private:
		DISALLOW_COPY_AND_ASSIGN(Image);
 
		void detection_left_corner(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter);

		void detection_left_border(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter);

		void detection_high_border(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter);

		void detection_normal(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter);
	
	public:
		int mNbPoints;
		const int mNbPointsMax;
		int **mPositionsCenter;
};


#endif
