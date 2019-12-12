#ifndef ENERGYITEM_A_H
#define ENERGYITEM_A_H

#include "World/CircleObject.h"

class EnergyItem_A : public CircleObject
{

private:
    double maxEnergyLevel;
    int energyMode;         // 0: give all energy ; 1: give what is asked, fixed respawn delay ; 2: give what is asked, linear respawn time (ie. from what is asked).

public :

    EnergyItem_A( int __id ); // use PhysicalObjectFactory instead!
    ~EnergyItem_A() { }

    void step() override;
    void isTouched( int __idAgent ) override; // callback, triggered by agent
    void isWalked( int __idAgent ) override; // callback, triggered by agent
    void isPushed( int __id, std::tuple<double, double> __speed ) override; // callback, triggered by collision w/ agent/objects
};

#endif
