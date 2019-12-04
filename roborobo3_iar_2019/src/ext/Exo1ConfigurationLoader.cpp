#if defined PRJ_EXO1 || !defined MODULAR

#include "Config/Exo1ConfigurationLoader.h"
#include "Exo1/include/Exo1WorldObserver.h"
#include "Exo1/include/Exo1AgentObserver.h"
#include "Exo1/include/Exo1Controller.h"
#include "WorldModels/RobotWorldModel.h"


Exo1ConfigurationLoader::Exo1ConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

Exo1ConfigurationLoader::~Exo1ConfigurationLoader()
{
	//nothing to do
}

WorldObserver* Exo1ConfigurationLoader::make_WorldObserver(World* wm)
{
	return new Exo1WorldObserver(wm);
}

RobotWorldModel* Exo1ConfigurationLoader::make_RobotWorldModel()
{
	return new RobotWorldModel();
}

AgentObserver* Exo1ConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new Exo1AgentObserver(wm);
}

Controller* Exo1ConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new Exo1Controller(wm);
}


#endif
