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
		mPositionsCenter[i] = new int[2];
		mPositionsCenter[i][0] = 0;
		mPositionsCenter[i][1] = 0;
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

void Image::premiere_detection(unsigned char * pVector, float *pColor)
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
			// Lecture des composantes RVB
			int blueComp = pVector[lNbComp * (i*lWidth + j)];
			int greenComp = pVector[lNbComp * (i*lWidth + j) + 1];
			int redComp = pVector[lNbComp * (i*lWidth + j) + 2];

			// Le pixel correspond-il à un marqueur ?
			if (surMarqueur(redComp, greenComp, blueComp, pColor, false))
			{
				// Calcul du diamètre du marqueur
				int hauteur = 1;
				int indiceParcours = i + 1;
				redComp = pVector[lNbComp * (indiceParcours*lWidth + j)];
				greenComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 1];
				blueComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 2];
				while (surMarqueur(redComp, greenComp, blueComp, pColor, false))
				{
					hauteur++;
					indiceParcours++;
					redComp = pVector[lNbComp * (i*lWidth + indiceParcours)];
					greenComp = pVector[lNbComp * (i*lWidth + indiceParcours) + 1];
					blueComp = pVector[lNbComp * (i*lWidth + indiceParcours) + 2];
				}

				// MODIF AJOUTEE : Si la hauteur est inférieur à une hauteur minimale, on considère qu'il ne s'agit pas du marqueur
				if (hauteur >= 0) {

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

					// Si le centre est bien un nouveau, on l'aoute à la liste
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

	for (int centre = 0; centre < nbPoints; centre++) 
	{
		int x = mPositionsCenter[centre][0];
		int y = mPositionsCenter[centre][1];

		for (int dx = -3; dx < 4; dx++) {
			for (int dy = -3; dy < 4; dy++) {
				if (x+dx >= 0 && x+dx < lWidth && y+dy >= 0 && y+dy < lHeight) {
					image[ lNbComp*((y+dy)*lWidth + x + dx) ] = (unsigned char) 0;
					image[ lNbComp*((y+dy)*lWidth + x + dx) + 1] = (unsigned char) 255;
					image[ lNbComp*((y+dy)*lWidth + x + dx) + 2] = (unsigned char) 0;
				}
			}
		}
	}

}

