#include "Image.h"

using namespace Toolbox;

Image::Image(int pmNbPoints) :
	mNbPoints(0),
	mNbPointsMax(pmNbPoints),
	mPositionsCenter(new int*[mNbPointsMax])
{
	for (int i = 0; i<mNbPointsMax; i++) {
		mPositionsCenter[i] = new int[2];
	}
}

Image::~Image()
{
	for (int i = 0; i < mNbPointsMax; i++)
	{
		delete mPositionsCenter[i];
	}
	delete mPositionsCenter;
}

void Image::premiere_detection(std::vector<uint8_t> pVector, float *pColor)
{
	int lWidth =  640;
	int lHeight = 480;
	int lNbComp = static_cast<int>(pVector.size()) / lWidth / lHeight; // TODO: clean that
	int lProfMax = 255;  // Profondeur maximale pour l'analyse des pixels

	mNbPoints = 0;

	// Parcours des pixels de l'image
	for (int i = 0; i < lHeight; i++)
	{
		for (int j = 0; j < lWidth; j++)
		{
			int profComp = pVector[lNbComp * (i*lWidth + j) + 3];
	
			// On analyse seulement les pixels assez proches
			if (profComp <= lProfMax)
			{
				// Lecture des composantes RVB
				int lRedComp = pVector[lNbComp * (i*lWidth + j)];
				int lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
				int lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];

				// Le pixel correspond-il � un marqueur ?
				if (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
				{
					// Calcul du diam�tre du marqueur
					int hauteur = 1;
					int indiceParcours = i + 1;
					lRedComp = pVector[lNbComp * (indiceParcours*lWidth + j)];
					lGreenComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 1];
					lBlueComp = pVector[lNbComp * (indiceParcours*lWidth + j) + 2];
					while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
					{
						hauteur++;
						indiceParcours++;
						lRedComp = pVector[lNbComp * (i*lWidth + indiceParcours)];
						lGreenComp = pVector[lNbComp * (i*lWidth + indiceParcours) + 1];
						lBlueComp = pVector[lNbComp * (i*lWidth + indiceParcours) + 2];
					}

					// D�termination du centre du marqueur
					int xCentre = j;
					int yCentre = i + (hauteur/2);

					// On recherche un centre d�j� trouv� et se trouvant pr�s du nouveau centre
					int rayonSecteur = hauteur/2 + 5;
					bool dejaTrouve = false;
					for (int k = 0; k < mNbPoints; k++) {
						if ( xCentre - rayonSecteur < mPositionsCenter[k][0] && xCentre + rayonSecteur > mPositionsCenter[k][0]
						&& yCentre - rayonSecteur < mPositionsCenter[k][1] && yCentre + rayonSecteur > mPositionsCenter[k][1] )
						{
							dejaTrouve = true;
							break;
						}
					}

					// Si le centre est bien un nouveau, on l'aoute � la liste
					if (!dejaTrouve)
					{
						mPositionsCenter[mNbPoints][0] = xCentre;
						mPositionsCenter[mNbPoints][1] = yCentre;
						mNbPoints++;
						if (mNbPoints == mNbPointsMax)
						{
							return;
						}
					}
				}
			}
		}
	}

	if (mNbPoints != mNbPointsMax)
	{
		std::cout << "Erreur : tous les marqueurs n'ont pas �t� trouv�s" << std::endl;
	}
}

void Image::detections_en_cours(std::vector<uint8_t> pVector, float *pColor)
{
	int lWidth =  640;
	//int lHeight = 480;
	int lNbComp = 4;

	int lWinSize = 10;
	bool lLeftBorder;
	bool lHighBorder;
	bool lFound;
	int lXFound;
	int lYFound;
	int lRedComp, lGreenComp, lBlueComp;

	for (int lNumCenter = 0; lNumCenter < mNbPoints; lNumCenter++)
	{
		//Traiter plus tard les cas de d�passement d'indice (min , max)
		for (int i = mPositionsCenter[lNumCenter][1]-lWinSize; i <= mPositionsCenter[lNumCenter][1]+lWinSize; i++)
		{
			lHighBorder = (i ==  mPositionsCenter[lNumCenter][1]-lWinSize);
			for (int j = mPositionsCenter[lNumCenter][0]-lWinSize; j <= mPositionsCenter[lNumCenter][0]+lWinSize; j++)
			{
				lLeftBorder = (j == mPositionsCenter[lNumCenter][0]-lWinSize);
				lRedComp = pVector[lNbComp * (i*lWidth + j)];
				lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
				lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];
				lFound = (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor));
				if (lFound)
				{
					lXFound = j;
					lYFound = i;
					break;
				}
			}
			if (lFound)
			{
				break;
			}
		}

		if (!lFound)
		{
			printf("erreur\n");
		}
		else
		{
			if (lLeftBorder && lHighBorder)
			{
				detection_left_corner(pVector, pColor, lXFound, lYFound, lNumCenter);
			}
			else if (lLeftBorder)
			{
				detection_left_border(pVector, pColor, lXFound, lYFound, lNumCenter);
			}
			else if (lHighBorder)
			{
				detection_high_border(pVector, pColor, lXFound, lYFound, lNumCenter);
			}
			else
			{
				detection_normal(pVector, pColor, lXFound, lYFound, lNumCenter);
			}
		}
	}
}

void Image::detection_normal(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter)
{
	int lWidth =  640;
	//int lHeight = 480;
	int lNbComp = 4;

	int i = pYFound;
	int j = pXFound;
	int lRedComp = pVector[lNbComp * (i*lWidth + j)];
	int lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
	int lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		j++;
		lRedComp = pVector[lNbComp * (i*lWidth + j)];
		lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];
	}

	j -= 1;
	j = (j + pXFound)/2;
	mPositionsCenter[pNumCenter][0] = j;

	lRedComp = pVector[lNbComp * (i*lWidth + j)];
	lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
	lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		i++;
		lRedComp = pVector[lNbComp * (i*lWidth + j)];
		lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];
	}

	i -= 1;
	i = (i+pYFound)/2;
	mPositionsCenter[pNumCenter][1] = i;
}

void Image::detection_left_border(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter)
{
	int lWidth =  640;
	//int lHeight = 480;
	int lNbComp = 4;

	int i = pYFound;	
	int jRight = pXFound;
	int lRedComp = pVector[lNbComp * (i*lWidth + jRight)];
	int lGreenComp = pVector[lNbComp * (i*lWidth + jRight) + 1];
	int lBlueComp = pVector[lNbComp * (i*lWidth + jRight) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		jRight++;
		lRedComp = pVector[lNbComp * (i*lWidth + jRight)];
		lGreenComp = pVector[lNbComp * (i*lWidth + jRight) + 1];
		lBlueComp = pVector[lNbComp * (i*lWidth + jRight) + 2];
	}

	jRight -= 1;

	int jLeft = pXFound;
	lRedComp = pVector[lNbComp * (i*lWidth + jLeft)];
	lGreenComp = pVector[lNbComp * (i*lWidth + jLeft) + 1];
	lBlueComp = pVector[lNbComp * (i*lWidth + jLeft) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		jLeft--;
		lRedComp = pVector[lNbComp * (i*lWidth + jLeft)];
		lGreenComp = pVector[lNbComp * (i*lWidth + jLeft) + 1];
		lBlueComp = pVector[lNbComp * (i*lWidth + jLeft) + 2];
	}

	jLeft -= 1;
	int j = (jLeft+jRight)/2;
	mPositionsCenter[pNumCenter][0] = j;

	lRedComp = pVector[lNbComp * (i*lWidth + j)];
	lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
	lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		i++;
		lRedComp = pVector[lNbComp * (i*lWidth + j)];
		lGreenComp = pVector[lNbComp * (i*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (i*lWidth + j) + 2];
	}

	i -= 1;
	i = (i+pYFound)/2;
	mPositionsCenter[pNumCenter][1] = i;
}

void Image::detection_high_border(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter)
{
	int lWidth =  640;
	//int lHeight = 480;
	int lNbComp = 4;

	int iBottom = pYFound;	
	int j = pXFound;
	int lRedComp = pVector[lNbComp * (iBottom*lWidth + j)];
	int lGreenComp = pVector[lNbComp * (iBottom*lWidth + j) + 1];
	int lBlueComp = pVector[lNbComp * (iBottom*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		j++;
		lRedComp = pVector[lNbComp * (iBottom*lWidth + j)];
		lGreenComp = pVector[lNbComp * (iBottom*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (iBottom*lWidth + j) + 2];
	}

	j -= 1;
	j = (j + pXFound)/2;
	mPositionsCenter[pNumCenter][0] = j;
 
	lRedComp = pVector[lNbComp * (iBottom*lWidth + j)];
	lGreenComp = pVector[lNbComp * (iBottom*lWidth + j) + 1];
	lBlueComp = pVector[lNbComp * (iBottom*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		iBottom++;
		lRedComp = pVector[lNbComp * (iBottom*lWidth + j)];
		lGreenComp = pVector[lNbComp * (iBottom*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (iBottom*lWidth + j) + 2];
	}
	iBottom -= 1;

	int iTop = pYFound;
	lRedComp = pVector[lNbComp * (iTop*lWidth + j)];
	lGreenComp = pVector[lNbComp * (iTop*lWidth + j) + 1];
	lBlueComp = pVector[lNbComp * (iTop*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		iTop--;
		lRedComp = pVector[lNbComp * (iTop*lWidth + j)];
		lGreenComp = pVector[lNbComp * (iTop*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (iTop*lWidth + j) + 2];
	}

	iTop -= 1;
	int i = (iTop+iBottom)/2;
	mPositionsCenter[pNumCenter][1] = i;
}

void Image::detection_left_corner(std::vector<uint8_t> pVector, float *pColor, int pXFound, int pYFound, int pNumCenter)
{
	int lWidth =  640;
	//int lHeight = 480;
	int lNbComp = 4;

	int iBottom = pYFound;	
	int jRight = pXFound;
	int lRedComp = pVector[lNbComp * (iBottom*lWidth + jRight)];
	int lGreenComp = pVector[lNbComp * (iBottom*lWidth + jRight) + 1];
	int lBlueComp = pVector[lNbComp * (iBottom*lWidth + jRight) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		jRight++;
		lRedComp = pVector[lNbComp * (iBottom*lWidth + jRight)];
		lGreenComp = pVector[lNbComp * (iBottom*lWidth + jRight) + 1];
		lBlueComp = pVector[lNbComp * (iBottom*lWidth + jRight) + 2];
	}

	jRight -= 1;

	int jLeft = pXFound;
	lRedComp = pVector[lNbComp * (iBottom*lWidth + jLeft)];
	lGreenComp = pVector[lNbComp * (iBottom*lWidth + jLeft) + 1];
	lBlueComp = pVector[lNbComp * (iBottom*lWidth + jLeft) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		jLeft--;
		lRedComp = pVector[lNbComp * (iBottom*lWidth + jLeft)];
		lGreenComp = pVector[lNbComp * (iBottom*lWidth + jLeft) + 1];
		lBlueComp = pVector[lNbComp * (iBottom*lWidth + jLeft) + 2];
	}

	jLeft -= 1;
	int j = (jLeft+jRight)/2;
	mPositionsCenter[pNumCenter][0] = j;

	lRedComp = pVector[lNbComp * (iBottom*lWidth + j)];
	lGreenComp = pVector[lNbComp * (iBottom*lWidth + j) + 1];
	lBlueComp = pVector[lNbComp * (iBottom*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		iBottom++;
		lRedComp = pVector[lNbComp * (iBottom*lWidth + j)];
		lGreenComp = pVector[lNbComp * (iBottom*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (iBottom*lWidth + j) + 2];
	}

	iBottom -= 1;

	int iTop = pYFound;
	lRedComp = pVector[lNbComp * (iTop*lWidth + j)];
	lGreenComp = pVector[lNbComp * (iTop*lWidth + j) + 1];
	lBlueComp = pVector[lNbComp * (iTop*lWidth + j) + 2];

	while (surMarqueur(lRedComp, lGreenComp, lBlueComp, pColor))
	{
		iTop--;
		lRedComp = pVector[lNbComp * (iTop*lWidth + j)];
		lGreenComp = pVector[lNbComp * (iTop*lWidth + j) + 1];
		lBlueComp = pVector[lNbComp * (iTop*lWidth + j) + 2];
	}

	iTop -= 1;
	int i = (iTop+iBottom)/2;
	mPositionsCenter[pNumCenter][1] = i;
}
