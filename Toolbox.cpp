#include "Toolbox.h"

namespace Toolbox
{
	bool surMarqueur(int redValue, int greenValue, int blueValue, float* couleurMarqueur)
	{
		float intervalle = 30;
		return ( couleurMarqueur[0] - intervalle < (float) redValue && (float) redValue < couleurMarqueur[0] + intervalle
			&& couleurMarqueur[1] - intervalle < (float) greenValue && (float) greenValue < couleurMarqueur[1] + intervalle
			&& couleurMarqueur[2] - intervalle < (float) blueValue && (float) blueValue < couleurMarqueur[2] + intervalle );
	}

	void remplirProfondeur(std::vector<uint8_t> pVector, std::vector<uint8_t> depth, int tailleVector)
	{
		int indiceProf = 0;
		for (int i = 0; i < tailleVector; i++)
		{
			if (i % 4 == 3)
			{
				pVector[i] = depth[indiceProf];
				indiceProf++;
			}
		}

		if (indiceProf != tailleVector * 4)
		{
			std::cout << "Attention : on a pas parcouru l'intégralité du vecteur depth" << std::endl;
		}
	}

}
