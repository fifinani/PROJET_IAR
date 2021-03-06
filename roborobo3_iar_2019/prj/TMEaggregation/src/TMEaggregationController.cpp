/**
 * @author Nicolas Bredeche <nicolas.bredeche@upmc.fr>
 * 2018-10-18
 */


#include "TMEaggregation/include/TMEaggregationController.h"
#include "WorldModels/RobotWorldModel.h"
#include "RoboroboMain/roborobo.h"
#include "World/World.h"

// Load readable sensor names
#define NB_SENSORS 12 // should be coherent with gRobotSpecsImageFilename value read from the property file.
#include "Utilities/Sensorbelt.h"

TMEaggregationController::TMEaggregationController( RobotWorldModel *__wm ) : Controller ( __wm )
{
    if ( _wm->_cameraSensorsNb != NB_SENSORS )
    {
        std::cerr << "[CRITICAL] This project assumes robot specifications with " << NB_SENSORS << " sensors (provided: " << _wm->_cameraSensorsNb << " sensors). STOP.\n";
        exit(-1);
    }
}

TMEaggregationController::~TMEaggregationController()
{
    // nothing to do.
}

void TMEaggregationController::reset()
{
    // nothing to do.
}

void TMEaggregationController::step()
{
  int poids[9] = {1,1,1,1,1,-1,-1,-1,-1};
  int i;
  double rotation = 0;
  double min = 1;
  for(i=0;i<9;i++){
    if(getRobotIdAt(i) != -1 && getDistanceAt(i)< min){
      rotation = -poids[i];
      min = getDistanceAt(i);
    }else if (getWallAt(i) != -1 && getDistanceAt(i)< min){
      rotation = poids[i];
    }
  }
  setRotation(rotation);
  setTranslation(1);
}
