#include "Toolbox.h"

using namespace std;

namespace Toolbox
{
	bool surMarqueur(int redValue, int greenValue, int blueValue, MarqueurId &marqId)
	{
		// Pour l'instant, requiert que les valeurs rgb entr�es soient celles de la repr�sentation RGB
		if (redValue < 10 && greenValue > 80 && blueValue > 140 && marqId == VIDE) {      // Eclair�
		//if (redValue < 20 && greenValue > 130 && blueValue > 50 && marqId == VIDE) {       // Salle d'immersion
		//if (redValue < 5 && greenValue > 180 && blueValue > 80 && marqId == VIDE) {     // Night
			marqId = ORANGE;
			return true;
		} else if (redValue > 150 && greenValue > 80 && blueValue > 80 && marqId == VIDE) {   // Eclair�
		//} else if (redValue < 10 && greenValue > 80 && greenValue < 120 && blueValue > 50 && blueValue < 100 && marqId == VIDE) {   // Salle d'immersion
		//} else if (redValue > 120 && greenValue < 100 && blueValue < 170 && marqId == VIDE) {   // Night
			marqId = BLEU;
			return true;
		} else if (marqId == ORANGE) {
			return (redValue < 10 && greenValue > 80 && blueValue > 140);   // Eclair�
			//return (redValue < 20 && greenValue > 130 && blueValue > 50);    // Salle d'immersion
			//return (redValue < 5 && greenValue > 180 && blueValue > 80);     // Night
		} else if (marqId == BLEU) {
			return (redValue > 150 && greenValue > 80 && blueValue > 80);       // Eclair�
			//return (redValue < 10 && greenValue > 80 && greenValue < 120 && blueValue > 50 && blueValue < 100);    // Salle d'immersion
			//return (redValue > 120 && greenValue < 100 && blueValue < 170);    // Night
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

				// R�cup�ration des couleurs RGB (dans cet ordre)
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
				
				// �criture des valeurs dans les composantes RGB
				image[indiceR] = (unsigned char) teinteInt;
				image[indiceV] = (unsigned char) saturationInt;
				image[indiceB] = (unsigned char) valeur;
			
			}
		}
	}

	std::vector<Point> detecterCentres(unsigned char * pImage, int width, int height)
	{
		int lWidth =  width;
		int lHeight = height;
		int lNbComp = 3;
		int nbCentresOrangesTrouves = 0;
		int nbCentresBleusTrouves = 0;
		int nbCentresOrangesCherches = 2;
		int nbCentresBleusCherches = 2;

		// On va travailler sur une copie de pImage (car il y aura des conversion HSV)
		unsigned char * pVector = new unsigned char[width*height*lNbComp];
		for (int i = 0; i < width*height*lNbComp; i++) {
			pVector[i] = pImage[i];
		}
		rgbToHsv(pVector, lWidth, lHeight);


		std::vector<Point> listeCentres;
		for (int nbC = 0; nbC < (nbCentresOrangesCherches + nbCentresBleusCherches); nbC++) {
			listeCentres.push_back(Point(lWidth - 1, lHeight - 1, 0));
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

				// Le pixel correspond-il � un marqueur ?
				MarqueurId mID = VIDE;
				if (surMarqueur(redComp, greenComp, blueComp, mID))
				{

					// Calcul du diam�tre du marqueur
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


					// Lecture des composantes RVB d'un pixel � gauche (un peu �loign� du centre) (afin de filtrer les cas de lignes verticales de couleur du marqueur)
					int redCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4)];
					int greenCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4) + 1];
					int blueCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4) + 2];

					// Lecture des composantes RVB d'un pixel � droite (un peu �loign� du centre) (afin de filtrer les cas de lignes verticales de couleur du marqueur)
					int redCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4)];
					int greenCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4) + 1];
					int blueCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4) + 2];

					// Si la hauteur est inf�rieure � une hauteur minimale, ou si l'un des pixels "voisins" gauche ou droite n'est pas un marqueur, on consid�re qu'il ne s'agit pas du marqueur
					if (hauteur >= 10 && surMarqueur(redCompG, greenCompG, blueCompG, mID) && surMarqueur(redCompD, greenCompD, blueCompD, mID)) {

						// D�termination du centre du marqueur
						int xCentre = j;
						int yCentre = i + (hauteur/2);

						// On recherche un centre de m�me couleur d�j� trouv� et se trouvant pr�s du nouveau centre
						int rayonSecteur = 4*hauteur;
						bool dejaTrouve = false;
						if (mID == ORANGE) {
							for (int k = 0; k < nbCentresOrangesCherches; k++) {
								if ( xCentre - rayonSecteur < listeCentres[k].x && xCentre + rayonSecteur > listeCentres[k].x
								&& yCentre - rayonSecteur < listeCentres[k].y && yCentre + rayonSecteur > listeCentres[k].y )
								{
									dejaTrouve = true;
									break;
								}
							}
						} else if (mID == BLEU) {
							for (int k = nbCentresOrangesCherches; k < nbCentresOrangesCherches + nbCentresBleusCherches; k++) {
								if ( xCentre - rayonSecteur < listeCentres[k].x && xCentre + rayonSecteur > listeCentres[k].x
								&& yCentre - rayonSecteur < listeCentres[k].y && yCentre + rayonSecteur > listeCentres[k].y )
								{
									dejaTrouve = true;
									break;
								}
							}
						}

						// Si le centre est bien un nouveau, on l'ajoute � la liste
						if (!dejaTrouve)
						{
							Point coord(xCentre, yCentre, 0);
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
			// Si tous les marqueurs n'ont pas �t� trouv�s, on rajoute des �l�ments pour que le vecteur soit bien de taille nbCentresCherches (les coords st alors en bas � droite)
			delete pVector;
			for (int ajout = 0; ajout < nbCentresCherches - nbCentresTrouves; ajout++) {
				Point coord;
				coord = new int[3];
				coord.x = lWidth - 1;
				coord.y = lHeight - 1;
				coord.z = 0;
				listeCentres.push_back(coord);
				}
			return listeCentres;
		}*/

	}


	void placerMarqueurs(unsigned char * image, std::vector<Point> centres, int width, int height)
	{
		int lWidth =  width;
		int lHeight = height;
		int lNbComp = 3;
		int largMarque = 3;   // 3

		for (unsigned int centre = 0; centre < centres.size(); centre++) 
		{
			int x = centres[centre].x;
			int y = centres[centre].y;

			for (int dx = -largMarque; dx < largMarque+1; dx++) {
				for (int dy = -largMarque; dy < largMarque+1; dy++) {
					if (x+dx >= 0 && x+dx < lWidth && y+dy >= 0 && y+dy < lHeight) {
						if (centre == 0) {    // Base du bras (vert)
							image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 255;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 0;
						} else if (centre == 1) {    // Extr�mit� du bras (bleu)
							image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 255;
						} else if (centre == 2) {    // Point angulaire 1 du haut (rouge)
							image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 255;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 0;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 0;
						} else if (centre == 3) {    // Point angulaire 2 du bas (gris)
							image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 128;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 128;
							image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 128;
						}
					}
				}
			}
		}

	}


	void remplirProfondeur(unsigned short * depth, std::vector<Point> &centres, int width, int height)
	{
		int lWidth =  width;
		int lHeight = height;
		for (unsigned int centre = 0; centre < centres.size(); centre++) 
		{
			int x = centres[centre].x;
			int y = centres[centre].y;
			centres[centre].z = depth[y*lWidth + x];
			/*if (centre == 0) {
				cout << "profondeur de centre[" << centre << "] = " << centres[centre][2] << endl; 
			}*/
		}
	}

	void followLeftConvention(std::vector<Point>& centres)
	{
		if (centres.size() > 1) { // TODO: not safe for size > 2
			if (centres[0].x > centres[1].x) {
				Point aux(centres[0]);
				centres[0] = centres[1];
				centres[1] = aux;
			}
			if (centres.size() > 3) {
				if (centres[2].y < centres[3].y && centres[2].x > centres[3].x) {
					Point aux2(centres[2]);
					centres[2] = centres[3];
					centres[3] = aux2;
				}
			}
		}
	}

	float calculAngle(Point p1, Point p2)
	{
		Point segment(p2 - p1);
		segment.z = 0.0;
		float segNorm = sqrt(segment.squareNorm());
		segment = segment / segNorm;
		Point axe(1.0, 0.0, 0.0);
		float prodScal = acos(segment * axe);
		if (segment.y < 0.0) {
			prodScal = -prodScal;
		}
		return prodScal;
	}


}
