#include "stdafx.h"
#include "Image.h"

using namespace Toolbox;
using namespace std;

Image::Image(int pNbPoints)
{
	nbPoints = pNbPoints;
	mPositionsCenter = new int*[pNbPoints];
	for (int i = 0; i<pNbPoints; i++)
	{
		mPositionsCenter[i] = new int[3];
		mPositionsCenter[i][0] = 639;
		mPositionsCenter[i][1] = 479;
		mPositionsCenter[i][2] = 479;
	}
}

Image::~Image()
{
	for (int i = 0; i < nbPoints; i++)
	{
		delete mPositionsCenter[i];
	}
	delete mPositionsCenter;
}

void Image::premiere_detection(unsigned char * pVector, std::vector<MarqueurId> marqueurs)
{
	int lWidth =  640;
	int lHeight = 480;
	int lNbComp = 4;
	int nbCentresTrouves = 0;


	// Parcours des pixels de l'image
	for (int i = 0; i < lHeight; i++)
	{
		for (int j = 0; j < lWidth; j++)
		{
			// Lecture des composantes RVB du pixel
			int blueComp = pVector[lNbComp * (i*lWidth + j)];
			int greenComp = pVector[lNbComp * (i*lWidth + j) + 1];
			int redComp = pVector[lNbComp * (i*lWidth + j) + 2];

			// Le pixel correspond-il à un marqueur ?
			if (surMarqueur(redComp, greenComp, blueComp, ORANGE, false))
			{
				/*ofstream outFile("trace.txt", ios::out);
				if (!outFile.is_open()) {
					cout << "Erreur : impossible d'ouvrir trace.txt" << endl;
					system("pause");
					exit(0);
				}
				outFile << "Premier pixel ok en (" << j << "," << i << ") : " << redComp << " " << greenComp << " " << blueComp << endl;*/

				// Calcul du diamètre du marqueur
				int hauteur = 1;
				int indiceParcours = i + 1;
				blueComp = pVector[lNbComp * (indiceParcours*lWidth + j)];
				greenComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 1];
				redComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 2];
				while (surMarqueur(redComp, greenComp, blueComp, ORANGE, false))
				{
					hauteur++;
					indiceParcours++;
					blueComp = pVector[lNbComp * (indiceParcours*lWidth + j)];
					greenComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 1];
					redComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 2];
				}

				//outFile << "Premier pixel KO en (" << j << "," << indiceParcours << ") : " << redComp << " " << greenComp << " " << blueComp << endl;
				//outFile.close();


				// Lecture des composantes RVB d'un pixel à gauche (un peu éloigné du centre) (afin de filtrer les cas de lignes verticales de couleur du marqueur)
				int blueCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4)];
				int greenCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4) + 1];
				int redCompG = pVector[lNbComp * (i*lWidth + j - hauteur/4) + 2];

				// Lecture des composantes RVB d'un pixel à droite (un peu éloigné du centre) (afin de filtrer les cas de lignes verticales de couleur du marqueur)
				int blueCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4)];
				int greenCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4) + 1];
				int redCompD = pVector[lNbComp * (i*lWidth + j + hauteur/4) + 2];

				// Si la hauteur est inférieure à une hauteur minimale, ou si l'un des pixels "voisins" gauche ou droite n'est pas un marqueur, on considère qu'il ne s'agit pas du marqueur
				if (hauteur >= 20 && surMarqueur(redCompG, greenCompG, blueCompG, ORANGE, false) && surMarqueur(redCompD, greenCompD, blueCompD, ORANGE, false)) {

					// Détermination du centre du marqueur
					int xCentre = j;
					int yCentre = i + (hauteur/2);

					// On recherche un centre déjà trouvé et se trouvant près du nouveau centre
					int rayonSecteur = hauteur/2 + 5;
					bool dejaTrouve = false;
					for (int k = 0; k < nbCentresTrouves; k++) {
						if ( xCentre - rayonSecteur < mPositionsCenter[k][0] && xCentre + rayonSecteur > mPositionsCenter[k][0]
						&& yCentre - rayonSecteur < mPositionsCenter[k][1] && yCentre + rayonSecteur > mPositionsCenter[k][1] )
						{
							dejaTrouve = true;
							break;
						}
					}

					// Si le centre est bien un nouveau, on l'ajoute à la liste
					if (!dejaTrouve)
					{
						mPositionsCenter[nbCentresTrouves][0] = xCentre;
						mPositionsCenter[nbCentresTrouves][1] = yCentre;
						nbCentresTrouves++;
						if (nbCentresTrouves == nbPoints)
						{
							return;
						}
					}
				}
			}
		}
	}

	if (nbCentresTrouves != nbPoints)
	{
		//std::cout << "Erreur : tous les marqueurs n'ont pas été trouvés" << std::endl;
	}

}


void Image::placerMarqueurs(unsigned char * image)
{
	int lWidth =  640;
	int lHeight = 480;
	int lNbComp = 4;
	int largMarque = 3;   // 3

	for (int centre = 0; centre < nbPoints; centre++) 
	{
		int x = mPositionsCenter[centre][0];
		int y = mPositionsCenter[centre][1];

		for (int dx = -largMarque; dx < largMarque+1; dx++) {
			for (int dy = -largMarque; dy < largMarque+1; dy++) {
				if (x+dx >= 0 && x+dx < lWidth && y+dy >= 0 && y+dy < lHeight) {
					image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 0;
					image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 0;
					image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 255;
				}
			}
		}
	}

}


void Image::remplirProfondeur(unsigned char * depth)
{
	int lWidth =  640;
	int lHeight = 480;
	int lNbComp = 4;
	for (int centre = 0; centre < nbPoints; centre++) 
	{
		int x = mPositionsCenter[centre][0];
		int y = mPositionsCenter[centre][1];
		mPositionsCenter[centre][2] = depth[y*lWidth + x];
	}
}
