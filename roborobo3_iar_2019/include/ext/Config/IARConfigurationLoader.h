/*
 * IARConfigurationLoader.h
 */

#ifndef IARCONFIGURATIONLOADER_H
#define	IARCONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class IARConfigurationLoader : public ConfigurationLoader
{
	public:
		IARConfigurationLoader();
		~IARConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
