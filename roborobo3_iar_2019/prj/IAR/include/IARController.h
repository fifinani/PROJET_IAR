/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */



#ifndef IARCONTROLLER_H
#define IARCONTROLLER_H

#include "Controllers/Controller.h"
#include "RoboroboMain/common.h"

class RobotWorldModel;

class IARController : public Controller
{
	public:
		IARController( RobotWorldModel *__wm );
		~IARController();
    
		void reset();
		void step();
    
        void receiveMessage(int _senderId, std::string _message);

    protected:
        void sendMessage(IARController* _targetRobot, std::string _message);

};


#endif

