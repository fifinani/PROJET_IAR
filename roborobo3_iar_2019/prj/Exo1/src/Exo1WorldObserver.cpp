/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */


#include "Exo1/include/Exo1WorldObserver.h"
#include "World/World.h"
#include "Utilities/Misc.h"
#include "Exo1/include/Exo1Controller.h"
#include "RoboroboMain/roborobo.h"


Exo1WorldObserver::Exo1WorldObserver( World *__world ) : WorldObserver( __world )
{
	_world = __world;
}

Exo1WorldObserver::~Exo1WorldObserver()
{
	// nothing to do.
}

void Exo1WorldObserver::initPre() // called *before* creating and locating robots in the environment
{
    // nothing to do.
}

void Exo1WorldObserver::initPost() // called just *after* creating and locating robots in the environment
{
    // nothing to do.
}

void Exo1WorldObserver::stepPre() // called just *before* the robots move
{
    // The following code shows an example where every 100 iterations, robots are re-located to their initial positions, and parameters are randomly changed.
    /*
    if ( gWorld->getIterations() % 100 == 0 )
    {
        if ( gVerbose && gDisplayMode == 0 )
            std::cout << "Relocating\n";

        for ( int i = 0 ; i != gWorld->getNbOfRobots() ; i++ )
        {
            Robot *robot = (gWorld->getRobot(i));
            
            (*robot).setCoordReal( ...TODO... , ...TODO...  ); // whereever you want, but check locations are empty before.
        }
    }
    */
}

void Exo1WorldObserver::stepPost() // called just *after* the robots move
{
    // nothing to do.
}
