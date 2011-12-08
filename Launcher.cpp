#include "Launcher.h"


Launcher::Launcher(void) : GameObj(
{

	MIN_VEL = 0.5;			// Lower bounds of launch velocity meters/sec
	MAX_VEL = 10;			// Upper bounds of launch velocity meters/sec
	LEFT_ORIENTATION = true; // true = facing left    false = facing right
	MIN_ANGLE = -45.0;			// MIN angle allowed relative to direction facing (0 = horizontal plane. POS = up, neg = down.
	MAX_ANGLE = 85.0;			// degrees



}


Launcher::~Launcher(void)
{
}
