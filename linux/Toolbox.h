#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <iostream>
#include <vector>
#include <cstdint>

namespace Toolbox {

	bool surMarqueur(int redValue, int greenValue, int blueValue, float* couleurMarqueur);

	// Remplace les 4ème composantes de pVector (alpha) par les profondeurs contenues dans 'depth'
	void remplirProfondeur(std::vector<uint8_t> pVector, std::vector<uint8_t> depth, int tailleVector);
	
}

#endif
