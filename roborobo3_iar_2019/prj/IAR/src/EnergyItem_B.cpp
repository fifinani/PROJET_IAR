#include "IAR/include/EnergyItem_B.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"
#include "WorldModels/RobotWorldModel.h"
#include "IAR/include/IARRobotWorldModel.h"
#include "Utilities/Misc.h"
#include <Utilities/Graphics.h>

EnergyItem_B::EnergyItem_B( int __id ) : CircleObject( __id ) // should only be called by PhysicalObjectFactory
{
    setType(1);


    if ( gProperties.hasProperty( "itemRadius" ) ){
      convertFromString<double>(_radius, gProperties.getProperty( "itemRadius" ), std::dec);
  		convertFromString<double>(_footprintRadius, gProperties.getProperty( "itemRadius" ), std::dec);
  	}else
    {
        if ( gVerbose )
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem_B) missing default energy initial level (integer, >=0). Assume default (" << gEnergyItemDefaultInit << ").\n";
        // _radius = 60;
        // _footprintRadius = 60;
    }

    std::string s = "";
  	std::stringstream out;
    out << getId();
    s = "physicalObject[";
  	s += out.str();
  	s += "].energy";
  	if ( gProperties.hasProperty( s ) )
  		convertFromString<double>(maxEnergyLevel, gProperties.getProperty( s ), std::dec);
  	else
      {
        if ( gVerbose )
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem_B) missing default energy initial level (integer, >=0). Assume default (" << gEnergyItemDefaultInit << ").\n";
        maxEnergyLevel = gEnergyItemDefaultInit;
    }

    s = "physicalObject[";
  	s += out.str();
  	s += "].energyMode";
  	if ( gProperties.hasProperty( s ) )
  		convertFromString<int>(energyMode, gProperties.getProperty( s ), std::dec);
  	else
    {
        if ( gVerbose )
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem_B) missing default energy mode (integer, >=0). Assume default (" << gEnergyItemDefaultMode << ").\n";
        energyMode = gEnergyItemDefaultMode;
    }
    this->setDisplayColor(0x0F, 0xF0, 0x0F);
}

void EnergyItem_B::step()
{
    stepPhysicalObject();
}

void EnergyItem_B::isTouched( int __idAgent )
{
//    if ( gVerbose && gDisplayMode <= 1)
//        std::cout << "[DEBUG] Physical object #" << this->getId() << " (energy item) touched by robot #" << __idAgent << std::endl;

}

void EnergyItem_B::isWalked( int __idAgent )
{
    gWorld->getRobot(__idAgent)->getWorldModel()->addEnergy_B( B_B );
    gWorld->getRobot(__idAgent)->getWorldModel()->addEnergy_B( B_A );

    regrowTime = 100;
    relocate();
    unregisterObject();
    registered = false;
    hide();
    _visible = false;
}

void EnergyItem_B::isPushed( int __id, std::tuple<double, double> __speed )
{
    //    if ( gVerbose && gDisplayMode <= 1)
    //        std::cout << "[DEBUG] Physical object #" << this->getId() << " (energy item) pushed by robot/object #" << __id << std::endl;
}
