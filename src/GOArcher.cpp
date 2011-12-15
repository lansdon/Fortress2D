#include "GOArcher.h"



GOArcher::GOArcher(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("archer.dat", x, y);

}

GOArcher::~GOArcher(void)
{
}
