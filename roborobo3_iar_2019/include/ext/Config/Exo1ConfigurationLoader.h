/*
 * Exo1ConfigurationLoader.h
 */

#ifndef EXO1CONFIGURATIONLOADER_H
#define	EXO1CONFIGURATIONLOADER_H

#include "Config/ConfigurationLoader.h"

class Exo1ConfigurationLoader : public ConfigurationLoader
{
	public:
		Exo1ConfigurationLoader();
		~Exo1ConfigurationLoader();

		WorldObserver *make_WorldObserver(World* wm) ;
		RobotWorldModel *make_RobotWorldModel();
		AgentObserver *make_AgentObserver(RobotWorldModel* wm) ;
		Controller *make_Controller(RobotWorldModel* wm) ;
};

#endif
