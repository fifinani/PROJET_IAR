#if defined PRJ_IAR || !defined MODULAR

#include "Config/IARConfigurationLoader.h"
#include "IAR/include/IARWorldObserver.h"
#include "IAR/include/IARAgentObserver.h"
#include "IAR/include/IARController.h"
#include "IAR/include/IARRobotWorldModel.h"
#include "WorldModels/RobotWorldModel.h"


IARConfigurationLoader::IARConfigurationLoader()
{
	// create the single instance of Agent-World Interface.
}

IARConfigurationLoader::~IARConfigurationLoader()
{
	//nothing to do
}

WorldObserver* IARConfigurationLoader::make_WorldObserver(World* wm)
{
	return new IARWorldObserver(wm);
}

RobotWorldModel* IARConfigurationLoader::make_RobotWorldModel()
{
	return new IARRobotWorldModel();
}

AgentObserver* IARConfigurationLoader::make_AgentObserver(RobotWorldModel* wm)
{
	return new IARAgentObserver(wm);
}

Controller* IARConfigurationLoader::make_Controller(RobotWorldModel* wm)
{
	return new IARController(wm);
}


#endif
