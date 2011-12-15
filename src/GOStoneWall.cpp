#include "GOStoneWall.h"


GOStoneWall::GOStoneWall(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("stonewall.dat", x, y);

}


GOStoneWall::~GOStoneWall(void)
{
}

