#include "GOWoodWall.h"


GOWoodWall::GOWoodWall(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
				
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("woodwall.dat", x, y);
}


GOWoodWall::~GOWoodWall()
{
}
