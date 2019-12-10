/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
#ifndef IARCONTROLLER_H
#define IARCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"
#include "IAR/include/Variables.h"
#define RAND_MAX 1;
class RobotWorldModel;

class IARController : public Controller
{
	private:
		double A_value;
		double B_value;
		double target_orientation;
		int alive;
	public:
		IARController( RobotWorldModel *__wm );
		~IARController();

		void reset();
		void step();
		int objective();
		double getDistance_A();
		double getDistance_B();
		Point2d getClosestA();
		Point2d getClosestB();
		void goToB();
		void goToA();
		void explore();

};


#endif
