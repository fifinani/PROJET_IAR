/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
#ifndef IARCONTROLLER_H
#define IARCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"
#include "IAR/include/Variables.h"
#include "World/PhysicalObject.h"
#include <string>


class RobotWorldModel;

class IARController : public Controller
{
	private:
		double A_value;
		double B_value;
		bool isClump = false;
		std::string clumpedStr = "unClumped";

		PhysicalObject * closest_A;
		PhysicalObject * closest_B;
		double closest_dist_A = -1;
		double closest_dist_B = -1;
		int _directionX_A = 0;
		int _directionY_A = 0;
		int _directionX_B = 0;
		int _directionY_B = 0;
		std::string algo;
		int nb_objet = 20;
		int nbr_iteration = 0;

		double ALossPerCycle;
		double BLossPerCycle;

		int objectiveFunction = 0;

		int alive;
	public:
		IARController( RobotWorldModel *__wm );
		~IARController();

		void reset();
		void step();
		int objective();
		int consumeNearest();
		int cueDeficit();
		int costFunction();
		int planningCostFunction();
		int reactiveFunction();
		double getDistance_A();
		double getDistance_B();
		Point2d getClosestA();
		Point2d getClosestB();
		void goToB();
		void goToA();
		void explore();
		void updateValue();
		double getDistance(PhysicalObject * obj);
		bool isInRange(PhysicalObject * obj);
		double ToroidalDistance (double x1, double y1, double x2, double y2, int& directionX, int& directionY);
		double getDistance(PhysicalObject * obj, int &directionX, int& directionY);


		void toroidaliter();

		void setClosest_A();
		void setClosest_B();
		void setClosests();
};


#endif
