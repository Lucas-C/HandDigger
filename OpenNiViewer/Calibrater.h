#include <cstdio>
#include <vector>
#include "Point.h"

class Calibrater
{
public:
	Calibrater();
	~Calibrater();
	void LookSheet(unsigned char * Image, unsigned short * DepthTab, int *color, int *width, int *height, int * depth);
	void calibrationAxis(unsigned short *Depth, unsigned char *Image);
	void calibrationUser(std::vector<Point> Centers);
	void KinectToCamera(double Kinectx, double Kinecty, double Kinectprof, double *Worldx, double *Worldy, double *Worldprof);
	void setSheetColor(int r, int g, int b);

private:
	int mNumberAxis;
	int mNumberUser;
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
	double mXmin;
	double mXmax;
	double mYmin;
	double mYmax;
};