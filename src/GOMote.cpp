#include "GOMote.h"


GOMote::GOMote(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("mote.dat", x, y);

}


GOMote::~GOMote(void)
{
}
