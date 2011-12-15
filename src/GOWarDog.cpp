#include "GOWarDog.h"


GOWarDog::GOWarDog(Settings *settings, double x, double y) : GameObj(settings, x, y)
{

	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("wardog.dat", x, y);


}


GOWarDog::~GOWarDog(void)
{
}
