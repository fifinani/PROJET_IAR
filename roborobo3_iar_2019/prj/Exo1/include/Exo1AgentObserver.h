/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 */
 
#ifndef EXO1AGENTOBSERVER_H
#define EXO1AGENTOBSERVER_H 

#include "Observers/AgentObserver.h"

class RobotWorldModel;

class Exo1AgentObserver : public AgentObserver
{
	public:
		Exo1AgentObserver( );
		Exo1AgentObserver( RobotWorldModel *__wm );
		~Exo1AgentObserver();
				
		void reset() override;
		void stepPre() override;
		
};


#endif

