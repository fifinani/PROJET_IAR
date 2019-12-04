/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef EXO1CONTROLLER_H
#define EXO1CONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class Exo1Controller : public Controller
{
	public:
		Exo1Controller( RobotWorldModel *__wm );
		~Exo1Controller();
    
		void reset();
		void step();
};


#endif

