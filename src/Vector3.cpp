#include "Vector3.h"


Vector3::Vector3(void)
{
	posX=posY=posZ=0;
}

Vector3::Vector3(double x, double y, double z) { 
	set(x, y, z); 
}

Vector3::~Vector3(void)
{
}
