#include "GOMageTower.h"


GOMageTower::GOMageTower(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("magetower.dat", x, y);

}


GOMageTower::~GOMageTower()
{
}
