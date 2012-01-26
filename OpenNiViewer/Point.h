#ifndef DEF_H_POINT_
#define DEF_H_POINT_

#include <iostream>

class Point {
public:
	double x;
	double y;
	double z;
	Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
	Point() : x(0), y(0), z(0) {}
	double squareNorm() const { return x * x + y * y + z * z; }
	double norm() const { return sqrt(squareNorm()); }
	Point operator*(double f) const { return Point(x * f, y * f, z * f); }
	Point operator/(double f) const { return Point(x / f, y / f, z / f); }
	double operator*(const Point& p) { return x*p.x + y*p.y + z*p.z; }
	Point operator+(const Point& p) const { return Point(x + p.x, y + p.y, z + p.z); }
	Point operator-(const Point& p) const { return Point(x - p.x, y - p.y, z - p.z); }
	std::ostream& operator>>(std::ostream &strm) const {
		return strm << "  " << x << "  " << y << "  " << z;
	}
};

inline std::ostream& operator<<(std::ostream &strm, Point p) {
	return p >> strm;
}

#endif //DEF_H_POINT_