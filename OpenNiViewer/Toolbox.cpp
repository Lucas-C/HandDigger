#include "Toolbox.h"

using namespace std;

namespace Toolbox
{
	bool surMarqueur(int redValue, int greenValue, int blueValue, MarqueurId &marqId)
	{
		// Pour l'instant, requiert que les valeurs rgb entrées soient celles de la représentation RGB
		//if (redValue == 0 && greenValue > 80 && blueValue > 150 && marqId == VIDE) {      // Eclairé
		if (redValue < 20 && greenValue > 130 && blueValue > 50 && marqId == VIDE) {       // Salle d'immersion
			marqId = ORANGE;
			return true;
		//} else if (redValue > 150 && greenValue > 100 && blueValue > 50 && marqId == VIDE) {   // Eclairé
		} else if (redValue < 10 && greenValue > 80 && greenValue < 120 && blueValue > 50 && blueValue < 100 && marqId == VIDE) {   // Salle d'immersion
			marqId = BLEU;
			return true;
		} else if (marqId == ORANGE) {
			//return (redValue == 0 && greenValue > 80 && blueValue > 150);   // Eclairé
			return (redValue < 20 && greenValue > 130 && blueValue > 50);    // Salle d'immersion
		} else if (marqId == BLEU) {
			//return (redValue > 150 && greenValue > 100 && blueValue > 50);       // Eclairé
			return (redValue < 10 && greenValue > 80 && greenValue < 120 && blueValue > 50 && blueValue < 100);    // Salle d'immersion
		} else {
			return false;
		}
		return false;
			
	}

	void creerPpm(const char *sortie, unsigned char * image, int width, int height)
	{
		const int larg = width;
		const int haut = height;

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
				int colors[3];
				colors[0] = (int) image[indice];
				indice++;
				colors[1] = (int) image[indice];
				indice++;
				colors[2] = (int) image[indice];
				indice++;
				//colors[3] = (int) image[indice];
				//indice++;
				outFile << colors[0] << " " << colors[1] << " " << colors[2] << " ";
			}
			outFile << endl;
		}
		outFile.close();
	}

	void rgbToHsv(unsigned char * image, int width, int height)
	{
		const int larg = width;
		const int haut = height;

		// On rentre les donnees
		int indice = 0;
		for (int i = 0; i < haut; i++) {
			for (int j = 0; j < larg; j++) {

				// Récupération des couleurs RGB (dans cet ordre)
				int colors[3];
				int indiceR, indiceV, indiceB;
				colors[0] = (int) image[indice];
				indiceR = indice;
				indice++;
				colors[1] = (int) image[indice];
				indiceV = indice;
				indice++;
				colors[2] = (int) image[indice];
				indiceB = indice;
				indice++;
				//indice++;

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
				int valeur = M;


				// Conversion des valeurs HSV dans l'intervalle [0, 255]
				teinte *= 255.0/360.0;
				saturation *= 255.0;

				int teinteInt = (int) teinte;
				int saturationInt = (int) saturation;

				if (teinteInt < 0) {
					teinteInt = 0;
				} else if (teinteInt > 255) {
					teinteInt = 255;
				}

				if (saturationInt < 0) {
					saturationInt = 0;
				} else if (saturationInt > 255) {
					saturationInt = 255;
				}
				
				// Écriture des valeurs dans les composantes RGB
				image[indiceR] = (unsigned char) teinteInt;
				image[indiceV] = (unsigned char) saturationInt;
				image[indiceB] = (unsigned char) valeur;
			
			}
		}
	}

	std::vector<int*> detecterCentres(unsigned char * pImage, int width, int height)
	{
		int lWidth =  width;
		int lHeight = height;
		int lNbComp = 3;
		int nbCentresOrangesTrouves = 0;
		int nbCentresBleusTrouves = 0;
		int nbCentresOrangesCherches = 2;
		int nbCentresBleusCherches = 1;

		// On va travailler sur une copie de pImage (car il y aura des conversion HSV)
		unsigned char * pVector = new unsigned char[width*height*lNbComp];
		for (int i = 0; i < width*height*lNbComp; i++) {
			pVector[i] = pImage[i];
		}
		rgbToHsv(pVector, lWidth, lHeight);


		std::vector<int*> listeCentres;
		for (int nbC = 0; nbC < (nbCentresOrangesCherches + nbCentresBleusCherches); nbC++) {
				int* coord = new int[3];
				coord[0] = lWidth - 1;
				coord[1] = lHeight - 1;
				coord[2] = 0;
				listeCentres.push_back(coord);
		}


		// Parcours des pixels de l'image
		for (int i = 0; i < lHeight; i++)
		{
			for (int j = 0; j < lWidth; j++)
			{
				// Lecture des composantes RVB du pixel
				int redComp = pVector[lNbComp * (i*lWidth + j)];
				int greenComp = pVector[lNbComp * (i*lWidth + j) + 1];
				int blueComp = pVector[lNbComp * (i*lWidth + j) + 2];

				// Le pixel correspond-il à un marqueur ?
				MarqueurId mID = VIDE;
				if (surMarqueur(redComp, greenComp, blueComp, mID))
				{

					// Calcul du diamètre du marqueur
					int hauteur = 1;
					int indiceParcours = i + 1;
					redComp = pVector[lNbComp * (indiceParcours*lWidth + j)];
					greenComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 1];
					blueComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 2];
					while (surMarqueur(redComp, greenComp, blueComp, mID))
					{
						hauteur++;
						indiceParcours++;
						redComp = pVector[lNbComp * (indiceParcours*lWidth + j)];
						greenComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 1];
						blueComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 2];
					}


					// Lecture des composantes RVB d'un pixel à gauche (un peu éloigné du centre) (afin de filtrer les cas de lignes verticales de couleur du marqueur)
					int redCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4)];
					int greenCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4) + 1];
					int blueCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4) + 2];

					// Lecture des composantes RVB d'un pixel à droite (un peu éloigné du centre) (afin de filtrer les cas de lignes verticales de couleur du marqueur)
					int redCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4)];
					int greenCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4) + 1];
					int blueCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4) + 2];

					// Si la hauteur est inférieure à une hauteur minimale, ou si l'un des pixels "voisins" gauche ou droite n'est pas un marqueur, on considère qu'il ne s'agit pas du marqueur
					if (hauteur >= 20 && surMarqueur(redCompG, greenCompG, blueCompG, mID) && surMarqueur(redCompD, greenCompD, blueCompD, mID)) {

						// Détermination du centre du marqueur
						int xCentre = j;
						int yCentre = i + (hauteur/2);

						// On recherche un centre déjà trouvé et se trouvant près du nouveau centre
						int rayonSecteur = 2*hauteur;
						bool dejaTrouve = false;
						for (int k = 0; k < listeCentres.size(); k++) {
							if ( xCentre - rayonSecteur < listeCentres[k][0] && xCentre + rayonSecteur > listeCentres[k][0]
							&& yCentre - rayonSecteur < listeCentres[k][1] && yCentre + rayonSecteur > listeCentres[k][1] )
							{
								dejaTrouve = true;
								break;
							}
						}

						// Si le centre est bien un nouveau, on l'ajoute à la liste
						if (!dejaTrouve)
						{
							int* coord;
							coord = new int[3];
							coord[0] = xCentre;
							coord[1] = yCentre;
							coord[2] = 0;
							if (mID == ORANGE && nbCentresOrangesTrouves < nbCentresOrangesCherches) {
								listeCentres[nbCentresOrangesTrouves] = coord;
								nbCentresOrangesTrouves++;
							}
							if (mID == BLEU && nbCentresBleusTrouves < nbCentresBleusCherches) {
								listeCentres[nbCentresBleusTrouves + nbCentresOrangesCherches] = coord;
								nbCentresBleusTrouves++;
							}
							if ((nbCentresOrangesTrouves + nbCentresBleusTrouves) == (nbCentresOrangesCherches + nbCentresBleusCherches))
							{
								delete pVector;
								return listeCentres;
							}
						}
					}
				}
			}
		}

		delete pVector;
		return listeCentres;

		/*if (nbCentresTrouves != listeCentres.size()) {
			cout << "Erreur de programmation (2) : le vecteur centres est de taille " << listeCentres.size() << " et nbCentresTrouves vaut " << nbCentresTrouves << endl;
			system("pause");
			exit(0);
		}*/

		/*if (nbCentresTrouves != nbCentresCherches)
		{
			// Si tous les marqueurs n'ont pas été trouvés, on rajoute des éléments pour que le vecteur soit bien de taille nbCentresCherches (les coords st alors en bas à droite)
			delete pVector;
			for (int ajout = 0; ajout < nbCentresCherches - nbCentresTrouves; ajout++) {
				int* coord;
				coord = new int[3];
				coord[0] = lWidth - 1;
				coord[1] = lHeight - 1;
				coord[2] = 0;
				listeCentres.push_back(coord);
				}
			return listeCentres;
		}*/

	}


	void placerMarqueurs(unsigned char * image, std::vector<int*> centres, int width, int height)
	{
		int lWidth =  width;
		int lHeight = height;
		int lNbComp = 3;
		int largMarque = 3;   // 3

		for (unsigned int centre = 0; centre < centres.size(); centre++) 
		{
			int x = centres[centre][0];
			int y = centres[centre][1];

			for (int dx = -largMarque; dx < largMarque+1; dx++) {
				for (int dy = -largMarque; dy < largMarque+1; dy++) {
					if (x+dx >= 0 && x+dx < lWidth && y+dy >= 0 && y+dy < lHeight) {
						if (centre == 0) {    // Extrémité du bras (vert)
							image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 255;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 0;
						} else if (centre == 1) {    // Base du bras (bleu)
							image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 255;
						} else if (centre == 2) {    // Point angulaire 1 (rouge)
							image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 255;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 0;
						}
					}
				}
			}
		}

	}


	void remplirProfondeur(unsigned short * depth, std::vector<int*> centres, int width, int height)
	{
		int lWidth =  width;
		int lHeight = height;
		for (unsigned int centre = 0; centre < centres.size(); centre++) 
		{
			int x = centres[centre][0];
			int y = centres[centre][1];
			centres[centre][2] = depth[y*lWidth + x];
			/*if (centre == 0) {
				cout << "profondeur de centre[" << centre << "] = " << centres[centre][2] << endl; 
			}*/
		}
	}

	void reglerBras(std::vector<int*> centres, int width, int height)
	{
		if (centres.size() > 1) {
			if (centres[0][0] > centres[1][0]) {
				int xAux = centres[0][0];
				int yAux = centres[0][1];
				centres[0][0] = centres[1][0];
				centres[0][1] = centres[1][1];
				centres[1][0] = xAux;
				centres[1][1] = yAux;
			}
		}
	}


}
