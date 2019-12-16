#include "IAR/include/EnergyItem_A.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"
#include "WorldModels/RobotWorldModel.h"
#include "IAR/include/IARRobotWorldModel.h"
#include "Utilities/Misc.h"
#include <Utilities/Graphics.h>

EnergyItem_A::EnergyItem_A( int __id ) : CircleObject( __id ) // should only be called by PhysicalObjectFactory
{
    setType(0);
    _clumpID = 0;

    if ( gProperties.hasProperty( "itemRadius" ) ){
      convertFromString<double>(_radius, gProperties.getProperty( "itemRadius" ), std::dec);
  		convertFromString<double>(_footprintRadius, gProperties.getProperty( "itemRadius" ), std::dec);
  	}else
    {
        if ( gVerbose )
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem_A) missing default energy initial level (integer, >=0). Assume default (" << gEnergyItemDefaultInit << ").\n";
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
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem_A) missing default energy initial level (integer, >=0). Assume default (" << gEnergyItemDefaultInit << ").\n";
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
            std::cerr << "[MISSING] Physical Object #" << _id << " (EnergyItem_A) missing default energy mode (integer, >=0). Assume default (" << gEnergyItemDefaultMode << ").\n";
        energyMode = gEnergyItemDefaultMode;
    }
    this->setDisplayColor(0x00, 0x00, 0x00); //noir
}

EnergyItem_A::EnergyItem_A( int __id, int clumpId ) : EnergyItem_A(__id) // should only be called by PhysicalObjectFactory
{
  if(clumpId >=0){
    _clumpID = clumpId;
    MoveToClump(clumpId);
  }
}

void EnergyItem_A::step()
{
    stepPhysicalObject();
}

void EnergyItem_A::isTouched( int __idAgent )
{
//    if ( gVerbose && gDisplayMode <= 1)
//        std::cout << "[DEBUG] Physical object #" << this->getId() << " (energy item) touched by robot #" << __idAgent << std::endl;
}

void EnergyItem_A::isWalked( int __idAgent )
{
  std::cout << "walked " <<std::endl;
    gWorld->getRobot(__idAgent)->getWorldModel()->addEnergy_A( A_A );
    gWorld->getRobot(__idAgent)->getWorldModel()->addEnergy_B( A_B );

    regrowTime = 100;
    relocate();
    unregisterObject();
    registered = false;
    hide();
    _visible = false;
}

void EnergyItem_A::isPushed( int __id, std::tuple<double, double> __speed )
{
    //    if ( gVerbose && gDisplayMode <= 1)
    //        std::cout << "[DEBUG] Physical object #" << this->getId() << " (energy item) pushed by robot/object #" << __id << std::endl;
}

void EnergyItem_A::MoveToClump(int clumpId){
  unregisterObject();
  do{
    Point2d center = gClumpCenters[clumpId];
    int dist = std::rand()%251;
    int orientation = std::rand()%360;
    int x = center.x + dist*cos( (double)orientation * M_PI / 180);
    int y = center.y + dist*sin((double)orientation * M_PI / 180 );
    if(x < 0 ){ x += gAreaWidth; }
    else if( x > gAreaWidth ){ x-= gAreaWidth ; }
    if(y < 0 ){ y += gAreaHeight; }
    else if(y > gAreaHeight ){ y -= gAreaHeight ; }
    setCoordinates( x, y );
  }while(canRegister() == false);

  registerObject();

}
