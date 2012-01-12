#include "stdafx.h"
#include "Toolbox.h"

using namespace std;

namespace Toolbox
{
	bool surMarqueur(int redValue, int greenValue, int blueValue, float* couleurMarqueur, bool yuv)
	{
		if (!yuv) {

			// DETECTION RGB
			/*float intervalle = 20;
			return ( couleurMarqueur[0] - intervalle < (float) redValue && (float) redValue < couleurMarqueur[0] + intervalle
				&& couleurMarqueur[1] - intervalle < (float) greenValue && (float) greenValue < couleurMarqueur[1] + intervalle
				&& couleurMarqueur[2] - intervalle < (float) blueValue && (float) blueValue < couleurMarqueur[2] + intervalle );*/


			// DETECTION TEINTE
			/*float intervalle = 20.0;

			// Calcul teinte désirée
			int M_des = max(couleurMarqueur[0], max(couleurMarqueur[1], couleurMarqueur[2]));
			int m_des = min(couleurMarqueur[0], min(couleurMarqueur[1], couleurMarqueur[2]));
			int C_des = M_des - m_des;
			if (C_des == 0) {
				// teinte non définie
				return false;
			}
			double teinte_des;
			if (M_des == couleurMarqueur[0]) {
				teinte_des = (((double) (couleurMarqueur[1] - couleurMarqueur[2])) / ((double) C_des));
				if (teinte_des < 0) {
					teinte_des += 6.0;
				}
			} else if (M_des == couleurMarqueur[1]) {
				teinte_des = (((double) (couleurMarqueur[2] - couleurMarqueur[0])) / ((double) C_des)) + 2.0;
			} else {
				teinte_des = (((double) (couleurMarqueur[0] - couleurMarqueur[1])) / ((double) C_des)) + 4.0;
			}

			teinte_des *= 60.0;

			// Calcul teinte pixel
			int M = max(redValue, max(greenValue, blueValue));
			int m = min(redValue, min(greenValue, blueValue));
			int C = M - m;
			if (C < 100) {
				// teinte non définie
				return false;
			}
			double teinte;
			if (M == redValue) {
				teinte = ((greenValue - blueValue) / C) % 6;
			} else if (M == greenValue) {
				teinte = (((double) (blueValue - redValue)) / ((double) C)) + 2.0;
			} else {
				teinte = (((double) (redValue - greenValue)) / ((double) C)) + 4.0;
			}

			teinte *= 60;

			if (teinte < 0 || teinte > 360) {
				return false;
			}

			return (teinte_des - intervalle < teinte && teinte < teinte_des + intervalle); */


			// DETECTION HSV (en supposant que couleurMarqueur est en HSV
			// Calcul teinte pixel
			int M = max(redValue, max(greenValue, blueValue));
			int m = min(redValue, min(greenValue, blueValue));
			int C = M - m;
			if (C == 0) {
				return false;
			}
			double teinte;
			if (M == redValue) {
				teinte = ((greenValue - blueValue) / C) % 6;
			} else if (M == greenValue) {
				teinte = (((double) (blueValue - redValue)) / ((double) C)) + 2.0;
			} else {
				teinte = (((double) (redValue - greenValue)) / ((double) C)) + 4.0;
			}

			teinte *= 60;
			if (teinte < 0) {
				teinte = 0;
			}
			if (teinte > 360) {
				teinte = 360;
			}

			// Calcul saturation pixel
			double saturation;
			if (M == 0) {
				saturation = 0.0;
			} else {
				saturation = 1.0 - (((double) m)/ ((double) M));
			}

			// Calcul valeur pixel
			double valeur = (double) M;




		} else {

			// DETECTION YUV
			double intervalle_u = 0.1;
			double intervalle_v = 0.2;
			//float y_des = 0.299*couleurMarqueur[0] + 0.587*couleurMarqueur[1] + 0.114*couleurMarqueur[2];
			double u_des = -0.14713*((double) couleurMarqueur[0]) - 0.28886*((double) couleurMarqueur[1]) + 0.439*((double) couleurMarqueur[2]);
			double v_des = 0.615*((double) couleurMarqueur[0]) - 0.51498*((double) couleurMarqueur[1]) - 0.10001*((double) couleurMarqueur[2]);
			double u_value = -0.14713*redValue - 0.28886*greenValue + 0.439*blueValue;
			double v_value = 0.615*redValue - 0.51498*greenValue - 0.10001*blueValue;

			return ( u_des - intervalle_u < u_value && u_value < u_des + intervalle_u && v_des - intervalle_v < v_value && v_value < v_des + intervalle_v );
		}
	}

	void creerPpm(const char *sortie, unsigned char * image)
	{
		const int larg = 640;
		const int haut = 480;

		ofstream outFile(sortie, ios::out);
		if (!outFile.is_open()) {
			cout << "Erreur : impossible d'ouvrir " << sortie << endl;
			system("pause");
			exit(0);
		}
		outFile << "P3" << endl;
		outFile << larg << " " << haut << endl;
		outFile << 255 << endl;
		// On rentre les donnees
		int indice = 0;
		for (int i = 0; i < haut; i++) {
			for (int j = 0; j < larg; j++) {
				int colors[4];
				colors[0] = (int) image[indice];
				indice++;
				colors[1] = (int) image[indice];
				indice++;
				colors[2] = (int) image[indice];
				indice++;
				colors[3] = (int) image[indice];
				indice++;
				outFile << colors[2] << " " << colors[1] << " " << colors[0] << " ";
			}
			outFile << endl;
		}
		outFile.close();
	}

	void rgbToHsv(unsigned char * image)
	{
		const int larg = 640;
		const int haut = 480;

		// On rentre les donnees
		int indice = 0;
		for (int i = 0; i < haut; i++) {
			for (int j = 0; j < larg; j++) {

				// Récupération des couleurs RGB (dans cet ordre)
				int colors[3];
				int indiceR, indiceV, indiceB;
				colors[2] = (int) image[indice];
				indiceB = indice;
				indice++;
				colors[1] = (int) image[indice];
				indiceV = indice;
				indice++;
				colors[0] = (int) image[indice];
				indiceR = indice;
				indice++;
				indice++;

				// Calcul teinte pixel
				int M = max(colors[0], max(colors[1], colors[2]));
				int m = min(colors[0], min(colors[1], colors[2]));
				int C = M - m;
				double teinte;
				if (C == 0) {
					teinte = 0.0;
				} else {
					if (M == colors[0]) {
						teinte = ((colors[1] - colors[2]) / C) % 6;
					} else if (M == colors[1]) {
						teinte = (((double) (colors[2] - colors[0])) / ((double) C)) + 2.0;
					} else {
						teinte = (((double) (colors[0] - colors[1])) / ((double) C)) + 4.0;
					}
				}

				teinte *= 60;
				if (teinte < 0) {
					teinte = 0;
				}
				if (teinte > 360) {
					teinte = 360;
				}

				// Calcul saturation pixel
				double saturation;
				if (M == 0) {
					saturation = 0.0;
				} else {
					saturation = 1.0 - (((double) m)/ ((double) M));
				}

				// Calcul valeur pixel
				double valeur = (double) M;
				
			}
		}
	}


}
