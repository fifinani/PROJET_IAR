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
    _clumpID = -1;

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
    std::string str = "gALossPerCycle";
    if ( gProperties.hasProperty( str ) == true )
    {
        convertFromString<double>(ALossPerCycle, gProperties.getProperty( str ), std::dec);
    }
    else
    {
        ALossPerCycle = A_LOSS_PER_CYCLE;
    }
    str = "gBLossPerCycle";
    if ( gProperties.hasProperty( str ) == true )
    {
        convertFromString<double>(BLossPerCycle, gProperties.getProperty( str ), std::dec);
    }
    else
    {
        BLossPerCycle = B_LOSS_PER_CYCLE;
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

EnergyItem_B::EnergyItem_B( int __id, int clumpId ) : EnergyItem_B(__id) // should only be called by PhysicalObjectFactory
{
    if(clumpId >=0){
      // std::cout << "add B at : " << clumpId << " nbr : " << gClumpNb_B[clumpId] << std::endl;
      _clumpID = clumpId;
      MoveToClump(clumpId);
    }
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
    gWorld->getRobot(__idAgent)->getWorldModel()->addEnergy_B( B_B + BLossPerCycle);
    gWorld->getRobot(__idAgent)->getWorldModel()->addEnergy_A( B_A + ALossPerCycle);

    regrowTime = 100;
    if(_clumpID != -1 ){
      MoveToClump(selectNewClump());
      // std::cout << "clump B\n :";
      // for(int i =0;  i < gClumpCenters_B.size() ; i++ ){
      //   std::cout << "\tposition : " <<  gClumpCenters_B[i].x << " " << gClumpCenters_B[i].y << " nb : " << gClumpNb_B[i] << std::endl;
      // }
    }else{
      relocate();
    }
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

void EnergyItem_B::moveClump(int clumpId){
  int rx = std::rand()%gAreaWidth;
  int ry = std::rand()%gAreaHeight;
  gClumpCenters_B[clumpId] = Point2d(rx,ry);
  gClumpNb_B[clumpId] = 0;
  // std::cout << "create new clump B at : " << rx << " " << ry << std::endl;
}

int EnergyItem_B::selectNewClump(){
  int nbClump = gClumpCenters_B.size();
  int r = rand()%nbClump;
  _clumpID = r;
  return r;
}

void EnergyItem_B::MoveToClump(int clumpId){
  unregisterObject();

  do{
    Point2d center = gClumpCenters_B[clumpId];

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
  gClumpNb_B[clumpId] += 1;
  //if full realocate
  if(gClumpNb_B[clumpId] >= 5){
    moveClump(clumpId);
  }
  registerObject();
}
