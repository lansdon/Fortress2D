#include "GOOilTower.h"


GOOilTower::GOOilTower(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("oiltower.dat", x, y);

}


GOOilTower::~GOOilTower(void)
{
}
