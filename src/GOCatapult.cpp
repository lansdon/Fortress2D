#include "GOCatapult.h"


GOCatapult::GOCatapult(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("catapult.dat", x, y);

}


GOCatapult::~GOCatapult(void)
{
}
