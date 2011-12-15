#include "Toolbox.h"

namespace Toolbox
{
	bool surMarqueur(int redValue, int greenValue, int blueValue, float* couleurMarqueur)
	{
		float intervalle = 30;

		// Essai avec RVB
		/*return ( couleurMarqueur[0] - intervalle < (float) redValue && (float) redValue < couleurMarqueur[0] + intervalle
			&& couleurMarqueur[1] - intervalle < (float) greenValue && (float) greenValue < couleurMarqueur[1] + intervalle
			&& couleurMarqueur[2] - intervalle < (float) blueValue && (float) blueValue < couleurMarqueur[2] + intervalle );*/

		// Essaie avec Teinte

		// Calcul de la teinte désirée
		float teinteDes;
		float MDes = (float) std::max(couleurMarqueur[0], std::max(couleurMarqueur[1], couleurMarqueur[2]));
		float mDes = (float) std::min(couleurMarqueur[0], std::min(couleurMarqueur[1], couleurMarqueur[2]));
		float denomDes = MDes - mDes;
		if (denomDes < 0.000000000001) {
			std::cout << "Pas de teinte désirée" << std::endl;
			return false;
		}

		if ((couleurMarqueur[0] - MDes) < 0.000000000001) {
			teinteDes = 60 + (couleurMarqueur[1] - couleurMarqueur[2])/denomDes;
		} else if ((couleurMarqueur[1] - MDes) < 0.000000000001) {
			teinteDes = 120 + (couleurMarqueur[2] - couleurMarqueur[0])/denomDes;
		} else {
			teinteDes = 240 + (couleurMarqueur[0] - couleurMarqueur[1])/denomDes;
		}

		// Calcul de la teinte du pixel analysé
		float teinte;
		float M = (float) std::max(redValue, std::max(greenValue, blueValue));
		float m = (float) std::min(redValue, std::min(greenValue, blueValue));
		float denom = M - m;
		if (denom < 0.000000000001) {
			std::cout << "Pas de teinte dans le pixel" << std::endl;
			return false;
		}

		if (((float) redValue - M) < 0.000000000001) {
			teinte = 60 + ((float) greenValue - (float) blueValue)/denom;
		} else if (((float) greenValue - M) < 0.000000000001) {
			teinte = 120 + ((float) blueValue - (float) redValue)/denom;
		} else {
			teinte = 240 + ((float) redValue - (float) greenValue)/denom;
		}

		return fabs(teinte - teinteDes) <= (float) intervalle;

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
