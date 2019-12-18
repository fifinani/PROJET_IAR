#include "World/PhysicalObjectFactory.h"
#include "World/RoundObject.h"
#include "World/EnergyItem.h"
#include "IAR/include/EnergyItem_A.h"
#include "IAR/include/EnergyItem_B.h"
#include "World/GateObject.h"
#include "World/SwitchObject.h"
#include "World/MovableObject.h"
#include "RoboroboMain/roborobo.h"
#include "Utilities/Misc.h"


int PhysicalObjectFactory::_nextId = 0;
int PhysicalObjectFactory::_clumpId_A = -1;
int PhysicalObjectFactory::_clumpId_B = -1;

void PhysicalObjectFactory::makeObjectNormal( int type )
{
    int id = PhysicalObjectFactory::getNextId();

	std::string s = "";
	std::stringstream out;
	out << id;

    switch ( type )
    {
        case 0:
            if ( gVerbose )
                std::cout << "[INFO] Round Object created (type = " << type << ").\n";
            // gPhysicalObjects.push_back( new EnergyItem_A(id) );
            gPhysicalObjects.push_back( new EnergyItem_A(id) );
            break;
        case 1:
            if ( gVerbose )
                std::cout << "[INFO] Energy Item created (type = " << type << ").\n";
            // gPhysicalObjects.push_back( new EnergyItem_B(id) );
            gPhysicalObjects.push_back( new EnergyItem_B(id) );
            break;
        case 2:
            if ( gVerbose )
                std::cout << "[INFO] Gate Object created (type = " << type << ").\n";
            gPhysicalObjects.push_back( new GateObject(id) );
            break;
        case 3:
            if ( gVerbose )
                std::cout << "[INFO] Switch Object created (type = " << type << ").\n";
            gPhysicalObjects.push_back( new SwitchObject(id) );
            break;
        case 4:
            if ( gVerbose )
                std::cout << "[INFO] Movable Object created (type = " << type << ").\n";
            gPhysicalObjects.push_back( new MovableObject(id) );
            break;
        // case ...: DO NOT FORGET TO UPDATE getNbOfTypes() method.
        default:
            std::cerr << "[CRITICAL] PhysicalObjectFactory: object #" << id << ", type unknown (" << type << ")" << std::endl;
            exit(-1);
    }
}

int PhysicalObjectFactory::getNbOfTypes()
{
    return 5;
}

void PhysicalObjectFactory::makeObject( int type , bool clumped ){
  // std::cout << "create object of type : " << type << std::endl;
  if(!clumped){
    PhysicalObjectFactory::makeObjectNormal( type );
  }else{
    int id = PhysicalObjectFactory::getNextId();

    //initialisze
    if(_clumpId_A == -1 && _clumpId_B == -1){
      std::cout << "initialisation A " << _clumpId_B << std::endl;
      int rx = std::rand()%gAreaWidth;
      int ry = std::rand()%gAreaHeight;
      gClumpCenters_A.push_back(Point2d(rx,ry));
      gClumpNb_A.push_back(0);
      _clumpId_A++;
      std::cout << "initialisation B " << _clumpId_B << std::endl;
      rx = std::rand()%gAreaWidth;
      ry = std::rand()%gAreaHeight;
      gClumpCenters_B.push_back(Point2d(rx,ry));
      gClumpNb_B.push_back(0);
      _clumpId_B++;
    }else if(type == 0 && gClumpNb_A[_clumpId_A] == 0){
        std::cout << "add new clump A " << _clumpId_A << std::endl;
        int rx = std::rand()%gAreaWidth;
        int ry = std::rand()%gAreaHeight;
        gClumpCenters_A.push_back(Point2d(rx,ry));
        gClumpNb_A.push_back(0);
        _clumpId_A++;
        // std::cout << " clumpID upgrade : " << _clumpId << std::endl;
    }else if(type == 1 && gClumpNb_B[_clumpId_B] == 0 ){
      std::cout << "add new clump B " << _clumpId_B << std::endl;
        int rx = std::rand()%gAreaWidth;
        int ry = std::rand()%gAreaHeight;
        gClumpCenters_B.push_back(Point2d(rx,ry));
        gClumpNb_B.push_back(0);
        _clumpId_B++;
        // std::cout << " clumpID upgrade : " << _clumpId << std::endl;
    }


    switch ( type )
    {
      case 0:
        if ( gVerbose )
          std::cout << "[INFO] Round Object created (type = " << type << ").\n";
        gPhysicalObjects.push_back( new EnergyItem_A(id, _clumpId_A ) );
        break;
      case 1:
        if ( gVerbose )
          std::cout << "[INFO] Energy Item created (type = " << type << ").\n";
        gPhysicalObjects.push_back( new EnergyItem_B(id, _clumpId_B) );
        break;
      default:
        std::cerr << "[CRITICAL] PhysicalObjectFactory: object #" << id << ", type unknown (" << type << ")" << std::endl;
        exit(-1);
    }
  }
}

int PhysicalObjectFactory::getNextId()
{
    int retValue = _nextId;
    _nextId++;
    return retValue;
}
