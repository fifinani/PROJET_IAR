/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "TMEdispersion/include/TMEdispersionController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

TMEdispersionController::TMEdispersionController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
}

TMEdispersionController::~TMEdispersionController()
{
    // nothing to do.
}

void TMEdispersionController::reset()
{
    // nothing to do.
}

void TMEdispersionController::step()
{
  int poids[12] = {1,1,1,1,1,-1,-1,-1,-1,-1,-1,1};
  int i;
  double rotation = 0;
  double min = 1;
  for(i=0;i<12;i++){
    if(getRobotIdAt(i) != -1 && getDistanceAt(i)< min){
      rotation = poids[i];
      min = getDistanceAt(i);
    }else if (getWallAt(i) != -1 && getDistanceAt(i)< min){
      rotation = poids[i];
    }
    if(min == 1){
      rotation = 1;
    }
  }
  setRotation(rotation);
  setTranslation(1);
}
