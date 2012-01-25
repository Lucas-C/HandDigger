#ifndef DEF_H_POINT_
#define DEF_H_POINT_

#include <iostream>

class Point {
public:
	float x;
	float y;
	float z;
	Point(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
	Point() : x(0), y(0), z(0) {}
	float squareNorm() const { return x * x + y * y + z * z; }
	Point operator*(float f) { return Point(x * f, y * f, z * f); }
	Point operator/(float f) { return Point(x / f, y / f, z / f); }
	float operator*(const Point& p) { return x*p.x + y*p.y + z*p.z; }
	Point operator+(const Point& p) { return Point(x + p.x, y + p.y, z + p.z); }
	Point operator-(const Point& p) { return Point(x - p.x, y - p.y, z - p.z); }
	std::ostream& operator>>(std::ostream &strm) const {
		return strm << "  " << x << "  " << y << "  " << z;
	}
};

inline std::ostream& operator<<(std::ostream &strm, Point p) {
	return p >> strm;
}

#endif //DEF_H_POINT_