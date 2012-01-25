#include <cstdio>
#include <vector>
class Calibrater
{
public:
	Calibrater();
	~Calibrater();
	void LookSheet(unsigned char * Image, unsigned short * DepthTab, int *color, int *width, int *height, int * depth);
	void calibrage(unsigned short *Depth, unsigned char *Image);
	void KinectToCamera(double Kinectx, double Kinecty, double Kinectprof, double *Worldx, double *Worldy, double *Worldprof);
	void setSheetColor(int r, int g, int b);

private:
	int mNumero;
	int mFirstHeight;
	int mFirstWidth;
	int mFirstDepth;
	int mSecondHeight;
	int mSecondWidth;
	int mSecondDepth;
	int mSheetColor[3];
	double mFirstRealMeasure;
	double mSecondRealMeasure;
	double mCoefADepth;
	double mCoefBDepth;
	double mSheetWidth;
	double mFocalLength;
};