#ifndef DEF_H_TOOLBOX_
#define DEF_H_TOOLBOX_

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>

#include "Point.h"

enum MarqueurId { ORANGE, BLEU, VIDE };

namespace Toolbox {

	bool surMarqueur(int redValue, int greenValue, int blueValue, MarqueurId &marqId);

	void creerPpm(const char *sortie, unsigned char * image, int width, int height);

	void rgbToHsv(unsigned char * image, int width, int height);

	std::vector<Point> detecterCentres(unsigned char * pImage, int width, int height);

	// Convention : centre[0] (vert) défini la l'extrémité du bras et centres[1] (bleu) sa base
	void placerMarqueurs(unsigned char * image, std::vector<Point> centres, int width, int height);

	void remplirProfondeur(unsigned short * depth, std::vector<Point> &centres, int width, int height);

	// Va placer régler centre[0] et centre[1] (convention : le centre le plus à gauche sur l'image est la base du bras) et centre[2] et centre[3] (convention : centre[2] est le point arrière du godet)
	void followLeftConvention(std::vector<Point>& centres);

	// Calcul l'angle entre l'axe horizontal et le vecteur p1p2 formé par deux points (positif si le vecteur pointe vers le bas sur l'image)
	float calculAngle(Point p1, Point p2);
};

#endif //DEF_H_TOOLBOX_