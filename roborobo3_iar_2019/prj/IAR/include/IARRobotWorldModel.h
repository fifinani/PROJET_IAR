/*
 *  RobotWorldModel.h
 *  roborobo-online
 *
 *  Created by Nicolas on 20/03/09.
 *  Copyright 2009. All rights reserved.
 *
 */


#ifndef IARROBOTAGENTWORLDMODEL_H
#define IARROBOTAGENTWORLDMODEL_H

extern double gEnergyMax;
extern int gSensorRange;

#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/common.h"
#include "IAR/include/Variables.h"

class World;

#define SENSOR_REGISTERID 0
#define SENSOR_SOURCENORM 1
#define SENSOR_SOURCEANGLE 2
#define SENSOR_TARGETNORM 3
#define SENSOR_TARGETANGLE 4
#define SENSOR_DISTANCEVALUE 5
#define SENSOR_OBJECTVALUE 6

typedef boost::multi_array<double, 2> sensor_array;

class IARRobotWorldModel : public RobotWorldModel
{
protected:
    double _energyLevel_A;
    double _energyLevel_B;

public:

	// * Initializes the variables
    IARRobotWorldModel();
    virtual ~IARRobotWorldModel();

    double getEnergyLevel_A() { return _energyLevel_A; }
    double getEnergyLevel_B() { return _energyLevel_B; }
    void setEnergyLevel_A( double __value )
    {
        _energyLevel_A = __value;
        if ( _energyLevel_A < 0 )
            _energyLevel_A = 0  ;
        else
            if ( _energyLevel_A > A_MAX )
                _energyLevel_A = A_MAX;
    }
    void setEnergyLevel_B( double __value )
    {
        _energyLevel_B = __value;
        if ( _energyLevel_B < 0 )
            _energyLevel_B = 0  ;
        else
            if ( _energyLevel_B > B_MAX )
                _energyLevel_B = B_MAX;
    }

    void addEnergy_A( double __value )
    {
        _energyLevel_A += __value;
        if ( _energyLevel_A > A_MAX )
            _energyLevel_A = A_MAX;
    }
    void addEnergy_B( double __value )
    {
        _energyLevel_B += __value;
        if ( _energyLevel_B > B_MAX )
            _energyLevel_B = B_MAX;
    }
    void substractEnergy_A( double __value )
    {
        _energyLevel_A -= __value;
        if ( _energyLevel_A < 0 )
            _energyLevel_A = 0;
    }
    void substractEnergy_B( double __value )
    {
        _energyLevel_B -= __value;
        if ( _energyLevel_B < 0 )
            _energyLevel_B = 0;
    }

};


#endif
