/*
 *  IARRobotWorldModel.cpp
 *  roborobo-online
 *
 *  Created by Nicolas on 20/03/09.
 *  Copyright 2009. All rights reserved.
 *
 */

#include "IAR/include/IARRobotWorldModel.h"
#include "RoboroboMain/roborobo.h"


IARRobotWorldModel::IARRobotWorldModel() : RobotWorldModel()
{
    _energyLevel_A = A_INITIAL;
    _energyLevel_B = B_INITIAL;
    std::cout << "initialisation : " << _energyLevel_A << " " << _energyLevel_B <<std::endl;
}

IARRobotWorldModel::~IARRobotWorldModel()
{
}
