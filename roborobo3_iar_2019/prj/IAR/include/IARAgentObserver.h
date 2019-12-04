/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef IARAGENTOBSERVER_H
#define IARAGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class IARAgentObserver : public AgentObserver
{
	public:
		IARAgentObserver( );
		IARAgentObserver( RobotWorldModel *__wm );
		~IARAgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

