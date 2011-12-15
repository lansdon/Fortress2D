#include "GOSeigeEngine.h"


GOSeigeEngine::GOSeigeEngine(Settings *settings, double x, double y) : GameObj(settings, x, y)
{
	// Startup / Load / Initialization routine   (Use in constructor of derived classes to setup the object!!)
	loadObject("seigeengine.dat", x, y);

}


GOSeigeEngine::~GOSeigeEngine(void)
{
}
