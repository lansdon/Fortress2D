#pragma once

#include <windows.h>		// Header File For Windows
#include <math.h>			// Header File For Windows Math Library
#include <stdio.h>			// Header File For Standard Input/Output
#include <stdarg.h>			// Header File For Variable Argument Routines
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <string>
#include <sstream>
#include "Vector3.h"
#include "WinParems.h"


class Util
{
public:
	Util(void);
	~Util(void);

	static const double PI;
	static const double METER_PER_PIXEL; 
	static double Util::rad2Deg (double Angle);
	static double Util::deg2Rad (double Angle);
	static double meter2Pixel(double meters);
	static double pixel2Meter(double pixel);
	static Vector3 Util::convertCenter2LowerLeft(Vector3 coords, WinParems *parems);
	static double Util::convertCenter2LowerLeftX(double x, WinParems *parems);
	static double Util::convertCenter2LowerLeftY(double y, WinParems *parems);

	
	static struct Color {
		Color() {
			setColors(0, 0, 0, 0);
		}
		Color(float rin, float gin, float bin, float ain) {
			setColors(rin, gin, bin, ain);
		}
		void setColors(float rin, float gin, float bin, float ain) {
			rin > 1.0 ? r = 1.0 : r = rin; // 0-1 values allowed
			gin > 1.0 ? g = 1.0 : g = gin; // 0-1 values allowed
			bin > 1.0 ? b = 1.0 : b = rin; // 0-1 values allowed
			ain > 1.0 ? a = 1.0 : a = ain; // 0-1 values allowed
			if(r<0) r=0; // 0-1 values allowed
			if(b<0) b=0; // 0-1 values allowed
			if(g<0) g=0; // 0-1 values allowed
			if(a<0) a=0; // 0-1 values allowed
		}
		float r, b, g, a;   
	};


private:

};

