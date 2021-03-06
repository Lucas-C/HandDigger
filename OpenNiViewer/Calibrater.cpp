#include "Calibrater.h"
#include <cmath>

Calibrater::Calibrater()
{
	mNumberAxis = 0;
	mNumberUser = 0;
	mSheetColor[0] = 250;
	mSheetColor[1] = 250;
	mSheetColor[2] = 250;
}

Calibrater::~Calibrater()
{
}

void Calibrater::LookSheet(unsigned char * Image, unsigned short * DepthTab, int *color, int *width, int *height, int * depth)
{
	int sumx = 0;
	int	sumy = 0;
	int nbPoints = 0;
	int epsilon = 10;
	
	for (int i = 0; i < 480; i++)
	{
		for (int j = 0; j < 640; j++)
		{
			int indice = 3*(i*640+j);
			if (abs(Image[indice] - color[0]) < epsilon && abs(Image[indice+1] - color[1]) < epsilon && abs(Image[indice+2] - color[2]) < epsilon)
			{
				sumx += j;
				sumy += i;
				nbPoints++;
			}
		}
	}

	double moyx = (double) sumx / (double) nbPoints;
	double moyy = (double) sumy / (double) nbPoints;
	
	int ligne_cour = moyy-1;
	double couleur_moy_line[3];
	couleur_moy_line[0] = color[0];
	couleur_moy_line[1] = color[1];
	couleur_moy_line[2] = color[2];
	while (fabs(couleur_moy_line[0] - color[0]) < epsilon && fabs(couleur_moy_line[1] - color[1]) < epsilon && fabs(couleur_moy_line[2] - color[2]) < epsilon && ligne_cour > 0)
	{
		couleur_moy_line[0] = 0.0;
		couleur_moy_line[1] = 0.0;
		couleur_moy_line[2] = 0.0;
		for (int x = moyx-10; x <= moyx+10; x++)
		{	
			int indice = 3*(ligne_cour*640+x);
			couleur_moy_line[0] += Image[indice];
			couleur_moy_line[1] += Image[indice+1];
			couleur_moy_line[2] += Image[indice+2];
		}
		couleur_moy_line[0] /= 21.0;
		couleur_moy_line[1] /= 21.0;
		couleur_moy_line[2] /= 21.0;
		ligne_cour--;
	}
	*height = 2*(moyy - (ligne_cour+1))+1;
	*width = nbPoints/(*height); //le bruit va dans la largeur, ou pas !
	*depth = DepthTab[3*((int)moyy*640+(int)moyx)];

}

void Calibrater::calibrationAxis(unsigned short *Depth, unsigned char *Image)
{
	std::cout << "Calibration..." << std::endl;
	if (mNumberAxis%2 == 0)
	{
		LookSheet(Image, Depth, mSheetColor, &mFirstWidth, &mFirstHeight, &mFirstDepth);
		mNumberAxis++;
	}
	else
	{
		//Horizontal field of view: 57 degrees. Vertical field of view: 43 degrees
		mFirstRealMeasure = 1.0;
		mSecondRealMeasure = 2.0;
		LookSheet(Image, Depth, mSheetColor, &mSecondWidth, &mSecondHeight, &mSecondDepth);
		mCoefADepth = (mFirstDepth - mSecondDepth)/(mFirstRealMeasure - mSecondRealMeasure);
		mCoefBDepth = (mFirstDepth - mFirstRealMeasure)/mCoefADepth; 
		mSheetWidth = 0.297;
		mFocalLength = mFirstWidth*mFirstRealMeasure/mSheetWidth;
		mNumberAxis++;
	}
}

void Calibrater::calibrationUser(std::vector<Point> Centers)
{
	double x0, y0, prof0;
	KinectToCamera(Centers[0].x, Centers[0].y, Centers[0].z, &x0, &y0, &prof0);
	double x1, y1, prof1;
	KinectToCamera(Centers[1].x, Centers[1].y, Centers[1].z, &x1, &y1, &prof1);
	if (mNumberUser%6 == 0)
	{
		mNumberUser++;
		mXmin = x1 - x0;
	}
	else if (mNumberUser%6 == 1)
	{
		mNumberUser++;
		mXmax = x1 - x0;
	}
	else if (mNumberUser%6 == 2)
	{
		mNumberUser++;
		mYmin = y1 - y0;
	}
	else if (mNumberUser%6 == 3)
	{
		mNumberUser++;
		mYmax = y1 - y0;
	}
	else if (mNumberUser%6 == 4)
	{
		mNumberUser++;
		mProfmin = prof1 - prof0;
	}
	else if (mNumberUser%6 == 5)
	{
		mNumberUser++;
		mProfmax = prof1 - prof0;
	}
}

void Calibrater::KinectToCamera(double Kinectx, double Kinecty, double Kinectprof, double *Worldx, double *Worldy, double *Worldprof)
{
	*Worldprof = (Kinectprof - mCoefBDepth)/mCoefADepth;
	*Worldx = (Kinectx-320.0)*(*Worldprof)/mFocalLength;
	*Worldy = (Kinecty-240.0)*(*Worldprof)/mFocalLength;
}

void Calibrater::CameraToShovel(double VecWorldx, double VecWorldy, double VecWorldprof, double *Shovelx, double *Shovely, double *Shovelz)
{
	*Shovelx = VecWorldx/(mXmax-mXmin);
	*Shovely = VecWorldy/(mYmax-mYmin);
	*Shovelz = VecWorldprof/(mProfmax - mProfmin);
}

void Calibrater::setSheetColor(int r, int g, int b)
{
	mSheetColor[0] = r;
	mSheetColor[1] = g;
	mSheetColor[2] = b;
}


