#include "Util.h"

const double Util::PI = 3.141592653589793238;
const double Util::METER_PER_PIXEL = 8;						// meters per pixel  (100m / 800px) 

Util::Util(void)
{
}


Util::~Util(void)
{
}


double Util::rad2Deg (double Angle) {
	static double ratio = 180.0 / PI;
	return Angle * ratio;
}

double Util::deg2Rad (double Angle) {
	static double ratio = PI / 180.0;
	return Angle * ratio;
}

double Util::meter2Pixel(double meters) {
	return meters * METER_PER_PIXEL;
}

double Util::pixel2Meter(double pixel) {
	return pixel / METER_PER_PIXEL;
}

// Convert coordinates to lower left corner coordinates
Vector3 Util::convertCenter2LowerLeft(Vector3 coords, Settings *settings) {
	coords.set(convertCenter2LowerLeftX(coords.x(), settings), convertCenter2LowerLeftY(coords.y(), settings), coords.z());
	return coords;
}
// Convert coordinates to lower left corner coordinates
double Util::convertCenter2LowerLeftX(double x, Settings *settings) {
	return x + settings->width()/2;
}
// Convert coordinates to lower left corner coordinates
double Util::convertCenter2LowerLeftY(double y, Settings *settings) {
	return y + settings->height()/2;
}

double Util::normAngle(double angle) {
	if(angle < 0) {
		angle += 360;
	} 
	return angle;
}


