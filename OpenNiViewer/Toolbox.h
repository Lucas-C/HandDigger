#ifndef DEF_H_TOOLBOX_
#define DEF_H_TOOLBOX_

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>

enum MarqueurId { ORANGE, BLEU, VIDE };

namespace Toolbox {

	bool surMarqueur(int redValue, int greenValue, int blueValue, MarqueurId &marqId);

	void creerPpm(const char *sortie, unsigned char * image, int width, int height);

	void rgbToHsv(unsigned char * image, int width, int height);

	std::vector<int*> detecterCentres(unsigned char * pImage, int width, int height);

	// Convention : centre[0] (vert) défini la l'extrémité du bras et centres[1] (bleu) sa base
	void placerMarqueurs(unsigned char * image, std::vector<int*> centres, int width, int height);

	void remplirProfondeur(unsigned short * depth, std::vector<int*> centres, int width, int height);

	// Va placer régler centre[0] et centre[1] (convention : le centre le plus à gauche est l'extrémité du bras)
	void reglerBras(std::vector<int*> centres, int width, int height);
};

#endif //DEF_H_TOOLBOX_