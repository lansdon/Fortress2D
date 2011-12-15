#include "GOFence.h"


GOFence::GOFence(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("fence.dat", x, y);

}


GOFence::~GOFence(void)
{
}
