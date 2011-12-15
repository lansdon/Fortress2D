#include "GOBarbarian.h"


GOBarbarian::GOBarbarian(Settings *settings, double x, double y) : GameObj(settings, x, y)
{

	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("barbarian.dat", x, y);


}


GOBarbarian::~GOBarbarian(void)
{
}
